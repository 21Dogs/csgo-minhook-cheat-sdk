#include <Windows.h>
#include <thread>

#include "hooks.hpp"

unsigned long WINAPI DllThread(void* instance)
{
    while (!GetModuleHandleA("serverbrowser.dll")) 
        Sleep(200);

    interfaces::g_VGuiPanel = reinterpret_cast<IPanel*>(tools::captureInterface("vgui2.dll", "VGUI_Panel"));
    interfaces::g_VGuiSurface = reinterpret_cast<ISurface*>(tools::captureInterface("vguimatsurface.dll", "VGUI_Surface"));

    const auto PaintTraverseTarget = reinterpret_cast<void*>(tools::createVirtual(interfaces::g_VGuiPanel, 41));

    if (MH_Initialize() != MH_OK)
        throw std::runtime_error("failed to initialize MH_Initialize.");

    if (MH_CreateHook(PaintTraverseTarget, &hooks::PaintTraverseHk, reinterpret_cast<void**>(&originalPaintTraverse)) != MH_OK)
        throw std::runtime_error("failed to initialize paint_traverse. (outdated index?)");

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
        throw std::runtime_error("failed to enable hooks.");

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
}

void __stdcall hooks::PaintTraverseHk(unsigned int panel, bool forceRepaint, bool allowForce) {

    originalPaintTraverse(interfaces::g_VGuiPanel, panel, forceRepaint, allowForce);

    if (!strcmp("FocusOverlayPanel", interfaces::g_VGuiPanel->GetName(panel))) //MatSystemTopPanel
    {
        //render here
    }
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved)  // reserved
{
    DisableThreadLibraryCalls(hinstDLL);
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        //CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)DllThread, hinstDLL, NULL, nullptr);
        if (auto handle = CreateThread(nullptr, NULL, DllThread, hinstDLL, NULL, nullptr))
            CloseHandle(handle);
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:
        // Perform any necessary cleanup.
        FreeLibraryAndExitThread(hinstDLL, TRUE);
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}