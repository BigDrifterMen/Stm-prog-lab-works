#include <windows.h>
#include <stdio.h>



//INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
//int _tmain(int argc, TCHAR *argv[]
int main()
{
	printf("____________PROCESS 4____________\n");

	CONST HANDLE hMutex = CreateMutex(NULL, TRUE, "4mutex");

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		printf("You can not launch two programs! ");
		system("pause");
		return 1;
	}

	printf("Hello world!");
	printf("\n____________END PROCESS 4____________");

	CloseHandle(hMutex);

	return 0;
}