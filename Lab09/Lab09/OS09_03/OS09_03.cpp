#define _CRT_NON_CONFORMING_WCSTOK
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <cstdlib>
#include "Windows.h"

using namespace std;

#define FILE_PATH L"C:/University/5_term/ОС/Lab09/Students.txt"

BOOL insRowFileTxt(LPWSTR FileName, LPWSTR str, DWORD row);
BOOL printFileTxt(LPWSTR fileName);

int main()
{
    LPWSTR fileName = (LPWSTR)FILE_PATH;

    printFileTxt(fileName);

    insRowFileTxt(fileName, (LPWSTR)L"1. Avdeeva Vera (0)", 0);
    insRowFileTxt(fileName, (LPWSTR)L"4. Kartuzov Danila (-1)", -1);
    insRowFileTxt(fileName, (LPWSTR)L"10. Puzikov Alexey (5)", 5);
    insRowFileTxt(fileName, (LPWSTR)L"13. Smirnov Vladislav (7)", 7);

    printFileTxt(fileName);

}

BOOL insRowFileTxt(LPWSTR fileName, LPWSTR str, DWORD row)
{
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();
    int rowCount = 1;
    int position = 0;
    int positionAfter = 0;
    bool rowFound = false;
    try
    {
        HANDLE of = CreateFile(
            fileName,
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if (of == INVALID_HANDLE_VALUE)
        {
            CloseHandle(of);
            throw "Open file failed";
        }
        if (GetFileSizeEx(of, fileSize))
        {
            char* cstr = new char[wcslen(str) * sizeof(char)];
            wcstombs(cstr, str, strlen(cstr));
            char* buf = new char[(fileSize->QuadPart + 1) * sizeof(char)];
            char* bufAfterIns = new char[(fileSize->QuadPart + 3 + strlen(cstr)) * sizeof(char)];
            ZeroMemory(buf, (fileSize->QuadPart + 1) * sizeof(char));

            ZeroMemory(bufAfterIns, (fileSize->QuadPart + 1 + strlen(cstr)) * sizeof(char));
            DWORD n = NULL;
            if (ReadFile(of, buf, fileSize->QuadPart, &n, NULL))
            {
                buf[fileSize->QuadPart] = '\0';
                while (buf[position] != '\0')
                {
                    if ((rowCount == row || row == 0) && !rowFound)
                    {
                        for (int i = 0; i < strlen(cstr); i++)
                        {
                            bufAfterIns[positionAfter++] = cstr[i];
                        }
                        bufAfterIns[positionAfter++] = '\r';
                        bufAfterIns[positionAfter++] = '\n';
                        rowFound = true;
                        rowCount++;
                    }
                    if (buf[position] == '\n')
                    {
                        rowCount++;
                    }
                    bufAfterIns[positionAfter++] = buf[position++];
                    if (buf[position] == '\0')
                    {
                        break;
                    }

                }
                if (row == MAXDWORD)
                {
                    bufAfterIns[positionAfter++] = '\r';
                    bufAfterIns[positionAfter++] = '\n';
                    for (int i = 0; i < strlen(cstr); i++)
                    {
                        bufAfterIns[positionAfter++] = cstr[i];
                    }
                    rowFound = true;
                    rowCount++;
                }
                bufAfterIns[positionAfter] = '\0';
            }
            if (rowFound)
            {
                printf("\n--- After insertion row №%d:\n%s\n", row == MAXDWORD ? -1 : row, bufAfterIns);
                if (SetFilePointer(of, 0, 0, FILE_BEGIN) == 0)
                {
                    if (WriteFile(of, bufAfterIns, strlen(bufAfterIns), &n, NULL))
                    {
                        printf("\nRow inserted successfully\n");
                    }
                    else
                    {
                        CloseHandle(of);
                        throw "WriteFile failed";
                    }
                    if (!SetEndOfFile(of))
                    {
                        CloseHandle(of);
                        throw "SetEndOfFile failed";
                    }
                }
                else
                {
                    CloseHandle(of);
                    throw "SetFilePointer failed";
                }
            }
            else
            {
                CloseHandle(of);
                throw "Row isn't found";
            }
        }
        else
        {
            CloseHandle(of);
            throw "GetFileSizeEx failed";
        }
        CloseHandle(of);
    }
    catch (const char* err)
    {
        std::cout << "--- Error:\n" << err << "\n";
        return false;
    }
    return true;
}


BOOL printFileTxt(LPWSTR fileName)
{
	try
	{
		HANDLE hf = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hf == INVALID_HANDLE_VALUE) throw "Error: Create or open file failed.";
		DWORD  n = NULL;
		char buf[1024];

		ZeroMemory(buf, sizeof(buf));
		BOOL b = ReadFile(hf, &buf, 1000, &n, NULL);
		if (!b) throw "Error: Read file failed";
		cout << buf << endl;
		CloseHandle(hf);
		return true;
	}
	catch (const char* em)
	{
		cout << "Error: " << em << endl;
		return false;
	}
}