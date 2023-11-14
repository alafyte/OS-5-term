#include <iostream>
#include <Windows.h>

using namespace std;

void sh(HANDLE pheap)
{
	PROCESS_HEAP_ENTRY phe;
	phe.lpData = NULL;
	while (HeapWalk(pheap, &phe))
	{
		cout << "-- address = " << showbase << hex << phe.lpData <<
			", size = " << dec << phe.cbData <<
			((phe.wFlags & PROCESS_HEAP_REGION) ? " R" : "") << 		// начало непрерывной области
			((phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) ? " U" : "") << 		// нераспределенная область 
			((phe.wFlags & PROCESS_HEAP_ENTRY_BUSY) ? " B" : "") << "\n"; 		// распределенная область
	}
}

int main()
{
	HANDLE pheap = GetProcessHeap();

	sh(pheap);

	int size = 300000;

	int* m = new int[size];
	
	cout << "\n\n-- m = " << showbase << hex << m << ", size = " << dec << size << endl << endl;

	sh(pheap);
	return 0;
}

