#pragma once

/// <core concept>
///
/// Core is a namespace created to store the stack refference/memory
/// of its variables to be used across the interfaces "imgui,features etc"
/// like global variables
///
/// <>

namespace Core
{
	//event manager refference
	extern EventBus g_EventBus;
	extern FeatureManager g_Features;

	//files for console allocation refference
	extern FILE* FileBuffer;
	extern HMODULE hModule;

	//atomic switch for ejecting the dll
	extern std::atomic<bool> exitswitch;

	//Game Base address for refference
	extern DWORD64 GameModuleBase;

	//SDL2.dll module base
	extern DWORD64 SDLModuleBase;

	//Game window handle
	extern HWND GameHwnd;

	//exception handler
	LONG WINAPI ExceptionHandler(EXCEPTION_POINTERS* pExceptionInfo);


	bool init();
	void Eject();
}