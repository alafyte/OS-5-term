#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <TlHelp32.h>

using namespace std;

int main()
{
    DWORD pid = GetCurrentProcessId();
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

    PROCESSENTRY32 peProcessEntry;
    peProcessEntry.dwSize = sizeof(PROCESSENTRY32);

	wcout << L"Current PID = " << pid << endl << L"-----------------------------------" << endl;
	try
	{
		if (!Process32First(snap, &peProcessEntry))
			throw L"Process32First";
		do
		{
			wcout << L"Name\t\t" << peProcessEntry.szExeFile << endl
				<< L"PID\t\t" << peProcessEntry.th32ProcessID;
			if (peProcessEntry.th32ProcessID == pid)
				wcout << " --> current process";
			wcout << L"\nParent ID\t" << peProcessEntry.th32ParentProcessID;

			wcout << endl << L"-----------------------------------" << endl;

		} while (Process32Next(snap, &peProcessEntry));
	}
	catch (char* msg)
	{
		wcout << L"ERROR: " << msg << endl;
	}

}

