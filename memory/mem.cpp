#include"../libs/includes.h"

void MEM::PATCH(BYTE* byte, BYTE* addrs, int bytes)
{
	DWORD oldprotection = 0;
	if (VirtualProtect(addrs, bytes, PAGE_EXECUTE_READWRITE, &oldprotection))
	{
		memcpy(addrs, byte, bytes);
		VirtualProtect(addrs, bytes, oldprotection, &oldprotection);
	}
	else
		printf("MEM::PATCH FAILED at 0x%x\n", addrs);
}

void MEM::WRITEMEM(uintptr_t address, int newValue)
{
	DWORD oldprotection = 0;
	if (VirtualProtect((LPVOID)address, sizeof(int), PAGE_EXECUTE_READWRITE, &oldprotection))
	{
		*(int*)address = newValue;
		VirtualProtect((LPVOID)address, sizeof(int), oldprotection, &oldprotection);
	}
	else
		printf("MEM::WRITEMEM failed at 0x%x\n",address);
}

void MEM::WRITEMEM64(DWORD64 addrs, int newValue)
{
	DWORD oldprotection = 0;
	if (VirtualProtect((LPVOID)addrs, sizeof(int), PAGE_EXECUTE_READWRITE, &oldprotection))
	{
		*(int*)addrs = newValue;
		VirtualProtect((LPVOID)addrs, sizeof(int), oldprotection, &oldprotection);
	}
	else
		printf("MEM::WRITEMEM failed at 0x%x\n", addrs);
}
