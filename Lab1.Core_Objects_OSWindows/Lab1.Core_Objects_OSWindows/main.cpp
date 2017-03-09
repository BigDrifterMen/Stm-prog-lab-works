//#include <windows.h>
//#include <iostream>
//
//#define MAX_SEM_COUNT 10
//#define THREADCOUNT 12
//
//using namespace std;
//
//
//INT WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//{
//	CONST HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
//	if (hMutex == NULL)
//	{
//		cout << "CreateMutex error: " << GetLastError() << endl;
//		return 1;
//	}
//	CONST HANDLE hSemaphore = CreateSemaphore(NULL, MAX_SEM_COUNT, MAX_SEM_COUNT, NULL);
//	if (hSemaphore == NULL)
//	{
//		cout << "CreateSemaphore error: " << GetLastError() << endl;
//		return 1;
//	}
//	CONST HANDLE hWaitTimer = CreateWaitableTimer(NULL, FALSE, NULL);
//	if (hWaitTimer == NULL)
//	{
//		cout << "CreateWaitableTimer error: " << GetLastError() << endl;
//		return 1;
//	}
//	CONST HANDLE hTreade = CreateThread(NULL, 0, );
//	WaitForSingleObject(hSemaphore, INFINITE);
//	CloseHandle(hMutex);
//	CloseHandle(hSemaphore);
//	CloseHandle(hWaitTimer);
//	ExitProcess(0);
//
//
//}

#include <windows.h>
#include <stdio.h>
#define MAX_SEM_COUNT 10
#define THREADCOUNT 12

HANDLE ghSemaphore;

DWORD WINAPI ThreadProc(LPVOID);

int main(int argc, char* argv[])
{
	HANDLE aThread[THREADCOUNT];
	DWORD ThreadID;
	int i;
	// Create a semaphore with initial and max counts of MAX_SEM_COUNT

	ghSemaphore = CreateSemaphore(
		NULL,           // default security attributes
		MAX_SEM_COUNT,  // initial count
		MAX_SEM_COUNT,  // maximum count
		NULL);          // unnamed semaphore


	//process 4
	HANDLE hMutex = OpenMutex(
		MUTEX_ALL_ACCESS, 0, "MyApp1.0");
	if (!hMutex)
		// Mutex doesn’t exist. This is
		// the first instance so create
		// the mutex.
		hMutex = CreateMutex(0, 0, "MyApp1.0");
	else
		// The mutex exists so this is the
		// the second instance so return.
		return 0;

	if (ghSemaphore == NULL)
	{
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	// Create worker threads

	for (i = 0; i < THREADCOUNT; i++)
	{
		aThread[i] = CreateThread(
			NULL,       // default security attributes
			0,          // default stack size
			(LPTHREAD_START_ROUTINE)ThreadProc,
			NULL,       // no thread function arguments
			0,          // default creation flags
			&ThreadID); // receive thread identifier

		if (aThread[i] == NULL)
		{
			printf("CreateThread error: %d\n", GetLastError());
			return 1;
		}
	}

	// Wait for all threads to terminate

	WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);

	// Close thread and semaphore handles

	for (i = 0; i < THREADCOUNT; i++)
		CloseHandle(aThread[i]);

	CloseHandle(ghSemaphore);
	
	//process 4
	ReleaseMutex(hMutex);

	system("pause");
	return 0;

}
// thread function
DWORD WINAPI ThreadProc(LPVOID lpParam)
{

	// lpParam not used in this example
	UNREFERENCED_PARAMETER(lpParam);

	DWORD dwWaitResult;
	BOOL bContinue = TRUE;

	while (bContinue)
	{
		// Try to enter the semaphore gate.

		dwWaitResult = WaitForSingleObject(
			ghSemaphore,   // handle to semaphore
			0L);           // zero-second time-out interval

		switch (dwWaitResult)
		{
			// The semaphore object was signaled.
		case WAIT_OBJECT_0:
			// TODO: Perform task
			printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
			bContinue = FALSE;

			// Simulate thread spending time on task
			Sleep(500);

			// Release the semaphore when task is finished

			if (!ReleaseSemaphore(
				ghSemaphore,  // handle to semaphore
				1,            // increase count by one
				NULL))       // not interested in previous count
			{
				printf("ReleaseSemaphore error: %d\n", GetLastError());
			}
			break;

			// The semaphore was nonsignaled, so a time-out occurred.
		case WAIT_TIMEOUT:
			printf("Thread %d: wait timed out\n", GetCurrentThreadId());
			break;
		}
	}
	return TRUE;
}
