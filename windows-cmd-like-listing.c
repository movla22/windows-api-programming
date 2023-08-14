// This program emulates the file listing style of the Windows Command Prompt (CMD) using the Windows API. 
// It retrieves file and directory information and prints it in a format similar to CMD's listing. 
// The code showcases how to work with file attributes and time conversion in Windows programming.


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Function to exit with an error message
void ExitSys(LPCSTR lpszMsg);

int main(void)
{
    HANDLE hFileFind;
    WIN32_FIND_DATA findData;
    unsigned long long ullSize;
    SYSTEMTIME sysTime;

    // Create a snapshot for obtaining file information
    if ((hFileFind = FindFirstFile("*.*", &findData)) == INVALID_HANDLE_VALUE)
        ExitSys("FindFirstFile");

    // Traverse all files and directories
    do {
        // Convert file time to local time and system time
        FileTimeToLocalFileTime(&findData.ftLastWriteTime, &findData.ftLastWriteTime);
        FileTimeToSystemTime(&findData.ftLastWriteTime, &sysTime);
        printf("%02d.%02d.%04d %02d:%02d   ", sysTime.wDay, sysTime.wMonth, sysTime.wYear, sysTime.wHour, sysTime.wMinute);

        // Display directory or file information
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            printf("%-14s", "<DIR>");
        else {
            ullSize = (unsigned long long)findData.nFileSizeHigh << 32 | findData.nFileSizeLow;
            printf("%14llu", ullSize);
        }   
        printf(" %s\n", findData.cFileName);
    } while (FindNextFile(hFileFind, &findData));

    if (GetLastError() != ERROR_NO_MORE_FILES)
        ExitSys("FindNextFile");

    FindClose(hFileFind);

    return 0;
}

// Function to exit with an error message and system error details
void ExitSys(LPCSTR lpszMsg)
{
    DWORD dwLastErr = GetLastError();
    LPTSTR lpszErr;

    if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
        fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
        LocalFree(lpszErr);
    }

    exit(EXIT_FAILURE);
}
