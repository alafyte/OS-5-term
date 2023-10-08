#include <iostream>
#include <cstdlib>
#include <intrin.h>
#include <iomanip>
#include "Windows.h"
using namespace std;


int main()
{
	HANDLE processHandle = GetCurrentProcess();
	HANDLE threadHandle = GetCurrentThread();
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();



	cout << "Current PID:       " << pid << endl;
	cout << "Current TID:       " << tid << endl;
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

	DWORD_PTR pa = NULL, sa = NULL, icpu = -1;
	char buf[10];

	if (!GetProcessAffinityMask(processHandle, &pa, &sa))
		throw "GetProcessAffinityMask threw an exception.";

	_itoa_s(pa, buf, 2);
	cout << "Process affinity mask: " << buf;
	cout << " (" << showbase << hex << pa << ")" << endl;
	_itoa_s(sa, buf, 2);
	cout << "System affinity mask:  " << buf;
	cout << " (" << showbase << hex << sa << ")" << endl;


	SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);
	cout << "Max processors count:  " << dec << sys_info.dwNumberOfProcessors << endl;
	icpu = SetThreadIdealProcessor(threadHandle, MAXIMUM_PROCESSORS);
	cout << "Thread IdealProcessor: " << dec << icpu << endl;

	system("pause");
}

