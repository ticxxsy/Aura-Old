
#include "stdafx.h"

#define RELATIVE_ADDR(addr, size)       ((uintptr_t)((uintptr_t)(addr) + *(PINT)((uintptr_t)(addr) + ((size) - sizeof(INT))) + (size)))
#define rva(addr, size) (reinterpret_cast<unsigned char*>(addr + *reinterpret_cast<int*>(addr + (size - 4)) + size))

void Main() {

	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);

	auto basemodule = GetModuleHandle(0);

	Basic::UWorld_Offset = g_Scanner->FindPattern(basemodule, ("\x48\x89\x05\x00\x00\x00\x00\x48\x8B\x8B\x00\x00\x00\x00"),
		"xxx????xxx????", 0);
	Basic::UWorld_Offset = reinterpret_cast<decltype(Basic::UWorld_Offset)>(rva(Basic::UWorld_Offset, 7));

	pGetBoneMatrix = g_Scanner->FindPattern(basemodule, ("\xE8\x00\x00\x00\x00\x48\x8B\x47\x30\xF3\x0F\x10\x45\x00"),
		"x????xxxxxxxx?", 0);
	pGetBoneMatrix = reinterpret_cast<decltype(pGetBoneMatrix)>(rva(pGetBoneMatrix, 5));


	printf("\n[Project-X] UWorld -> 0x%x", Basic::UWorld_Offset);

	hkpost::hkpostexecute();
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:

		DisableThreadLibraryCalls(hModule);
		Main();

		return TRUE;
	}

	return FALSE;
}
