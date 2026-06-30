#include "../libs/includes.h"

namespace Core
{
	EventBus g_EventBus;
	FeatureManager g_Features;

	FILE* FileBuffer = nullptr;
	HMODULE hModule = nullptr;

	// cross thread shared data, this data type prevent race conditions.
	std::atomic<bool> exitswitch = false;

	DWORD64 GameModuleBase = (DWORD64)GetModuleHandle(L"sauerbraten.exe");
	DWORD64 SDLModuleBase = (DWORD64)(GetModuleHandle(L"SDL2.dll"));

	HWND GameHwnd = FindWindowA(NULL, "Cube 2: Sauerbraten");
}

//
// Hooks
bool Core::init()
{
	SuperJmp superJmp;

	if (Render::init() && superJmp.init())
		return true;

	return false;
}

void Core::Eject()
{
	Windows::ReleaseImGuiWndProc();

	RemoveVectoredExceptionHandler(ExceptionHandler);

	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	fclose(Core::FileBuffer);
	FreeConsole();
	FreeLibraryAndExitThread(Core::hModule, 0);
}

LONG WINAPI Core::ExceptionHandler(EXCEPTION_POINTERS* pExceptionInfo)
{
	printf("\nERROR CODE: 0x%X\n", pExceptionInfo->ExceptionRecord->ExceptionCode);
	//std::cout << "\n ERROR CODE:" << "0x" << pExceptionInfo->ContextRecord << std::endl;
	std::cout << "ERROR ADDRESS:" << "0x" << pExceptionInfo->ExceptionRecord->ExceptionAddress << std::endl;
	//printf("ERROR ADDRESS: 0x%X\n", pExceptionInfo->ExceptionRecord->ExceptionAddress);
	MessageBoxA(NULL, "check terminal to find the error code", "ERROR", NULL);

	return EXCEPTION_CONTINUE_SEARCH; //Keep searching for any exceptions
}
