#define _CRT_NON_CONFORMING_WCSTOK
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <cstdlib>
#include "Windows.h"

#define FILE_PATH L"C:/University/5_term/ОС/Lab09/Students.txt"

using namespace std;

BOOL printFileInfo(LPWSTR FileName);
BOOL printFileTxt(LPWSTR FileName);

int main()
{
    printFileInfo((LPWSTR)FILE_PATH);
    printFileTxt((LPWSTR)FILE_PATH);
    system("pause");
}

BOOL printFileInfo(LPWSTR FileName)
{
    LPBY_HANDLE_FILE_INFORMATION lpFileInformation = new BY_HANDLE_FILE_INFORMATION();
    DWORD fileType;
    LPSYSTEMTIME systemTimeCreation = new SYSTEMTIME();
    LPSYSTEMTIME systemTimeLastWrite = new SYSTEMTIME();
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();
    try
    {
        HANDLE of = CreateFile(
            FileName,
            GENERIC_WRITE | GENERIC_READ,
            NULL,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if (of == INVALID_HANDLE_VALUE)
        {
            throw "Open file failed";
        }

        wcout << L"--- Open file successful --- \n\n";
        wcout << L"--- File info:  --- \n";

        wstring ws(FileName);
        string filename(ws.begin(), ws.end());
        const size_t last_slash_idx = filename.find_last_of("\\/");
        if (string::npos != last_slash_idx)
            filename.erase(0, last_slash_idx + 1);
        cout << "File name: " << filename << endl;

        if (GetFileInformationByHandle(of, lpFileInformation))
        {
            if (FileTimeToSystemTime(&lpFileInformation->ftCreationTime, systemTimeCreation)
                && FileTimeToSystemTime(&lpFileInformation->ftLastAccessTime, systemTimeLastWrite))
            {
                printf("Creation time: %u.%u.%u %u:%u:%u \n", systemTimeCreation->wDay, systemTimeCreation->wMonth, systemTimeCreation->wDay, systemTimeCreation->wHour, systemTimeCreation->wMinute, systemTimeCreation->wSecond);
                printf("Last access time: %u.%u.%u %u:%u:%u \n", systemTimeLastWrite->wDay, systemTimeLastWrite->wMonth, systemTimeLastWrite->wDay, systemTimeLastWrite->wHour, systemTimeLastWrite->wMinute, systemTimeLastWrite->wSecond);
            }
            else
            {
                throw "FileTimeToSystemTime failed";
            }
        }
        else
        {
            throw "GetFileInformationByHandle failed";
        }

        cout << "File type: ";
        if (fileType = GetFileType(of))
        {
            switch (fileType)
            {
            case FILE_TYPE_CHAR: cout << "Printe, console file\n"; break;
            case FILE_TYPE_DISK: cout << "Disk file\n"; break;
            case FILE_TYPE_PIPE: cout << "Socket,named pipe, or anonymous pipe\n"; break;
            case FILE_TYPE_REMOTE: cout << "UDEFINED\n"; break;
            case FILE_TYPE_UNKNOWN: cout << "Unknown file type\n"; break;
            }
        }
        else
        {
            throw "GetFileType failed";
        }

        if (GetFileSizeEx(of, fileSize))
        {
            cout << "File size: " << fileSize->QuadPart << " bytes" << endl;
        }
        else
        {
            throw "GetFileSizeEx failed";
        }

        CloseHandle(of);
    }
    catch (char* err)
    {
        cout << "--- Error:\n" << err << endl;
        return false;
    }
    return true;
}

BOOL printFileTxt(LPWSTR FileName)
{
    LPBY_HANDLE_FILE_INFORMATION lpFileInformation = new BY_HANDLE_FILE_INFORMATION();
    DWORD fileType;
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();
    try
    {
        HANDLE of = CreateFile(
            FileName,
            GENERIC_READ,
            NULL,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if (of == INVALID_HANDLE_VALUE)
        {
            throw "Open file failed";
        }

        if (GetFileSizeEx(of, fileSize))
        {
            char* buf = new char[fileSize->QuadPart];
            ZeroMemory(buf, sizeof(buf));
            DWORD n = NULL;
            if (ReadFile(of, buf, fileSize->QuadPart, &n, NULL))
            {
                buf[fileSize->QuadPart] = '\0';
                cout << "\n-- Read file: " << n << " byte successful: \n" << buf << endl;
            }
        }
        else
        {
            throw "GetFileSizeEx failed";
        }
        CloseHandle(of);
    }
    catch (char* err)
    {
        cout << "--- Error:\n" << err << endl;
        return false;
    }
    return true;
}