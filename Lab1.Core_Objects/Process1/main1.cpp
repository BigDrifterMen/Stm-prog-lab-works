#include <windows.h>
#include <stdio.h>
#define MAX_SEM_COUNT 10

//INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)

//int _tmain(int argc, TCHAR *argv[])
int main()
{
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	CONST HANDLE hMutex = CreateMutex(&sa, TRUE, "1mutex");
	if (hMutex == NULL)
	{
		printf("CreateMutex error: ", GetLastError());
		return 1;
	}
	CONST HANDLE hSemaphore = CreateSemaphore(&sa, MAX_SEM_COUNT, MAX_SEM_COUNT, "1semaphore");
	if (hSemaphore == NULL)
	{
		printf("CreateSemaphore error: ", GetLastError());
		return 1;
	}
	CONST HANDLE hWaitTimer = CreateWaitableTimer(&sa, FALSE, "1waittimer");
	if (hWaitTimer == NULL)
	{
		printf("CreateWaitableTimer error: ", GetLastError());
		return 1;
	}

	LPCSTR path5 = "E:\\Desktop\\pg\\VisualStudio\\education_nulp\\Sys-programming\\Lab1.Core_Objects\\Debug\\Process5.exe";

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	SecureZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	SecureZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(path5,   // module name
		NULL,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());

		CloseHandle(hMutex);
		CloseHandle(hSemaphore);
		CloseHandle(hWaitTimer);
		return 1;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);

	printf("Bye world!\n");

	CloseHandle(hMutex);
	CloseHandle(hSemaphore);
	CloseHandle(hWaitTimer);



	return 0;
}
