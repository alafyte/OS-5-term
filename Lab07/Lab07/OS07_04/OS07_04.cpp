#include <Windows.h>
#include <iostream>
#include <ctime>
using namespace std;


int main()
{
	DWORD pid = GetCurrentProcessId();
	cout << "Main process ID: " << pid << '\n';

	long long it = -60 * 10000000;

	HANDLE htimer = CreateWaitableTimer(NULL, FALSE, L"OS07_04");
	if (!SetWaitableTimer(htimer, (LARGE_INTEGER*)&it, 60000, NULL, NULL, FALSE))
		throw "SetWaitableTimer Error";

	LPCWSTR path = L"C:\\University\\5_term\\ОС\\Lab07\\Lab07\\x64\\Debug\\OS07_04x.exe";

	PROCESS_INFORMATION pi1, pi2;
	clock_t start = clock();

	STARTUPINFO si1; 
	ZeroMemory(&si1, sizeof(STARTUPINFO)); 
	si1.cb = sizeof(STARTUPINFO);

	if (CreateProcess(path, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1))
		cout << "Process OS08_04_1 was created" << endl;
	else
		cout << "CreateProcess 1 error" << endl;

	STARTUPINFO si2; 
	ZeroMemory(&si2, sizeof(STARTUPINFO)); 
	si2.cb = sizeof(STARTUPINFO);

	if (CreateProcess(path, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2))
		cout << "Process OS08_04_2 was created" << endl;
	else 
		cout << "CreateProcess 2 error" << endl;


	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);

	CloseHandle(htimer);
	cout << "Elapsed time = " << (clock() - start) / CLOCKS_PER_SEC << " s" << endl;
	system("pause");
	return 0;
}