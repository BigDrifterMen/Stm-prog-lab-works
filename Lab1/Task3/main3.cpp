#include <windows.h>
#include <stdio.h>


#define MAX_SEM_COUNT 10
#define THREADCOUNT 12

DWORD WINAPI ThreadProc();
HANDLE ghSemaphore;

//INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
//int _tmain(int argc, TCHAR *argv[]
int main()
{
	printf("____________PROCESS 3____________\n");


	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	ghSemaphore = OpenSemaphore(EVENT_ALL_ACCESS, FALSE, "1semaphore");
	if (ghSemaphore == NULL)
	{
		printf("OpenSemaphore error: ", GetLastError());
		return 1;
	}
	HANDLE aThread[THREADCOUNT];
	DWORD ThreadID;

	for (int i = 0; i < THREADCOUNT; i++)
	{
		aThread[i] = CreateThread(
			NULL,
			0,
			(LPTHREAD_START_ROUTINE)ThreadProc,
			NULL,
			0,
			&ThreadID);

		if (aThread[i] == NULL)
		{
			printf("CreateThread error: %d\n", GetLastError());
			return 1;
		}
	}


	WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);


	for (int i = 0; i < THREADCOUNT; i++)
		CloseHandle(aThread[i]);

	CloseHandle(ghSemaphore);

	printf("\n____________END PROCESS 3___________\n");

	return 0;
}


DWORD WINAPI ThreadProc()
{
	DWORD dwWaitResult;
	BOOL bContinue = TRUE;

	while (bContinue)
	{

		dwWaitResult = WaitForSingleObject(
			ghSemaphore,
			0L);

		switch (dwWaitResult)
		{
		case WAIT_OBJECT_0:
			printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
			bContinue = FALSE;

			Sleep(5);



			if (!ReleaseSemaphore(
				ghSemaphore,
				1,
				NULL))
			{
				printf("ReleaseSemaphore error: %d\n", GetLastError());
			}
			break;

		case WAIT_TIMEOUT:
			printf("Thread %d: wait timed out\n", GetCurrentThreadId());
			break;
		}
	}
	return TRUE;
}

