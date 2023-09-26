#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();

    for (int i = 0; i < 1000; i++)
    {
        cout << "PID = " << pid << ", TID = " << tid << endl;
        Sleep(2000);
    }
}
