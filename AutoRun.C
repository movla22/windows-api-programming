#include <windows.h>
#include <wchar.h>
#include <stdio.h>

#define AUTORUN_KEY L"Software\\Microsoft\\Windows\\CurrentVersion\\Run"

void AddToAutorun(const wchar_t* appName, const wchar_t* appPath) {
    HKEY hKey;
    LONG result;

    result = RegOpenKeyEx(HKEY_CURRENT_USER, AUTORUN_KEY, 0, KEY_WRITE, &hKey);
    if (result != ERROR_SUCCESS) {
        wprintf(L"Autorun anahtari acilamadı. Hata: %ld\n", result);
        return;
    }

    result = RegSetValueEx(hKey, appName, 0, REG_SZ, (const BYTE*)appPath, (wcslen(appPath) + 1) * sizeof(wchar_t));
    if (result != ERROR_SUCCESS) {
        wprintf(L"Deger eklenemedi. Hata: %ld\n", result);
    }
    else {
        wprintf(L"Program basariyla autorun'a eklendi.\n");
    }

    RegCloseKey(hKey);
}

void RemoveFromAutorun(const wchar_t* appName) {
    HKEY hKey;
    LONG result;

    result = RegOpenKeyEx(HKEY_CURRENT_USER, AUTORUN_KEY, 0, KEY_WRITE, &hKey);
    if (result != ERROR_SUCCESS) {
        wprintf(L"Autorun anahtarı açılamadı. Hata: %ld\n", result);
        return;
    }

    result = RegDeleteValue(hKey, appName);
    if (result != ERROR_SUCCESS) {
        wprintf(L"Değer silinemedi. Hata: %ld\n", result);
    }
    else {
        wprintf(L"Program başarıyla autorun'dan çıkarıldı.\n");
    }

    RegCloseKey(hKey);
}

int main() {
    const wchar_t* appName = L"MyProgram";
    const wchar_t* appPath = L"C:\\Program Files\\MyProgram\\myprogram.exe";

    AddToAutorun(appName, appPath);

    // Autorun'dan çıkarmayı test etmek için:
    // RemoveFromAutorun(appName);

    return 0;
}
