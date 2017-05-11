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

	LPCSTR path2 = "E:\\Desktop\\pg\\VisualStudio\\education_nulp\\Sys-programming\\Stm-prog-lab-works\\Lab1\\Debug\\Task2.exe";
	LPCSTR path3 = "E:\\Desktop\\pg\\VisualStudio\\education_nulp\\Sys-programming\\Stm-prog-lab-works\\Lab1\\Debug\\Task3.exe";
	LPCSTR path4 = "E:\\Desktop\\pg\\VisualStudio\\education_nulp\\Sys-programming\\Stm-prog-lab-works\\Lab1\\Debug\\Task4.exe";
	LPCSTR path5 = "E:\\Desktop\\pg\\VisualStudio\\education_nulp\\Sys-programming\\Stm-prog-lab-works\\Lab1\\Debug\\Task5.exe";


	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	SecureZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	SecureZeroMemory(&pi, sizeof(pi));

	#pragma region Task2 LAUNCH
	if (!CreateProcess(path2,   // module name
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
		system("pause");

		CloseHandle(hMutex);
		CloseHandle(hSemaphore);
		CloseHandle(hWaitTimer);

		return 1;
	}
	CloseHandle(pi.hThread);
	WaitForSingleObject(pi.hProcess, INFINITE);
	#pragma endregion
	#pragma region Task3 LAUNCH
	
	if (!CreateProcess(path3,   // module name
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
		system("pause");

		CloseHandle(hMutex);
		CloseHandle(hSemaphore);
		CloseHandle(hWaitTimer);

		return 1;
	}
	CloseHandle(pi.hThread);
	WaitForSingleObject(pi.hProcess, 100);
	#pragma endregion
	#pragma region Task4 LAUNCH
	if (!CreateProcess(path4,   // module name
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
		system("pause");

		CloseHandle(hMutex);
		CloseHandle(hSemaphore);
		CloseHandle(hWaitTimer);

		return 1;
	}
	CloseHandle(pi.hThread);
	WaitForSingleObject(pi.hProcess, INFINITE);
	#pragma endregion
	#pragma region Task5 LAUNCH
		if (!CreateProcess(path5,   // module name
				L,        
			NULL,           
			NULL,          
			TRUE,          // Set handle inheritance to True
			0,              
			NULL,           
			NULL,          
			&si,            // Pointer to STARTUPINFO structure
			&pi)           // Pointer to PROCESS_INFORMATION structure
			)
		{
			printf("CreateProcess failed (%d).\n", GetLastError());
			system("pause");

			CloseHandle(hMutex);
			CloseHandle(hSemaphore);
			CloseHandle(hWaitTimer);

			return 1;
		}
		CloseHandle(pi.hThread);
		WaitForSingleObject(pi.hProcess, INFINITE);
	#pragma endregion

	printf("\nBye world!\n");
	system("pause");
	printf("CLose handles... ");

	CloseHandle(pi.hProcess);
	CloseHandle(hMutex);
	CloseHandle(hSemaphore);
	CloseHandle(hWaitTimer);

	return 0;
}


