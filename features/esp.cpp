#include"../libs/includes.h"

namespace EspSwitch
{
	std::atomic<bool> Toggle = false;
}


void Esp::Toggle()
{
	HDC GameHdc = GetDC(Core::GameHwnd);
	std::vector<DWORD64*> entity_list;
	
	GameFunctions::GetEnemyEntities(entity_list);
	
	// SDL logic is different
	vector3 local_player_cur_pos
	{
		local_player_cur_pos.x = GameGlobals::localPlayer->position.y,
		local_player_cur_pos.y = GameGlobals::localPlayer->position.x,
		local_player_cur_pos.z = GameGlobals::localPlayer->position.z
	};

	for (DWORD64* current_entity : entity_list)
	{
		Entity* ent = (Entity*)current_entity;

		if (ent == GameGlobals::localPlayer || ent->health <= 0)
			continue;

		// 1. Define the 3D points in the world
		vector3 world_feet = { ent->position.x, ent->position.y, ent->position.z - 12.0f };
		vector3 world_head = ent->position; 

		vector3 screen_feet, screen_head;

		float fov_size = 50.0f;

		// 2. Project both points to 2D screen space
		if (GameFunctions::WorldToScreen(world_feet, *GameGlobals::view_matrix, screen_feet, GameGlobals::Screen.x, GameGlobals::Screen.y) &&
			GameFunctions::WorldToScreen(world_head, *GameGlobals::view_matrix, screen_head, GameGlobals::Screen.x, GameGlobals::Screen.y))
		{

			// 3. The height is simply the difference between the head Y and feet Y
			float height = std::abs(screen_feet.y - screen_head.y);
			float width = height / 2.0f; // Standard 2:1 aspect ratio for humans

			float left = screen_head.x - (width / 2.0f);
			float right = screen_head.x + (width / 2.0f);
			float top = screen_head.y;
			float bottom = screen_feet.y - 0.9f;

			// 4. Draw using these modular coordinates
			Render::DrawLine(left, bottom, right, bottom, Render::GreenPen);
			Render::DrawLine(left, top, right, top, Render::GreenPen);
			Render::DrawLine(left, bottom, left, top, Render::GreenPen);
			Render::DrawLine(right, bottom, right, top, Render::GreenPen);
		}

		//snapline
		Render::DrawLine(GameGlobals::ScreenCenter.x, GameGlobals::Screen.y, screen_feet.x, screen_feet.y, Render::WhitePen);
	}
	entity_list.clear();
	ReleaseDC(Core::GameHwnd, GameHdc);
}