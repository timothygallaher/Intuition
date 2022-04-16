#pragma once
#include <Windows.h>
#include <TlHelp32.h>

class Offsets
{

public:
	DWORD m_fFlags = 0x104;
	DWORD m_flFlashDuration = 0xA420;
	DWORD m_iCrosshairId = 0xB3E8;
	DWORD m_iGlowIndex = 0x10488;
	DWORD m_iTeamNum = 0xF4;
	DWORD m_iHealth = 0x100;
	DWORD m_bDormant = 0xED;

	DWORD dwClientState = 0;		// patternscan
	DWORD dwLocalPlayer = 0;		// patternscan
	DWORD dwEntityList = 0;			// patternscan
	DWORD dwForceJump = 0;			// patternscan
	DWORD dwGlowObjectManager = 0;  // patternscan


	DWORD procID = 0;
	HANDLE hProcess = 0;
	MODULEENTRY32 client;
	MODULEENTRY32 engine;
	DWORD clientBase = 0;
	DWORD engineBase = 0;

	void OffsetUpdate();
};

extern Offsets offsets;