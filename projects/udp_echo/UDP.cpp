/* UDP.cpp Ver 2.01.040626 */
// UDP.cpp: CUDP �N���X�̃C���v�������e�[�V����
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
// �\�z/����
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

	// WinSock�̏�����
	wVersionRequested = MAKEWORD(bLow, bHigh);			// �o�[�W����1.1
	nErrorStatus = WSAStartup(wVersionRequested, &wsaData);

	if (atexit((void (*)(void))(WSACleanup))) {	// �I������WinSock�̃��\�[�X�����
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

	// �\�P�b�g�̍쐬�i���s����ƁAINVALID_SOCKET��Ԃ��j
	m_nSock = socket(PF_INET, SOCK_DGRAM, 0);
	if ( m_nSock == INVALID_SOCKET )
		fSuccess = FALSE;

	return fSuccess;
}

BOOL CUDP::SetLocalPort(int nLocalPort)
{
	struct sockaddr_in	sockname;		// �\�P�b�g�̃A�h���X
	BOOL				fSuccess = TRUE;

	// �T�[�o��IP�A�h���X�ƃ|�[�g�ԍ��̐ݒ�

	// �C���^�[�l�b�g�̏ꍇ
	sockname.sin_family			= AF_INET;
	// �����IP�A�h���X�̎g�p
	sockname.sin_addr.s_addr	= INADDR_ANY;
	// ���[�J���̃|�[�g�ԍ�
	sockname.sin_port			= htons((unsigned short)nLocalPort);
	ZeroMemory(&sockname.sin_zero, sizeof(sockname.sin_zero));

	if ( bind(m_nSock, (struct sockaddr *)&sockname, sizeof(sockname)) == SOCKET_ERROR )
		fSuccess = FALSE;

	return fSuccess;
}

BOOL CUDP::SetServerAddr(char *lpszServer, int nPort)
{
	struct hostent		*serverhostent;	// �T�[�o�̃z�X�g���
	BOOL				fSuccess = TRUE;
	
	m_nPort = nPort;

	// svName�Ƀh�b�g�ŋ�؂���10�i����IP�A�h���X�������Ă���ꍇ
	// serveraddr��32bit������IP�A�h���X���Ԃ�
	m_ulServerAddr = inet_addr((char*)lpszServer);

	if ( m_ulServerAddr == -1 ) {
		// �T�[�o��(svName)����T�[�o�̃z�X�g�����擾
		serverhostent = gethostbyname(lpszServer);
		if ( serverhostent == NULL ) {
			// ���s
			m_ulServerAddr = 0;
			fSuccess = FALSE;
		}
		else
			// �T�[�o�̃z�X�g��񂩂��IP�A�h���X��serveraddr�ɃR�s�[
			m_ulServerAddr = *((unsigned long *)((serverhostent->h_addr_list)[0]));
	}

	return fSuccess;
}

BOOL CUDP::SendUDP(LPVOID lpBuffer, DWORD nNumberOfBytesToSend, LPDWORD lpSend)
{
	struct sockaddr_in	serversockaddr;		// �T�[�o�̃A�h���X
	BOOL				fSuccess = TRUE;
	int					nLen = 0;
	int					nRet = 0;
	
	// �T�[�o��IP�A�h���X�ƃ|�[�g�ԍ��̐ݒ�

	// �C���^�[�l�b�g�̏ꍇ
	serversockaddr.sin_family		= AF_INET;
	// �T�[�o��IP�A�h���X
	serversockaddr.sin_addr.s_addr	= m_ulServerAddr;
	// �|�[�g�ԍ�
	serversockaddr.sin_port			= htons((unsigned short)m_nPort);
	ZeroMemory(&serversockaddr.sin_zero, sizeof(serversockaddr.sin_zero));

	// �T�[�o���w�肵�ĕ�����(buf)�𑗐M
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
	struct sockaddr_in	serversockaddr;		/* �T�[�o�̃A�h���X */
	int					sockaddr_size;
	BOOL				fSuccess = TRUE;
	int					nRet = 0;
	fd_set				rdps;
	struct timeval		waittime;
	int					selret;

	// �T�[�o��IP�A�h���X�ƃ|�[�g�ԍ��̐ݒ�

	// �C���^�[�l�b�g�̏ꍇ
	serversockaddr.sin_family		= AF_INET;
	// �T�[�o��IP�A�h���X
	serversockaddr.sin_addr.s_addr	= m_ulServerAddr;
	// �|�[�g�ԍ�
	serversockaddr.sin_port			= htons((unsigned short)m_nPort);
	ZeroMemory(&serversockaddr.sin_zero, sizeof(serversockaddr.sin_zero));

	//select�֐����g���ă^�C���A�E�g��ݒ�
	waittime.tv_sec = lTimeOutSec;		// �^�C���A�E�g�b����ݒ�
	waittime.tv_usec = 0;
	FD_ZERO(&rdps);
	FD_SET(m_nSock, &rdps);				// select����\�P�b�g��ǉ�����

	selret = select(
			 FD_SETSIZE,
			 &rdps,
			 (fd_set *)0,
			 (fd_set *)0,
			 &waittime
			 );

	if( selret == SOCKET_ERROR )		// �G���[�̏ꍇ
		return FALSE;
	if( selret == 0 )					// �^�C���A�E�g�̏ꍇ
		return FALSE;
	if( ! FD_ISSET(m_nSock, &rdps) )	// ��M�͂������A�w��̃\�P�b�g�ł͂Ȃ��ꍇ
		return FALSE;

	sockaddr_size = sizeof(serversockaddr);

	// �T�[�o���w�肵�ĕ��������M
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

