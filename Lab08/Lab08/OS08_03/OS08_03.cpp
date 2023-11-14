#include <iostream>
#include <Windows.h>
using namespace std;
#define KB (1024)
#define MB (1024 * KB)
#define PG (4 * KB)



int main()
{
    int pages = 256;
    int countItems = pages * PG / sizeof(int);

    LPVOID xmemaddr = VirtualAlloc(NULL, pages * PG, MEM_COMMIT, PAGE_READWRITE);
    cout << "Выделено " << pages * PG / 1024 << " KB виртуальной памяти" << endl;

    int* arr = (int*)xmemaddr;
    for (int i = 0; i < countItems; i++)
        arr[i] = i;

    /* Р = D0
       у = F3
       с = F1

       Страница D0 = 208, смещение F3F = 3903

       Значение в байте должно получится 208 * 1024 + 3903 = 216895
    */

    int* byte = arr + 208 * KB + 3903;
    cout << "Значение памяти в байте: " << *byte << endl;


    if (!VirtualFree(xmemaddr, NULL, MEM_RELEASE))
        cout << "Ошибка при освобождении вирутальной памяти" << endl;

    return 0;
}