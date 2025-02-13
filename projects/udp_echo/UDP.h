/* UDP.h Ver 2.01.040626 */
/* link->winsock.lib */
// UDP.h: CUDP クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CEUDP_H__5C0AE130_C965_4756_A655_59293014C0C8__INCLUDED_)
#define AFX_CEUDP_H__5C0AE130_C965_4756_A655_59293014C0C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
#define MALLOC(size)				HeapAlloc(GetProcessHeap(),		\
									HEAP_ZERO_MEMORY,				\
									size							\
									)

#define	FREE(p)						HeapFree(GetProcessHeap(),		\
									0,								\
									p								\
									)
*/

class CUDP  
{
public:
	BOOL CloseUDP();
	BOOL ReceiveUDP(LPVOID lpBuffer, DWORD nNumberOfBytesToReceive, LPDWORD lpReceive, long lTimeOutSec = 0);
	BOOL SendUDP(LPVOID lpBuffer, DWORD nNumberOfBytesToSend, LPDWORD lpSend);
	BOOL SetServerAddr(char *lpszServer, int nPort);
	BOOL SetLocalPort(int nLocalPort);
	BOOL CreateUDP(BYTE bLow, BYTE bHigh);
	CUDP();
	virtual ~CUDP();

private:
	BOOL InitUDP(BYTE bLow, BYTE bHigh);
	int m_nSock;
	int m_nPort;
	unsigned long m_ulServerAddr;
};

#endif // !defined(AFX_CEUDP_H__5C0AE130_C965_4756_A655_59293014C0C8__INCLUDED_)
