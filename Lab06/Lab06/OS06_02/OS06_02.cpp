#include <iostream>
#include <windows.h>

using namespace std;

CRITICAL_SECTION cs;


void WINAPI LoopFunction(char* displayed_name)
{
	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();

	for (int i = 1; i <= 90; ++i)
	{
		if (i == 30)
			EnterCriticalSection(&cs);

		printf("[%s] %d. PID = %d TID = %u\n", displayed_name, i, pid, tid);

		if (i == 60)
			LeaveCriticalSection(&cs);

		Sleep(100);
	}
}


int main()
{
	int pid = GetCurrentProcessId();
	const int size = 2;
	DWORD ChildId1 = NULL;
	DWORD ChildId2 = NULL;

	HANDLE threads[size];

	threads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)LoopFunction, (char*)"A", 0, &ChildId1);
	threads[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)LoopFunction, (char*)"B", 0, &ChildId1);


	InitializeCriticalSection(&cs);

	LoopFunction((char*)"Main");


	WaitForMultipleObjects(size, threads, TRUE, INFINITE);
	for (int i = 0; i < size; ++i)
		CloseHandle(threads[i]);

	DeleteCriticalSection(&cs);
	return 0;
}
