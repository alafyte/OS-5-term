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


int main(int argc, char* argv[])
{
    try
    {
		if (argc == 4)
		{
			HANDLE hp = GetCurrentProcess();

			DWORD mask = atoi(argv[1]);
			DWORD firstPriority = atoi(argv[2]);
			DWORD secondPriority = atoi(argv[3]);

			if (!SetProcessAffinityMask(hp, mask))
				throw "SetProcessAffinityMask error";

			cout << "Current affinity mask: " << showbase << hex << mask << endl;
			cout << "First process priority: " << getProcessPriority(firstPriority) << endl;
			cout << "Second process priority: " << getProcessPriority(secondPriority) << endl;

			LPCWSTR path = L"C:\\University\\5_term\\ОС\\Lab05\\Lab05\\Debug\\OS05_02x.exe";
			STARTUPINFO si1, si2;
			PROCESS_INFORMATION pi1, pi2;
			ZeroMemory(&si1, sizeof(STARTUPINFO));
			ZeroMemory(&si2, sizeof(STARTUPINFO));
			si1.cb = sizeof(STARTUPINFO);
			si2.cb = sizeof(STARTUPINFO);

			if (CreateProcess(path, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | getProcessPriority(firstPriority), NULL, NULL, &si1, &pi1))
				cout << "-- Process OS05_02_1 was created\n";
			else cout << "-- Process OS05_02_1 wasn't created\n";

			if (CreateProcess(path, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | getProcessPriority(secondPriority), NULL, NULL, &si2, &pi2))
				cout << "-- Process OS05_02_2 was created\n";
			else cout << "-- Process OS05_02_2 wasn't created\n";

			WaitForSingleObject(pi1.hProcess, INFINITE);
			WaitForSingleObject(pi2.hProcess, INFINITE);

			CloseHandle(pi1.hProcess);
			CloseHandle(pi2.hProcess);
		}
		else
			cout << "No parameters provided" << endl;
	}
	catch (string err)
	{
		cout << err << endl;
	}
}
