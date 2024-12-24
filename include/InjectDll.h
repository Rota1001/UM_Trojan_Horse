#include<Windows.h>
#include<tlhelp32.h>
#include<stdio.h>
#include<string>
#include<set>
#include<psapi.h>

extern "C" __declspec(dllexport) void inject(DWORD pid, wchar_t*);

bool isRundll32();

void injectionLoop(wchar_t*);

bool IsDllLoadedInProcess(DWORD, const std::string&);