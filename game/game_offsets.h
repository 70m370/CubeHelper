#pragma once


//function addresses

#define SHOOT_FUNCTION_ADDRESS 0x1C7DC0
	//
	//	SHOOT_FUNCTION_ADDRESS binary signature
	//
	//\x80\x3d\x00\x00\x00\x00\x00\x74\x00\x80\x3d\x00\x00\x00\x00\x00\x75\x00\x48\x8b\x05 xx?????x?xx?????x?xxx

#define CURRENT_GAMEMODE_FUNCTION_ADDRESS 0x026F6B0
	//
	//	CURRENT_GAMEMODE_FUNCTION_ADDRESS binary signature
	//
	//\x0c\x00\x00\x00\x64\x00\x00 x?xxxxx 

#define CURRENT_MAP_FUNCTION_ADDRESS 0x1C7EA0
	//
	//	CURRENT_MAP_FUNCTION_ADDRESS binary signature
	//
	//\x48\x8d\x05\x00\x00\x00\x00\xc3\xcc\xcc\xcc\xcc\xcc\xcc\xcc\xcc\xb8\x00\x00\x00\x00\x3b\xc8 xxx????xxxxxxxxxx????xx

#define PROCESS_KEY_FUNCTION_ADDRESS 0x01A0260
	//
	//	PROCESS_KEY_FUNCTION_ADDRESS binary signature
	//
	//\x48\x89\x5c\x24\x00\x48\x89\x6c\x24\x00\x56\x48\x83\xec\x00\x8b\xd9 xxxx?xxxx?xxxx?xx

//addresses

#define ENTITIE_LIST_ADDRESS 0x346C90
#define USER_ENTITY_ADDRESS 0x2A5730
#define TOTAL_MAP_PLAYERS_ADDRESS 0x346C98
#define ACTIVE_PLAYERS_ADDRESS 0x346C9C
#define JUMP_HEIGHT_ADDRESS 0x2A5730 // same as user entity

//offsets

#define JUMP_HEIGHT_OFFSET 0x18

// Entity

#define POSITION_OFFSET 0x0
#define ANGLES_OFFSET 0x3C
#define STATE_OFFSET 0x77
#define LIFE_OFFSET 0x178
#define NAME_OFFSET 0x274
#define TEAM_OFFSET 0x378
#define SHOOT_OFFSET 0x1FC

//entity STATE_OFFSET
#define ALIVE_STATE 0x0
#define DEAD_STATE 0x01
#define EDIT_STATE 0x04
#define GHOST_STATE 0x05

//screen

#define SCREEN_X_OFFSET 0x2A3538
#define SCREEN_Y_OFFSET 0x2A3534
#define VIEW_MATRIX_OFFSET 0x32D040

//keys

#define SPACE_BAR 0x20

//SDL2.dll

#define SDL_FREECURSOR_ADDRESS 0x162AD8
	//
	// SDL_FREECURSOR_ADDRESS binary signature
	// 
	//\x48\x8b\x0d\x00\x00\x00\x00\x48\x39\xd9\x74\x00\x48\x85\xc9 xxx ? ? ? ? xxxx ? xxx

#define SDL_FREECURSOR_OFFSET 0x40

#define CURSOR_ENABLE 0x0000002A00000526
#define CURSOR_DISABLE 0X0000002A00000726



// VARIABLES 

#define ON 0x01
#define OFF 0x00