#include <windows.h>

int main() {
    
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    ZeroMemory(&pi, sizeof(pi));

    // "cmd.exe" 
    if (!CreateProcessA(NULL, "cmd.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Islem baslatma hatasi: %d\n", GetLastError());
        return 1;
    }

   
    WaitForSingleObject(pi.hProcess, INFINITE);

   
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
