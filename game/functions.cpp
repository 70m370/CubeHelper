#include"../libs/includes.h"

//
//	STILL NOT WORKING PROPERLY
//


namespace GameFunctions
{
	std::atomic<bool>isShooting = false;
	ULONGLONG TickTimer;
	ULONGLONG CurrentTimer;
}


void GameFunctions::ShootAction()
{
	uintptr_t user_entity = Core::GameModuleBase + USER_ENTITY_ADDRESS;
	uintptr_t base_address = *(uintptr_t*)user_entity;
	if (!base_address) return;
	uintptr_t shoot_state = base_address + SHOOT_OFFSET;

	if(!GameFunctions::isShooting)
	{
		*(BYTE*)shoot_state = ON;
		GameFunctions::TickTimer = GetTickCount64();
		GameFunctions::isShooting = true;
	}
}


bool GameFunctions::IsCurrentGameModTeamBased()
{
	const char* gamemodes[] = {
	"ffa",                // 0
	"coop-edit",          // 1
	"teamplay",           // 2
	"instagib",           // 3
	"instagib team",      // 4
	"efficiency",         // 5
	"efficiency team",    // 6
	"tactics",            // 7
	"tactics team",       // 8
	"capture",            // 9
	"regen capture",      // 10
	"ctf",                // 11
	"insta ctf",          // 12
	"efficiency ctf",     // 13
	"protect",            // 14
	"insta protect",      // 15
	"efficiency protect", // 16
	"hold",               // 17
	"insta hold",         // 18
	"efficiency hold",    // 19
	"collect",            // 20
	"insta collect",      // 21
	"efficiency collect"  // 22
	};

	DWORD* game_mode = *(DWORD**)(Core::GameModuleBase + CURRENT_GAMEMODE_FUNCTION_ADDRESS);
	uintptr_t current_gamemode = (DWORD)(uintptr_t)game_mode;

	int not_team[5] = { 0, 1, 3, 5, 7};

	for (int game_mode_val : not_team)
	{
		if (current_gamemode == game_mode_val)
			return false;
	}
	return true;
}

char* GameFunctions::CurrentMapName()
{
	uintptr_t CurrentClientMap = Core::GameModuleBase + CURRENT_MAP_FUNCTION_ADDRESS;

	typedef char* (__fastcall* CurrentMap)();
	CurrentMap CurrentMapF = (CurrentMap)(CurrentClientMap);

	char* current_map_name = CurrentMapF();

	return current_map_name;
}


void GameFunctions::GetEnemyEntities(std::vector<DWORD64*>& enemies)
{
	enemies.clear();

	DWORD64* entity_list = *(DWORD64**)(Core::GameModuleBase + ENTITIE_LIST_ADDRESS);
	DWORD64* user_entity = *(DWORD64**)(Core::GameModuleBase + USER_ENTITY_ADDRESS);
	DWORD64* total_players = *(DWORD64**)(Core::GameModuleBase + TOTAL_MAP_PLAYERS_ADDRESS);
	DWORD64* active_players = *(DWORD64**)(Core::GameModuleBase + ACTIVE_PLAYERS_ADDRESS);
	char* player_name = reinterpret_cast<char*>((DWORD64)user_entity + NAME_OFFSET);
	//fetch teams
	int playerteam = 0;
	int enemyteam = 0;
	int ghostteam = 0;

	char evil[] = "evil";
	char good[] = "good";

	char* evil_team = evil;
	char* good_team = good;

	char* enemy_team = nullptr;

	if (GameFunctions::IsCurrentGameModTeamBased())
	{
		char* player_team = reinterpret_cast<char*>((DWORD64)user_entity + TEAM_OFFSET);
		
		if (*player_team == *evil_team)
			enemy_team = good_team;
		else
			enemy_team = evil_team;
	}


	int player_count = reinterpret_cast<int>(active_players);

	std::vector<DWORD64*> entity_address;

	// loop through entities
	for (int i = 0; i < player_count; i++)
	{
		DWORD64* current_entity = (DWORD64*)entity_list[i];
		DWORD64 current_entity_address = (DWORD64)current_entity;
		DWORD current_entity_team = *(DWORD*)(current_entity_address + TEAM_OFFSET);

		char* team_charptr = reinterpret_cast<char*>(&current_entity_team);
		char* current_entity_name = reinterpret_cast<char*>(current_entity_address + NAME_OFFSET);

		//ghost player identification
		vector3* entity_position = (vector3*)(current_entity_address + POSITION_OFFSET);
		int entity_life = *(int*)(current_entity_address + LIFE_OFFSET);

		BYTE* current_entity_state = reinterpret_cast<BYTE*>(current_entity_address + STATE_OFFSET);


		if (enemy_team && !(current_entity_name == player_name))
		{
			if (*current_entity_state == GHOST_STATE)
			{
					ghostteam += 1;
			}
			else
			{
				if (*team_charptr == *enemy_team)
					enemies.push_back(current_entity);

				if (*team_charptr == *evil_team)
					enemyteam += 1;

				else
				{
					playerteam += 1;
				}
			}
		}
		else   //free for all case
		{
			if (!(current_entity_name == player_name))
			{
				enemies.push_back(current_entity);
			}
		}
	}
}

bool GameFunctions::WorldToScreen(const vector3& pos, view_matrix_t matrix, vector3& screen, int screen_x, int screen_y)
{
	float px = pos.x; // sideways
	float py = pos.y; // forward/back
	float pz = pos.z; // height

	float w = matrix[0][3] * px + matrix[1][3] * py + matrix[2][3] * pz + matrix[3][3];

	if (w < 0.001f)
		return false;

	float x = px * matrix[0][0] + py * matrix[1][0] + pz * matrix[2][0] + matrix[3][0];
	float y = px * matrix[0][1] + py * matrix[1][1] + pz * matrix[2][1] + matrix[3][1];
	float z = px * matrix[0][2] + py * matrix[1][2] + pz * matrix[2][2] + matrix[3][2];

	float nx = x / w;
	float ny = y / w;
	float nz = z / w;

	screen.x = (screen_x / 2.0f * nx) + (screen_x / 2.0f);
	screen.y = -(screen_y / 2.0f * ny) + (screen_y / 2.0f);
	screen.z = nz;

	return true;
}

//player pointer + 0x77 - player->state

//0 - alive
//1 - dead
//4 - editor mode
//5 - ghost