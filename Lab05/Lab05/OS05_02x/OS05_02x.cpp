﻿#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <cstdlib>
#include <intrin.h>

using namespace std;

int main()
{
	HANDLE processHandle = GetCurrentProcess();
	HANDLE threadHandle = GetCurrentThread();
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
	DWORD_PTR icpu = -1;

    for (int i = 0; i < 1000000; i++)
    {
        if (i % 1000 == 0 && i != 0)
        {
			Sleep(200);
            cout << "Iteration number: " << dec << i << endl;
			cout << "Current PID: " << dec << pid << endl;
			cout << "Current TID: " << dec << tid << endl;
			DWORD processPriority = GetPriorityClass(processHandle);

			switch (processPriority)
			{
			case IDLE_PRIORITY_CLASS:				cout << "Process priority:  IDLE_PRIORITY_CLASS\n";				break;
			case BELOW_NORMAL_PRIORITY_CLASS:		cout << "Process priority:  BELOW_NORMAL_PRIORITY_CLASS\n";		break;
			case NORMAL_PRIORITY_CLASS:				cout << "Process priority:  NORMAL_PRIORITY_CLASS\n";			break;
			case ABOVE_NORMAL_PRIORITY_CLASS:		cout << "Process priority:  ABOVE_NORMAL_PRIORITY_CLASS\n";		break;
			case HIGH_PRIORITY_CLASS:				cout << "Process priority:  HIGH_PRIORITY_CLASS\n";				break;
			case REALTIME_PRIORITY_CLASS:			cout << "Process priority:  REALTIME_PRIORITY_CLASS\n";			break;
			default:								cout << "Unknown process priority.\n";					break;
			}

			DWORD threadPriority = GetThreadPriority(threadHandle);

			switch (threadPriority)
			{
			case THREAD_PRIORITY_LOWEST:		cout << "Thread priority:  THREAD_PRIORITY_LOWEST\n";			break;
			case THREAD_PRIORITY_BELOW_NORMAL:	cout << "Thread priority:  THREAD_PRIORITY_BELOW_NORMAL\n";	break;
			case THREAD_PRIORITY_NORMAL:		cout << "Thread priority:  THREAD_PRIORITY_NORMAL\n";			break;
			case THREAD_PRIORITY_ABOVE_NORMAL:	cout << "Thread priority:  THREAD_PRIORITY_ABOVE_NORMAL\n";	break;
			case THREAD_PRIORITY_HIGHEST:		cout << "Thread priority:  THREAD_PRIORITY_HIGHEST\n";			break;
			case THREAD_PRIORITY_IDLE:			cout << "Thread priority:  THREAD_PRIORITY_IDLE\n";			break;
			default:							cout << "Unknown thread priority.\n";					break;
			}
			icpu = SetThreadIdealProcessor(threadHandle, MAXIMUM_PROCESSORS);
			cout << "Thread IdealProcessor: " << dec << icpu << endl;
        }
    }

	system("pause");
}

