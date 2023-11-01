#include <Windows.h>
#include <iostream>
#include <ctime>
#include <TlHelp32.h>
#include <stdio.h>
using namespace std;
bool stop = false;



int GetSimpleNumbers(int n)
{
	for (int i = 2; i <= n / 2; i++)
		if ((n % i) == 0)
			return 0;
	return 1;
}



DWORD ChildThread()
{
	for (long long i = 2; ; i++)
	{
		if (stop) break;
		if (GetSimpleNumbers(i)) 
			cout << i << endl;
	}
	return 0;
}


int main()
{
	clock_t start = clock();
	HANDLE timerHandle = OpenWaitableTimer(TIMER_ALL_ACCESS, FALSE, L"OS07_04");
	DWORD childId = NULL;

	HANDLE childHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, 0, &childId);

	WaitForSingleObject(timerHandle, INFINITE);
	stop = true;
	WaitForSingleObject(childHandle, INFINITE);
	CloseHandle(childHandle);

	cout << "Elapsed time = " << (clock() - start) / CLOCKS_PER_SEC << " s" << endl;
	system("pause");
	return 0;
}