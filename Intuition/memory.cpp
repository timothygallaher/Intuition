#include "memory.h"

Memory mem;


// Get a process by windowname
DWORD Memory::GetProcID(const char* winName) {
	do {
		hWin = FindWindowA(0, winName);
		Sleep(50);
	} while (!hWin);

	GetWindowThreadProcessId(hWin, &procID);

	//std::cout << "CSGO procID is " << procID << std::endl;
	return procID;
}


// Get a module by name
MODULEENTRY32 Memory::GetModule(DWORD procID, const char* modName) {
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);
	modEntry.dwSize = sizeof(MODULEENTRY32);

	if (hSnap != INVALID_HANDLE_VALUE) {
		if (Module32First(hSnap, &modEntry)) {
			do {
				if (!strcmp(modEntry.szModule, modName)) {
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
		CloseHandle(hSnap);
	}

	return modEntry;
}


void Memory::Setup() {
	offsets.procID = GetProcID("Counter-Strike: Global Offensive - Direct3D 9");
	offsets.hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, offsets.procID);
}


// Get client.dll and engine.dll
void Memory::GetModules() {
	do {
		offsets.client = GetModule(offsets.procID, "client.dll");
		offsets.clientBase = (DWORD)offsets.client.modBaseAddr;
		Sleep(50);
	} while (!offsets.clientBase);

	do {
		offsets.engine = GetModule(offsets.procID, "engine.dll");
		offsets.engineBase = (DWORD)offsets.engine.modBaseAddr;
		Sleep(50);
	} while (!offsets.engineBase);
}