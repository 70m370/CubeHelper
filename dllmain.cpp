#include "../CubeHelper/libs/includes.h"


DWORD64 Main(HMODULE hModule)
{
    FILE* f;

    AllocConsole();

    freopen_s(&f, "CONOUT$","w", stdout);

    AddVectoredExceptionHandler(TRUE, Core::ExceptionHandler);


    Core::FileBuffer = f;
    Core::hModule = hModule;
    

    if (!Core::init())
    {
        MessageBoxA(NULL,"Core::Init Failed, ejecting", NULL, NULL);
        Core::Eject();
        return 0;
    }
        

    Core::g_EventBus.Subscribe(&Core::g_Features);
    Render::event_bus = &Core::g_EventBus;

   
    //
    // how i'm handling the eject method - needs an update
    while (true)
    {
        if (Core::exitswitch)
            break;
        Sleep(10);
    }

    Core::Eject();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Main, hModule, 0, nullptr));
    }
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
};

