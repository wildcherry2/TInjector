#include "injector.h"

DWORD Injector::GetRocketLeaguePID() {
	PROCESSENTRY32 process_info;
	process_info.dwSize = sizeof(process_info);

	HANDLE processes_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processes_snapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processes_snapshot, &process_info);
	auto process_handle = _wcsicmp(L"RocketLeague.exe", process_info.szExeFile) == 0 ? OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_info.th32ProcessID) : NULL;

	if (process_handle == NULL) {
		while (Process32Next(processes_snapshot, &process_info)) {
			if (_wcsicmp(L"RocketLeague.exe", process_info.szExeFile) == 0) {
				CloseHandle(processes_snapshot);
				CloseHandle(process_handle);
				return process_info.th32ProcessID;
			}
		}
	}
	else return process_info.th32ProcessID;


	return GAMENOTFOUND;
}
LPVOID remote_alloc_addr;
HANDLE remote_thread;
int Injector::OpenAndInject() {
	DWORD pid = GetRocketLeaguePID();
	print(pid);
	HANDLE h = pid != 0 ? OpenProcess(PROCESS_ALL_ACCESS, false, pid) : NULL;
	if (h != NULL) {
		LPVOID LoadLibAddr = (LPVOID)GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "LoadLibraryW");
		auto dll_path = dll;
		auto dll_path_size = dll_size;
		remote_alloc_addr = VirtualAllocEx(h, NULL, dll_path_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		WriteProcessMemory(h, remote_alloc_addr, dll_path, dll_path_size, NULL);
		remote_thread = CreateRemoteThread(h, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddr, remote_alloc_addr, 0, NULL);
		WaitForSingleObject(remote_thread, INFINITE);
		VirtualFreeEx(h, remote_alloc_addr, dll_path_size, MEM_RELEASE);
		CloseHandle(remote_thread);
		CloseHandle(h);
		return 0;
	}

	return INJECTIONERROR;
}

//void Injector::OpenAndRemove() {
//	std::ofstream o;
//	o.open(std::filesystem::path("C:\\Users\\tyler\Documents\\C++ Repos\\RL Modding,Hacking\\TInjector\\state.txt"));
//	o << "remove";
//	o.close();
//}

bool Injector::IsInjected() {
	return 0;
}