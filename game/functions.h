#pragma once

#define DBG(x) std::cout << "[DEBUG]\t:" << x << std::endl;

//
//
//

namespace GameFunctions
{
	extern std::atomic<bool>isShooting;
	extern ULONGLONG TickTimer;
	extern ULONGLONG CurrentTimer;

	//actions
	void ShootAction();

	//reversed game functions
	bool IsCurrentGameModTeamBased();
	char* CurrentMapName();
	void GetEnemyEntities(std::vector<DWORD64*> &enemies);

	//created functions
	bool WorldToScreen(const vector3& pos, view_matrix_t matrix, vector3& screen, int screen_x, int screen_y);
}