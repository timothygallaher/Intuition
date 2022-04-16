#pragma once
#include <iostream>
#include <stdio.h>
#include <Windows.h>

#include "offsets.h"


class Memory {
public:
	HWND hWin;
	DWORD procID;
	HANDLE hSnap;
	MODULEENTRY32 modEntry;

	DWORD GetProcID(const char* winName);
	MODULEENTRY32 GetModule(DWORD procID, const char* modName);
	void Setup();
	void GetModules();


	// Read value from memory
	template <typename T>
	T Read(DWORD address) {
		T buffer;
		ReadProcessMemory(offsets.hProcess, (LPVOID)address, &buffer, sizeof(buffer), NULL);
		return buffer;
	}


	// Write value from memory
	template <typename T>
	void Write(DWORD address, T value) {
		WriteProcessMemory(offsets.hProcess, (LPVOID)address, &value, sizeof(value), NULL);
	}
};


extern Memory mem;