#include<Windows.h>
#include<tlhelp32.h>
#include<stdio.h>
#include<string>
#include<set>
#include<psapi.h>

extern "C" __declspec(dllexport) void inject(DWORD pid, char*);

bool isRundll32();

void injectionLoop(char*);

bool IsDllLoadedInProcess(DWORD, const std::string&);