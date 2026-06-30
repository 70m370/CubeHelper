#pragma once

namespace GameGlobals
{
	//core variables
	// 
	//inline int ScreenX;
	//inline int ScreenY;

	//inline int ScreenCenterX;
	//inline int ScreenCenterY;

	extern vector2 Screen;
	extern vector2 ScreenCenter;
	extern view_matrix_t* view_matrix;
	// player associate varibales
	extern Entity* localPlayer;
	
	void UpdateValues();
}