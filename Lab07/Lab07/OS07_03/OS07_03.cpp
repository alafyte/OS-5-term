#include <iostream>
#include <ctime>
#include <Windows.h>

#define SECOND 10000000

using namespace std;

int main() 
{
	HANDLE htimer = CreateWaitableTimer(NULL, FALSE, NULL);
	long long it = -3 * SECOND;

	clock_t start = clock();
	for (int i = 0; ; i++) 
	{
		if (!SetWaitableTimer(htimer, (LARGE_INTEGER*)&it, 3000, NULL, NULL, FALSE)) 
		{
			throw "Error SetWaitableTimer";
		}
		if ((clock() - start) / CLOCKS_PER_SEC == 15) 
		{
			cout << "i = " << i << ", elapsed time is " << clock() - start << endl;
			break;
		}

		cout << "i = " << i << ", elapsed time is " << clock() - start << endl;
		WaitForSingleObject(htimer, INFINITE);
	}

	system("pause");
	return 0;
}