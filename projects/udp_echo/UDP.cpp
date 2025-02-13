/* UDP.cpp Ver 2.01.040626 */
// UDP.cpp: CUDP クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "windows.h"
#include "UDP.h"
#include "winsock.h"

#pragma comment(lib, "Ws2_32.lib")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CUDP::CUDP()
{
	m_nSock = INVALID_SOCKET;
}

CUDP::~CUDP()
{
	if ( m_nSock != INVALID_SOCKET )
		closesocket(m_nSock);
}

BOOL CUDP::InitUDP(BYTE bLow, BYTE bHigh)
{
	WORD		wVersionRequested;
	int			nErrorStatus;
	WSADATA		wsaData;
	BOOL		fSuccess = TRUE;

	// WinSockの初期化
	wVersionRequested = MAKEWORD(bLow, bHigh);			// バージョン1.1
	nErrorStatus = WSAStartup(wVersionRequested, &wsaData);

	if (atexit((void (*)(void))(WSACleanup))) {	// 終了時にWinSockのリソースを解放
		fSuccess = FALSE;
		exit(-1);
	}
	
	if ( nErrorStatus != 0 ) {
		fSuccess = FALSE;
		exit(-1);
	}

	return fSuccess;
}

BOOL CUDP::CreateUDP(BYTE bLow, BYTE bHigh)
{
	BOOL				fSuccess = TRUE;

	if ( ! InitUDP(bLow, bHigh) ) return FALSE;

	// ソケットの作成（失敗すると、INVALID_SOCKETを返す）
	m_nSock = socket(PF_INET, SOCK_DGRAM, 0);
	if ( m_nSock == INVALID_SOCKET )
		fSuccess = FALSE;

	return fSuccess;
}

BOOL CUDP::SetLocalPort(int nLocalPort)
{
	struct sockaddr_in	sockname;		// ソケットのアドレス
	BOOL				fSuccess = TRUE;

	// サーバのIPアドレスとポート番号の設定

	// インターネットの場合
	sockname.sin_family			= AF_INET;
	// 自らのIPアドレスの使用
	sockname.sin_addr.s_addr	= INADDR_ANY;
	// ローカルのポート番号
	sockname.sin_port			= htons((unsigned short)nLocalPort);
	ZeroMemory(&sockname.sin_zero, sizeof(sockname.sin_zero));

	if ( bind(m_nSock, (struct sockaddr *)&sockname, sizeof(sockname)) == SOCKET_ERROR )
		fSuccess = FALSE;

	return fSuccess;
}

BOOL CUDP::SetServerAddr(char *lpszServer, int nPort)
{
	struct hostent		*serverhostent;	// サーバのホスト情報
	BOOL				fSuccess = TRUE;
	
	m_nPort = nPort;

	// svNameにドットで区切った10進数のIPアドレスが入っている場合
	// serveraddrに32bit整数のIPアドレスが返る
	m_ulServerAddr = inet_addr((char*)lpszServer);

	if ( m_ulServerAddr == -1 ) {
		// サーバ名(svName)からサーバのホスト情報を取得
		serverhostent = gethostbyname(lpszServer);
		if ( serverhostent == NULL ) {
			// 失敗
			m_ulServerAddr = 0;
			fSuccess = FALSE;
		}
		else
			// サーバのホスト情報からのIPアドレスをserveraddrにコピー
			m_ulServerAddr = *((unsigned long *)((serverhostent->h_addr_list)[0]));
	}

	return fSuccess;
}

BOOL CUDP::SendUDP(LPVOID lpBuffer, DWORD nNumberOfBytesToSend, LPDWORD lpSend)
{
	struct sockaddr_in	serversockaddr;		// サーバのアドレス
	BOOL				fSuccess = TRUE;
	int					nLen = 0;
	int					nRet = 0;
	
	// サーバのIPアドレスとポート番号の設定

	// インターネットの場合
	serversockaddr.sin_family		= AF_INET;
	// サーバのIPアドレス
	serversockaddr.sin_addr.s_addr	= m_ulServerAddr;
	// ポート番号
	serversockaddr.sin_port			= htons((unsigned short)m_nPort);
	ZeroMemory(&serversockaddr.sin_zero, sizeof(serversockaddr.sin_zero));

	// サーバを指定して文字列(buf)を送信
	nRet = sendto(
		   m_nSock,
		   (const char *)lpBuffer,
		   nNumberOfBytesToSend,
		   0,
		   (struct sockaddr *)&serversockaddr,
		   sizeof(serversockaddr)
		   );

	if ( nRet == SOCKET_ERROR )
		fSuccess = FALSE;

	*lpSend = (DWORD)nRet;

	return fSuccess;
}

BOOL CUDP::ReceiveUDP(LPVOID lpBuffer, DWORD nNumberOfBytesToReceive, LPDWORD lpReceive, long lTimeOutSec)
{
	struct sockaddr_in	serversockaddr;		/* サーバのアドレス */
	int					sockaddr_size;
	BOOL				fSuccess = TRUE;
	int					nRet = 0;
	fd_set				rdps;
	struct timeval		waittime;
	int					selret;

	// サーバのIPアドレスとポート番号の設定

	// インターネットの場合
	serversockaddr.sin_family		= AF_INET;
	// サーバのIPアドレス
	serversockaddr.sin_addr.s_addr	= m_ulServerAddr;
	// ポート番号
	serversockaddr.sin_port			= htons((unsigned short)m_nPort);
	ZeroMemory(&serversockaddr.sin_zero, sizeof(serversockaddr.sin_zero));

	//select関数を使ってタイムアウトを設定
	waittime.tv_sec = lTimeOutSec;		// タイムアウト秒数を設定
	waittime.tv_usec = 0;
	FD_ZERO(&rdps);
	FD_SET(m_nSock, &rdps);				// selectするソケットを追加する

	selret = select(
			 FD_SETSIZE,
			 &rdps,
			 (fd_set *)0,
			 (fd_set *)0,
			 &waittime
			 );

	if( selret == SOCKET_ERROR )		// エラーの場合
		return FALSE;
	if( selret == 0 )					// タイムアウトの場合
		return FALSE;
	if( ! FD_ISSET(m_nSock, &rdps) )	// 受信はしたが、指定のソケットではない場合
		return FALSE;

	sockaddr_size = sizeof(serversockaddr);

	// サーバを指定して文字列を受信
	nRet = recvfrom(
		   m_nSock,
		   (char *)lpBuffer,
		   nNumberOfBytesToReceive,
		   0,
		   (struct sockaddr *)&serversockaddr,
		   &sockaddr_size
		   );
	
	if ( nRet == SOCKET_ERROR )
		fSuccess = FALSE;

	*lpReceive = (DWORD)nRet;

	return fSuccess;
}

int CUDP::CloseUDP()
{
	BOOL			fSuccess = TRUE;

	if ( closesocket(m_nSock) != 0 )
		fSuccess = FALSE;

	m_nSock = INVALID_SOCKET;
	
	return fSuccess;
}

