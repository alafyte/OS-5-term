#include <iostream>
#include <cstdlib>
#include "Windows.h"

using namespace std;

DWORD getProcessPriority(int i)
{
	switch (i)
	{
	case 1: return IDLE_PRIORITY_CLASS;
	case 2: return BELOW_NORMAL_PRIORITY_CLASS;
	case 3: return NORMAL_PRIORITY_CLASS;
	case 4: return ABOVE_NORMAL_PRIORITY_CLASS;
	case 5: return HIGH_PRIORITY_CLASS;
	case 6: return REALTIME_PRIORITY_CLASS;
	default: throw "Unknown priority class";
	}
}


DWORD getThreadPriority(int i)
{
	switch (i)
	{
	case 1: return THREAD_PRIORITY_LOWEST;
	case 2: return THREAD_PRIORITY_BELOW_NORMAL;
	case 3: return THREAD_PRIORITY_NORMAL;
	case 4: return THREAD_PRIORITY_ABOVE_NORMAL;
	case 5: return THREAD_PRIORITY_HIGHEST;
	case 6: return THREAD_PRIORITY_IDLE;
	default: throw "No such priority class";
	}
}

void TA()
{
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	HANDLE hp = GetCurrentProcess();
	HANDLE ht = GetCurrentThread();

	for (int i = 0; i < 1000000; i++)
	{
		if (i % 1000 == 0 && i != 0)
		{
			Sleep(200);
			cout << "Iteration number: " << dec << i << endl;
			cout << "Current PID: " << dec << pid << endl;
			cout << "Current TID: " << dec << tid << endl;
			DWORD processPriority = GetPriorityClass(hp);

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

			DWORD threadPriority = GetThreadPriority(ht);

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
			DWORD icpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);
			cout << "Thread IdealProcessor: " << dec << icpu << endl;
		}
	}

	cout << "End of routine" << endl;
}


int main(int argc, char* argv[])
{
	try
	{
		if (argc == 5)
		{
			HANDLE hp = GetCurrentProcess();

			DWORD mask = atoi(argv[1]);
			DWORD processPriority = atoi(argv[2]);
			DWORD firstThreadPriority = atoi(argv[3]);
			DWORD secondThreadPriority = atoi(argv[4]);

			if (!SetProcessAffinityMask(hp, mask))
				throw "SetProcessAffinityMask error";

			cout << "Current affinity mask: " << showbase << hex << mask << endl;
			cout << "Process priority: " << getProcessPriority(processPriority) << endl;
			cout << "First thread priority: " << getThreadPriority(firstThreadPriority) << endl;
			cout << "Second thread priority: " << getThreadPriority(secondThreadPriority) << endl;

			DWORD childId_T1, childId_T2 = NULL;
			HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TA, NULL, CREATE_SUSPENDED, &childId_T1);
			HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TA, NULL, CREATE_SUSPENDED, &childId_T2);

			SetThreadPriority(hChild1, getThreadPriority(firstThreadPriority));
			SetThreadPriority(hChild2, getThreadPriority(secondThreadPriority));

			ResumeThread(hChild1);
			ResumeThread(hChild2);

			WaitForSingleObject(hChild1, INFINITE);
			WaitForSingleObject(hChild2, INFINITE);

			CloseHandle(hChild1);
			CloseHandle(hChild2);

		}
		else
			cout << "No parameters provided" << endl;
	}
	catch (string err)
	{
		cout << err << endl;
	}
}

