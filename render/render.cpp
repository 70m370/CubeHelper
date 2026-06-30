#include"../libs/includes.h"
#include"../game/structures.h"

namespace Render
{
	float RedPen[] = { 1.0f, 0.0f, 0.0f };
	float GreenPen[] = { 0.0f, 1.0f,0.0f };
	float BluePen[] = { 0.0f, 0.0f,1.0f };
	float WhitePen[] = { 1.0f, 1.0f, 1.0f };

}


void Render::Setup()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, viewport[2], viewport[3]);

	Render::window_width = viewport[2];
	Render::window_height = viewport[3];

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
}

void Render::Restore()
{
	glPopMatrix();
	glPopAttrib();
}

//
// local variables 
typedef BOOL(WINAPI* WswapBuffers_t)(HDC);
WswapBuffers_t oSwapBuffers = nullptr;

bool g_ImguiInitialized = false;

TriggerBot triggerbot;

//local func
bool SwapbuffersHook(HDC hdc)
{
	const auto old_ctx = wglGetCurrentContext();
	const auto old_hdc = wglGetCurrentDC();
	const auto old_index = GetPixelFormat(hdc);

	if (!Render::contexts.count(old_index))
	{
		auto ctx = wglCreateContext(hdc);
		wglMakeCurrent(hdc, ctx);
		wglMakeCurrent(old_hdc, old_ctx);
		Render::contexts[old_index] = ctx;
	}

	wglMakeCurrent(hdc, Render::contexts[old_index]);

	if (!g_ImguiInitialized)
	{
		Render::g_hdc = hdc;
		Render::g_hwnd = WindowFromDC(hdc);

		Render::InternalMenu::Start(Render::g_hwnd, Render::g_hdc);
		g_ImguiInitialized = true;
	}

	Render::Setup();

	//
	// rendering functions that are called everyframe
	GameGlobals::UpdateValues();
	Core::g_Features.UpdateAll();

	Render::Restore();

	wglMakeCurrent(old_hdc, old_ctx);

	Render::InternalMenu::RenderImGuiUI(Render::event_bus);


	return oSwapBuffers(hdc);
}


bool Render::init()
{
	HMODULE hOpenGl = GetModuleHandleA("opengl32.dll");
	FARPROC pSwapBuffers = GetProcAddress(hOpenGl, "wglSwapBuffers");

	if (MH_Initialize() != MH_OK && MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED)
	{
		printf("Failed to Initiliaze minhook\n");
		return false;
	}

	if (MH_CreateHook(pSwapBuffers, &SwapbuffersHook, reinterpret_cast<void**>(&oSwapBuffers)) != MH_OK)
	{
		printf("failed to create swapbuffers hook \n");
		return false;
	}

	if (MH_EnableHook(pSwapBuffers) != MH_OK)
	{
		printf("failed to enable swapbuffers hook\n");
		return false;
	}

	return true;
}

void Render::DrawLine(int start_x, int start_y, int end_x, int end_y, float color[])
{
	glLineWidth(1.0);
	glBegin(GL_LINES);
	glColor3f(color[0], color[1], color[2]);
	glVertex2f(start_x, start_y);
	glVertex2f(end_x, end_y);
	glEnd();
}

void Render::DrawCircle(vector2 position, float radius, float color[])
{
	float theta;
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_LINE_STRIP);

	for (int i = 0; i < 360; i++)
	{
		theta = i * std::numbers::pi_v<float> / 180;
		glVertex2f(position.x + radius * cos(theta), position.y + (radius * sin(theta)));
	}
	glEnd();
}

void Render::InternalMenu::RenderImGuiUI(EventBus* bus)
{

    //start imgui new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Cube Helper");
    ImGui::SetWindowSize(ImVec2(400, 250));

    if (ImGui::BeginChild(1))
    {

		static bool mark_check_1 = false;
	
		static bool mark_check_2 = false;
		static bool mark_check_3 = false;
		static bool mark_check_4 = false;
	
	
		ImGui::TextLink("\nESC to enable cursor\n");
		
		if (GetAsyncKeyState(VK_ESCAPE) & 1)
			bus->Publish(EventType::PressEsc);

		if (ImGui::Checkbox("super jump", &mark_check_1))
			bus->Publish(EventType::ToggleSuperJmp);

		ImGui::Spacing();

		if (ImGui::Checkbox("TriggerBot", &mark_check_2))
			bus->Publish(EventType::ToggleTriggerBot);

		ImGui::Spacing();

		if (ImGui::Checkbox("AimBot", &mark_check_3))
			bus->Publish(EventType::ToggleAimbot);

		if (ImGui::Checkbox("ESP", &mark_check_4))
			bus->Publish(EventType::ToggleEsp);



		ImGui::Spacing();

		ImGui::Bullet();
		if (ImGui::Button("Eject"))
			bus->Publish(EventType::Exit);

		ImGui::Spacing();

		ImGui::EndChild();
	}
	ImGui::End();

	//render

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// both start and destroy should be void ? 
bool Render::InternalMenu::Start(HWND hwnd, HDC hdc)
{
	//imgui initialization
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// can be StyleColorsDark etc
	ImGui::StyleColorsDark();

	//initialize imgui opengl and win32
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplOpenGL3_Init(nullptr);

	return true;
}


bool Render::InternalMenu::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	return true;
}


/// <WINDOWS SECTION>
/// 
///		This Section is for Windows API callback functions or implementations for 
///		procedures or functions flows
/// 

static WNDPROC oWndProc = nullptr;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc_H(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
		return 0;

	// Call the original WndProc for unhandled messages
	return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}

bool Windows::ImGuiWndProc()
{
	HWND target_window = FindWindow(NULL, L"Cube 2: Sauerbraten");
	if (!target_window) {
		printf("Failed to retrieve valid game window!\n");
		return false;
	}

	oWndProc = (WNDPROC)GetWindowLongPtr(target_window, GWLP_WNDPROC);

	if (!oWndProc) {
		printf("Failed to retrieve original WndProc! and the right window\n");
		return false;
	}

	SetWindowLongPtr(target_window, GWLP_WNDPROC, (LONG_PTR)WndProc_H);
	return true;
}

void Windows::ReleaseImGuiWndProc()
{
	HWND target_window = FindWindow(NULL,L"Cube 2: Sauerbraten");
	SetWindowLongPtr(target_window, GWLP_WNDPROC, (LONG_PTR)oWndProc);
}
