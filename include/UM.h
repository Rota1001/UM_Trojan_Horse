#include<Windows.h>
#include<string>
#include<set>
#include<tlhelp32.h>
#include<fstream>
#include<map>
#include"InjectDll.h"
#include"Rookit.h"
#include<stdlib.h>
#include<mmsystem.h>
#include<shlwapi.h>
#include"utils.h"


extern "C" __declspec(dllexport) void StartUM();

DWORD WINAPI StartFunction(LPVOID);