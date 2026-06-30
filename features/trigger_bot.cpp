#include"../libs/includes.h"

namespace TriggerBotSwitch
{
	std::atomic<bool>Toggle = false;
}

bool TriggerBot::Toggle()
{
	if (TriggerBotSwitch::Toggle)
	{
		std::vector<DWORD64*> EntityList;
		GameFunctions::GetEnemyEntities(EntityList);


		for (DWORD64* entityptr : EntityList)
		{
			DWORD64* current_entity = entityptr;
			int current_entity_life = *(int*)((DWORD64)entityptr + LIFE_OFFSET);
			vector3 current_entity_position = *(vector3*)((DWORD64)entityptr + POSITION_OFFSET);

			if (current_entity_life > 0)
			{
				vector3 current_entity_position_on_screen;
				if (!GameFunctions::WorldToScreen(current_entity_position, *GameGlobals::view_matrix, current_entity_position_on_screen, GameGlobals::Screen.x, GameGlobals::Screen.y))
					continue;

				float dx = current_entity_position_on_screen.x - GameGlobals::ScreenCenter.x;
				float dy = current_entity_position_on_screen.y - GameGlobals::ScreenCenter.y;
				float dist = sqrtf(dx * dx + dy * dy);

				if (dist < 10.0f)
				{
					GameFunctions::ShootAction();
				}
			}
		}
		return true;
	}
	else
		return false;
	
}

void TriggerBot::SanityCheck()
{
	uintptr_t user_entity = Core::GameModuleBase + USER_ENTITY_ADDRESS;
	uintptr_t base_address = *(uintptr_t*)user_entity;
	if (!base_address) return;
	uintptr_t shoot_state = base_address + SHOOT_OFFSET;

	BYTE shootstate = *(BYTE*)shoot_state;
	
	GameFunctions::CurrentTimer = GetTickCount64();

	if (GameFunctions::isShooting && GameFunctions::CurrentTimer - GameFunctions::TickTimer >= 16 && GameFunctions::TickTimer > 0)
	{
		*(BYTE*)shoot_state = OFF;
		GameFunctions::TickTimer = 0;
		GameFunctions::isShooting = false;
	}
}
