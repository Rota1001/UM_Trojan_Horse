#include"Utils.h"


wchar_t* getFolder(){
    HANDLE hMapFile = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"Folder");
    wchar_t* sharedMemory = (wchar_t*)MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 256);
    return sharedMemory;
}

void writeFolder(wchar_t* path){
    HANDLE hMapFile = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 256, L"Folder");
    wchar_t* sharedMemory = (wchar_t*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 256);
    StrCpyNW(sharedMemory, path, MAX_PATH);
}