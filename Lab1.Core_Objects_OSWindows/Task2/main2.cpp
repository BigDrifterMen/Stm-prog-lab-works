#include <windows.h>
#include <iostream>

using namespace std;


INT WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	CONST HANDLE hMutex2 = OpenMutex(MUTEX_ALL_ACCESS, TRUE, "main");
	if (hMutex2 == NULL)
	{
		cout << "OpenMutex error: " << GetLastError() << endl;
		return 1;
	}
	CONST HANDLE hSemaphore2 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, "main");
	if (hSemaphore2 == NULL)
	{
		cout << "OpenSemaphore error: " << GetLastError() << endl;
		return 1;
	}
	CONST HANDLE hWaitTimer2 = OpenWaitableTimer(TIMER_ALL_ACCESS, TRUE, "main");
	if (hWaitTimer2 == NULL)
	{
		cout << "OpenWaitableTimer error: " << GetLastError() << endl;
		return 1;
	}
}