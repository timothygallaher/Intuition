#pragma once
#include <Windows.h>
#include <TlHelp32.h>

#include "memory.h"

DWORD FindPattern(MODULEENTRY32 module, uint8_t* arr, const char* pattern, int offset, int extra);