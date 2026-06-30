#include"../libs/includes.h"

void EscFeature::Toggle()
{
	uintptr_t TableaAdress = Core::SDLModuleBase + SDL_FREECURSOR_ADDRESS;
	uintptr_t BaseAddress = *(uintptr_t*)TableaAdress;
	uintptr_t FunctionAddress = BaseAddress + SDL_FREECURSOR_OFFSET;

	if (!cursorswitch)
	{
		Windows::ImGuiWndProc();
		MEM::WRITEMEM(FunctionAddress, CURSOR_ENABLE);
		cursorswitch = true; 
	}
	else
	{
		Windows::ReleaseImGuiWndProc();
		MEM::WRITEMEM(FunctionAddress, CURSOR_DISABLE);
		cursorswitch = false;
	}
}