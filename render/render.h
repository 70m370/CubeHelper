#pragma once
//#include"../libs/includes.h"

namespace Windows {
	bool ImGuiWndProc();
	void ReleaseImGuiWndProc();
	
}

namespace Render {

	//
	// Open GL Section

	//
	// Global Variables
	inline HWND g_hwnd;
	inline HDC g_hdc;

	inline std::map<int, HGLRC> contexts;
	inline int window_width;
	inline int window_height;

	inline EventBus* event_bus;

	//
	// OpenGl functions
	void Setup();
	void Restore();

	//
	//
	bool init();

	//
	// Drawn
	void DrawLine(int start_x, int start_y, int end_x, int end_y, float color[]);
	void DrawCircle(vector2 position, float radius, float color[]);

	//
	// Colors 
	extern float RedPen[];
	extern float GreenPen[];
	extern float BluePen[];
	extern float WhitePen[];

	namespace InternalMenu {
		bool Start(HWND hwnd, HDC hdc);
		void RenderImGuiUI(EventBus* bus);
		bool Destroy();
	}
}