#include"../libs/includes.h"

namespace GameGlobals
{
	vector2 Screen;
	vector2 ScreenCenter;

	view_matrix_t* view_matrix = (view_matrix_t*)(Core::GameModuleBase + VIEW_MATRIX_OFFSET);
	Entity* localPlayer = (Entity*)*(DWORD64**)(Core::GameModuleBase + USER_ENTITY_ADDRESS);

	//fetched values through swapbuffers
	void UpdateValues()
	{
		Screen.x = *(int*)(Core::GameModuleBase + SCREEN_X_OFFSET);
		Screen.y = *(int*)(Core::GameModuleBase + SCREEN_Y_OFFSET);
		ScreenCenter.x = Screen.x / 2.0f;
		ScreenCenter.y = Screen.y / 2.0f;

	}
	// player associate varibales
}