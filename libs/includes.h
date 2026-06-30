#pragma once

//std libs
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<list>
#include<thread>
#include<map>
#include<numbers>
#include<algorithm>




//winapi
#include<WinSock2.h>
#include <WS2tcpip.h>  
#pragma comment(lib, "Ws2_32.lib")

#include<Windows.h>
#include<WinUser.h>


//utils
//#include"../structures/utils.h"

//reversed structures
//#include"../structures/sdl.h"
//#include"../structures/sauerbraten.h"
//#include"../classes/player.h"
//  trouble in this part, need to find out whatssss is gooing on here

//imgui part
//#include "../libs/imgui/imgui_impl_opengl3_loader.h"
#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_win32.h"
//#include "../libs/imgui/imgui_impl_win32.h"
#include "../libs/imgui/imgui_impl_opengl3.h"
#include "../libs/imgui/imgui_impl_opengl2.h"
#include "../libs/imgui/imgui_impl_win32.h"

//#include "../libs/imgui/imgui_impl_opengl2.h"
//
////minhook
#include "../libs/minhook/MinHook.h"


//my classes
//#include"../classes/gameinfo.h"
//#include"../classes/player.h"


//gui
//#include"../gui/gui.h"
#include<gl/gl.h>
#include<gl/glu.h>

//functions
//#include"../functions/memory.h"

//hacks
//#include"../classes/functions.h"

//opengl
#include <gl\GL.h>



// new part archtectured project

//game offsets
#include"../game/game_offsets.h"

//core
#include"../core/event_bus.h"

//game
#include"../game/structures.h"

//render
#include"../render/render.h"

//game globals
#include"../game/globals.h"

//memory
#include"../memory/mem.h"

//features 
#include"../features/esc_feature.h"
#include"../features/super_jmp.h"
#include"../features/trigger_bot.h"
#include"../features/aim_bot.h"
#include"../game/functions.h"
#include"../features/esp.h"

// needs to be at the bottom due to loading everything else 
#include"../core/feature_manager.h"

// core - needs to be here to be compiled
#include"../core/core_state.h"