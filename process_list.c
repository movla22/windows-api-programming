#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

// Function to list processes
void listProcesses() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // Create a snapshot for obtaining process information
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        printf("Snapshot could not be created. Error: %d\n", GetLastError());
        return;
    }

    // Set the size of PROCESSENTRY32 structure and get the first process information
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32)) {
        printf("Process information could not be retrieved. Error: %d\n", GetLastError());
        CloseHandle(hProcessSnap);
        return;
    }

    // Traverse all processes and print information
    printf("Process List:\n");
    do {
        printf("Process ID: %d\n", pe32.th32ProcessID);
        printf("Process Name: %s\n", pe32.szExeFile);
        printf("----------------------------------\n");
    } while (Process32Next(hProcessSnap, &pe32));

    // Close the snapshot handle
    CloseHandle(hProcessSnap);
}

int main() {
    listProcesses();
    return 0;
}
