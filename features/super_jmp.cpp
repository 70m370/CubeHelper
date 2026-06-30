#include"../libs/includes.h"


namespace SuperJmpSwitch
{
	std::atomic<bool> toggle = false;
}

typedef int(__fastcall* Processkey)(int code, bool isdown, int modstate);
Processkey oProcessKey = NULL;

int __fastcall HProcessKey(int code, bool isdown, int modstate)
{
	if (code == SPACE_BAR && SuperJmpSwitch::toggle)
	{
		DWORD64* UserEntity = *(DWORD64**)(Core::GameModuleBase + JUMP_HEIGHT_ADDRESS);
		vector3* infinityJmpPtr = (vector3*)((DWORD64)UserEntity + JUMP_HEIGHT_OFFSET);
		infinityJmpPtr->z = 150.0f;
	}

	return oProcessKey(code, isdown, modstate);
}


bool SuperJmp::init() 
{
	DWORD64 pProcessKey = (DWORD64)(Core::GameModuleBase + PROCESS_KEY_FUNCTION_ADDRESS);
	

	if (MH_CreateHook((DWORD64*)pProcessKey, &HProcessKey, reinterpret_cast<void**>(&oProcessKey)) != MH_OK)
	{
		printf("Failed to create Processkey hook\n");
		return false;
	}

	if (MH_EnableHook((DWORD64*)pProcessKey) != MH_OK) {
		printf("Failed to enable Processkey hook!\n");
		return false;
	}

	return true;
}
