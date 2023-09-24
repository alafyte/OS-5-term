#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{

    for (int i = 0; i < 125; i++)
    {
        cout << "PID: " << GetCurrentProcessId() << endl;
        Sleep(1000);
    }
}

