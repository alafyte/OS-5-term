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
	HANDLE heap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 1024 * 1024 * 4, 0);
	sh(heap);

	int* m = (int*)HeapAlloc(heap, HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 300000 * sizeof(int));
	cout << "\n\nAddress: " << m << endl << endl;

	sh(heap);

	HeapFree(heap, HEAP_NO_SERIALIZE, m);
	cout << endl << endl;
	sh(heap);
	HeapDestroy(heap);
}

