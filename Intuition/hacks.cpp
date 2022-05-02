#include "hacks.h"


struct Glow
{
	float r, g, b, a;
	uint8_t padding[8];
	float junk = 1;
	uint8_t padding2[4];
	BYTE RenderWhenObstructed = 1;
	BYTE NotRenderWhenObstructed = 0;
	BYTE fullbloom = 0;
}glowConfig;

void Trigger()
{
	DWORD localPlayer = mem.Read<DWORD>(offsets.dwLocalPlayer + offsets.clientBase);
	int xHair = mem.Read<int>(localPlayer + offsets.m_iCrosshairId);

	if (xHair == 0 || xHair > 64)
		return;

	DWORD entity = mem.Read<DWORD>(offsets.clientBase + offsets.dwEntityList + (xHair - 1) * 0x10);

	if (GetAsyncKeyState(0x56) < 0)
	{
		int myTeam = mem.Read<int>(localPlayer + offsets.m_iTeamNum);
		int entityTeam = mem.Read<int>(entity + offsets.m_iTeamNum);

		if (myTeam != entityTeam)
		{
			Sleep(5);
			mem.Write<int>(offsets.clientBase + offsets.dwForceAttack, 5);
			Sleep(20);
			mem.Write<int>(offsets.clientBase + offsets.dwForceAttack, 4);
		}
	}
}

void Antiflash()
{
	DWORD localPlayer = mem.Read<DWORD>(offsets.dwLocalPlayer + offsets.clientBase);

	int flashDur = mem.Read<int>(localPlayer + offsets.m_flFlashDuration);

	if (flashDur > 0)
	{
		mem.Write<int>(localPlayer + offsets.m_flFlashDuration, 0);
	}

	Sleep(10);
}

void GlowHack()
{
	DWORD localPlayer = mem.Read<DWORD>(offsets.dwLocalPlayer + offsets.clientBase);
	DWORD glowManager = mem.Read<DWORD>(offsets.dwGlowObjectManager + offsets.clientBase);
	DWORD myTeam = mem.Read<DWORD>(localPlayer + offsets.m_iTeamNum);

	for (int i = 1; i < 24; ++i)
	{
		DWORD entity = mem.Read<DWORD>(offsets.clientBase + offsets.dwEntityList + i * 0x10);
		if (entity == NULL)
			continue;

		bool isDormant = mem.Read<bool>(entity + offsets.m_bDormant);
		if (isDormant)
			continue;

		int entityTeam = mem.Read<int>(entity + offsets.m_iTeamNum);
		if (myTeam == entityTeam)
			continue;

		int glowIndex = mem.Read<int>(entity + offsets.m_iGlowIndex);

		glowConfig.r = 1.f;
		glowConfig.g = 0.f;
		glowConfig.b = 1.f;
		glowConfig.a = 0.5;
		mem.Write<Glow>(glowManager + (glowIndex * 0x38) + 0x08, glowConfig);
	}

}

void Bhop()
{
	int flag = mem.Read<DWORD>(mem.Read<DWORD>(offsets.dwLocalPlayer + (DWORD)offsets.clientBase) + offsets.m_fFlags);
	if ((flag == 257 || flag == 263 || flag == 261) && GetAsyncKeyState(VK_SPACE) < 0)
	{
		mem.Write<DWORD>(offsets.dwForceJump, 6);
	}
	else
		mem.Write<DWORD>(offsets.dwForceJump, 4);
}