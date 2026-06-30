#include"../libs/includes.h"

namespace AimBotSwitch
{
	std::atomic<bool> Toggle = false;
}

bool AimBot::Toggle()
{
	float fov_size = 50.0f;
	HDC GameHdc = GetDC(Core::GameHwnd);

	std::vector<DWORD64*> EntityAddresses;
	GameFunctions::GetEnemyEntities(EntityAddresses);
	vector3 eye_position = GameGlobals::localPlayer->position;
	vector3 view_angles = GameGlobals::localPlayer->angles;

	Render::DrawCircle(GameGlobals::ScreenCenter, fov_size, Render::WhitePen);

	for (DWORD64* current_ent : EntityAddresses)
	{
		Entity* ent = (Entity*)current_ent;

		if (ent == GameGlobals::localPlayer || ent->health <= 0)
			continue;

		vector3 current_ent_world_position = { ent->position.x,ent->position.y,ent->position.z };
		vector3 ent_position_on_screen;

		if (!GameFunctions::WorldToScreen(current_ent_world_position, *GameGlobals::view_matrix, ent_position_on_screen, GameGlobals::Screen.x, GameGlobals::Screen.y))
			continue;

		float dx = ent_position_on_screen.x - GameGlobals::ScreenCenter.x;
		float dy = ent_position_on_screen.y - GameGlobals::ScreenCenter.y;
		float ent_on_fov = sqrtf(dx * dx + dy * dy);
		

		vector3 dir = {
			current_ent_world_position.x - eye_position.x,
			current_ent_world_position.y - eye_position.y,
			current_ent_world_position.z - eye_position.z
		};

		vector3 dist_relation = {
			current_ent_world_position.x - GameGlobals::localPlayer->position.x,
			current_ent_world_position.y - GameGlobals::localPlayer->position.y,
			current_ent_world_position.z - GameGlobals::localPlayer->position.z
		};
		
		float distance = std::sqrt(
			(dist_relation.x * dist_relation.x) +
			(dist_relation.y * dist_relation.y) +
			(dist_relation.z * dist_relation.z)
		);

		//
		// entity inside the fov circle
		if (ent_on_fov < fov_size || distance < 25.000)
		{

			float target_yaw = atan2f(dir.y, dir.x) * (180.0f / std::numbers::pi_v<float>) - 90.0f;
			float horizontal_dist = sqrtf(dir.x * dir.x + dir.y * dir.y);
			float target_pitch = atan2f(dir.z, horizontal_dist) * (180.0f / std::numbers::pi_v<float>);

			GameGlobals::localPlayer->angles.x = target_yaw;
			GameGlobals::localPlayer->angles.y = std::clamp(target_pitch, -89.0f, 89.0f);
			EntityAddresses.clear();
			ReleaseDC(Core::GameHwnd, GameHdc);
			return true;
		}
	}
	EntityAddresses.clear();
	ReleaseDC(Core::GameHwnd, GameHdc);
	return false;
}
