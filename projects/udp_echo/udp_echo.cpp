// udp_echo.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

//#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

#include "UDP.h"


#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS


#define MALLOC(size)				HeapAlloc(GetProcessHeap(),		\
									HEAP_ZERO_MEMORY,				\
									size							\
									);

#define	FREE(p)						HeapFree(GetProcessHeap(),		\
									0,								\
									p								\
									);

BOOL		g_fStop;

/*
	[Property]
		ServerIpAddress
		ServerPort
		LocalPort
		Timeout
		Size
*/

typedef struct {

	int			nMode;
	char		szServerIP[16];
	int			nServerPort;
	int			nLocalPort;
	int			nTimeOut;
	DWORD		dwSize;

} OPTION_PRAM_UDP;


DWORD WINAPI test_Thread_func(LPVOID lpParameter)
{
	OPTION_PRAM_UDP		pram;
	CUDP				udp;
	char* lpTest;
	DWORD				dwCount = 0;
	BOOL				fSuccess = FALSE;
	DWORD				i;

	pram = *(OPTION_PRAM_UDP*)lpParameter;

	fSuccess = udp.CreateUDP(1, 1);
	if (!fSuccess) {
		printf("\r\nudp_echo> ERROR in CreateUDP()\r\n");
		return 0;
	}

	fSuccess = udp.SetServerAddr(pram.szServerIP, pram.nServerPort);
	if (!fSuccess) {
		printf("\r\nudp_echo> ERROR in SetServerAddr()\r\n");
		goto error0;
	}

	fSuccess = udp.SetLocalPort(pram.nLocalPort);
	if (!fSuccess) {
		printf("\r\nudp_echo> ERROR in SetLocalPort()\r\n");
		goto error0;
	}

	lpTest = (char*)MALLOC(pram.dwSize);

	do {

		ZeroMemory(lpTest, pram.dwSize);
		fSuccess = udp.ReceiveUDP(lpTest, pram.dwSize, &dwCount, pram.nTimeOut);

		if (!fSuccess)
			printf("\r\nudp_echo> Time out!!\r\n");
		else {
			for (i = 0; i < dwCount; i++) {
				if (lpTest[i] != 0x7)
					printf("%c", lpTest[i]);
			}

			fSuccess = udp.SendUDP(
				lpTest,
				pram.dwSize,
				&dwCount
			);

			if (!fSuccess)
				printf("\r\nudp_echo> ERROR in SendUDP()\r\n");
		}
		Sleep(1);

	} while (!g_fStop);

	FREE(lpTest);

error0:

	fSuccess = udp.CloseUDP();
	if (!fSuccess) {
		printf("\r\nudp_echo> ERROR in CloseUDP()\r\n");
		return 0;
	}

	return 0;
}


int outini()
{
	OPTION_PRAM_UDP		pram;
	HANDLE				hFile;
	DWORD				dwCount = 0;

	//	char		szServerIP[16];
	//	int			nServerPort;
	//	int			nLocalPort;
	//	int			nTimeOut;
	//	DWORD		dwSize;

	strcpy(pram.szServerIP, "192.168.0.2");
	pram.nServerPort = 0xC000;
	pram.nLocalPort = 1001;
	pram.nTimeOut = 5;
	pram.dwSize = 1024;//32768;

	hFile = CreateFile(
		L".\\udp_echo.ini",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	WriteFile(hFile, &pram, sizeof(OPTION_PRAM_UDP), &dwCount, NULL);

	CloseHandle(hFile);

	return 0;
}


int main()
{
//    std::cout << "Hello World!\n";
	static OPTION_PRAM_UDP		pram;
	HANDLE						hThread;
	DWORD						dwThreadID;
	HANDLE						hFile;
	DWORD						dwCount = 0;

	//outini(); return 0;

	hFile = CreateFile(
		L".\\udp_echo.ini",
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hFile == INVALID_HANDLE_VALUE) {
		printf("\r\nudp_echo> ERROR in CreateFile()\r\n");
		return 1;
	}

	ReadFile(hFile, &pram, sizeof(OPTION_PRAM_UDP), &dwCount, NULL);

	CloseHandle(hFile);

	printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\r\n");
	printf("\r\n");
	printf("    Echo Server for UDP Test  Ver 0.9.2\r\n");
	printf("\r\n");
	printf("(C)2025 Aeterlink Corp.,\r\n");
	printf("\r\n");
	printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\r\n");
	printf("\r\n");

	g_fStop = FALSE;

	hThread = ::CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)test_Thread_func,
		&pram,
		0,
		&dwThreadID
	);

	getch();
	printf("_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\r\n");
	printf("UDPEcho> Waiting for end of thread...\r\n");
	g_fStop = TRUE;

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	printf("Good Bye!!\r\n");

	return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
