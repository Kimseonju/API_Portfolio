#include <EngineBasePublic.h>
#include <EnginePlatformPublic.h>
#include <EngineClientPublic.h>
#include <EngineWindow.h>
#include <EngineDebug.h>
#include <Windows.h>

#include "Core.h"
int __stdcall wWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR    lpCmdLine,
    int       nCmdShow)
{
    EngineDebug::LeakCheck();
    EngineWindow::CreateGameEngineWindow(hInstance, L"Binding of Isaac: Rebirth", { 100, 100 }, { 960, 540 });
   

    EngineWindow::Loop<Core>();

    return 0;
}