#include "offsets.h"
#include "patternscanning.h"


Offsets offsets;


void Offsets::OffsetUpdate()
{
	auto bytes = new uint8_t[offsets.client.modBaseSize]; //making a variable size of the module
	DWORD bytes_read;
	ReadProcessMemory(hProcess, offsets.client.modBaseAddr, bytes, client.modBaseSize, &bytes_read); //reading the module and storing as bytes_read
	if (bytes_read != client.modBaseSize) throw; //checking that the size of bytes read is = to size of bytes in the module

	offsets.dwLocalPlayer = FindPattern(offsets.client, bytes, "8D 34 85 ? ? ? ? 89 15 ? ? ? ? 8B 41 08 8B 48 04 83 F9 FF", 0x3, 0x4) - offsets.clientBase; //0x3 is the offset, 0x4 is the extra
	offsets.dwEntityList = FindPattern(offsets.client, bytes, "BB ? ? ? ? 83 FF 01 0F 8C ? ? ? ? 3B F8", 0x1, 0x0); //0x1 is the offset, there is no extra
	offsets.dwGlowObjectManager = FindPattern(offsets.client, bytes, "A1 ? ? ? ? A8 01 75 4B", 0x1, 0x4) - offsets.clientBase;
	offsets.dwForceJump = FindPattern(offsets.client, bytes, "8B 0D ? ? ? ? 8B D6 8B C1 83 CA 02", 0x2, 0x0);
	offsets.dwClientState = FindPattern(offsets.engine, bytes, "A1 ? ? ? ? 33 D2 6A 00 6A 00 33 C9 89 B0", 0x1, 0x0);
	delete[] bytes;
}