#pragma once
#include "includes.h"

enum Errors;

struct Injector {
	static DWORD GetRocketLeaguePID();
	static int OpenAndInject();
	//static void OpenAndRemove();
	static bool IsInjected();
};

enum Errors {
	GAMENOTFOUND,
	INJECTIONERROR,
	NOTINJECTED
};