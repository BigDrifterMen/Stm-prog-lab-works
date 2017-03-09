#include <windows.h>
#include <iostream>

#define MAX_SEM_COUNT 10

using namespace std;


INT WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	CONST HANDLE hMutex = CreateMutex(NULL, TRUE, "main");
	if (hMutex == NULL)
	{
		cout << "CreateMutex error: " << GetLastError() << endl;
		return 1;
	}
	CONST HANDLE hSemaphore = CreateSemaphore(NULL, MAX_SEM_COUNT, MAX_SEM_COUNT, "main");
	if (hSemaphore == NULL)
	{
		cout << "CreateSemaphore error: " << GetLastError() << endl;
		return 1;
	}
	CONST HANDLE hWaitTimer = CreateWaitableTimer(NULL, FALSE, "main");
	if (hWaitTimer == NULL)
	{
		cout << "CreateWaitableTimer error: " << GetLastError() << endl;
		return 1;
	}




	CloseHandle(hMutex);
	CloseHandle(hSemaphore);
	CloseHandle(hWaitTimer);

	ExitProcess(0);
}
