#pragma once
#include "includes.h"

#ifndef defines
#define defines

#define cast(i,o)				reinterpret_cast<i>(o)
#define log(input)				debug::log(input)
#define s						std::string
#define ts(input)				std::to_string(input)
#define print(input)			log(ts(input))
#define dll						L"C:\\Users\\tyler\\Documents\\C++ Repos\\RL Modding,Hacking\\RLHook\\x64\\Release\\RLHook.dll"
#define dll_size				(std::wcslen(dll_path) + 1) * sizeof(WCHAR)
#endif