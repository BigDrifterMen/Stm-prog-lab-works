#include <windows.h>
#include <stdio.h>
#define MAX_SEM_COUNT 10


//INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
//int _tmain(int argc, TCHAR *argv[]
int main()
{
	printf("____________PROCESS 2____________\n");



	HANDLE hMutex = CreateMutex(NULL, NULL, "1mutex");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		printf("Mutex exist! ");
		hMutex = OpenMutex(NULL, NULL, "1mutex");
	}
	else
	{
		printf("Mutex does not exist! ");
	}
	HANDLE hWaitTimer = CreateWaitableTimer(NULL, FALSE, "1waittimer");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		printf("WaitableTimer exist! ");
		hWaitTimer = OpenWaitableTimer(NULL, FALSE, "1waittimer");
	}
	else
	{
		printf("WaitableTimer does not exist! ");
	}
	HANDLE hSemaphore = CreateSemaphore(NULL, MAX_SEM_COUNT, MAX_SEM_COUNT, "1semaphore");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		printf("Semaphore exist! ");
		hSemaphore = OpenSemaphore(NULL, MAX_SEM_COUNT, "1semaphore");
	}
	else
	{
		printf("Semaphore does not exist! ");
	}

	printf("\n____________END PROCESS 2____________\n");

	CloseHandle(hSemaphore);
	CloseHandle(hMutex);
	CloseHandle(hWaitTimer);

	return 0;
}