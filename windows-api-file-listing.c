// Author: Movla M.
// Date: 13.08.2023
// Description: This program lists files and directories in a specified directory using Windows API.


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
    HANDLE hFileFind;
    WIN32_FIND_DATA findData;
    unsigned long long ullSize;

    if ((hFileFind = FindFirstFile("c:\\windows\\*.*", &findData)) == INVALID_HANDLE_VALUE)
        ExitSys("FindFirstFile");

    do {
        printf("%-50s", findData.cFileName);
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            printf("%s", "<DIR>");
        else {
            ullSize = (unsigned long long)findData.nFileSizeHigh << 32 | findData.nFileSizeLow;
            printf("%30llu", ullSize);
        }   
        printf("\n");

    } while (FindNextFile(hFileFind, &findData));

    if (GetLastError() != ERROR_NO_MORE_FILES)
        ExitSys("FindNextFile");

    FindClose(hFileFind);

    return 0;
}

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






/*
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	HANDLE hFileFind;
	WIN32_FIND_DATA findData;
	unsigned long long ullSize;

	if ((hFileFind = FindFirstFile("c:\\windows\\*.*", &findData)) == INVALID_HANDLE_VALUE)
		ExitSys("FindFirstFile");

	do {
		printf("%-50s", findData.cFileName);
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			printf("%s", "<DIR>");
		else {
			ullSize = (unsigned long long)findData.nFileSizeHigh << 32 | findData.nFileSizeLow;
			printf("%30llu", ullSize);
		}	
		printf("\n");
		
	} while (FindNextFile(hFileFind, &findData));

	if (GetLastError() != ERROR_NO_MORE_FILES)
		ExitSys("FindNextFile");

	FindClose(hFileFind);

	return 0;
}

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


*/
