#include "DxProcess.h"
#include "WM_Interface.h"
#include "ID_Interface.h"

HWND g_WndHandle;
bool g_ShouldQuit = false;
ULONGLONG g_InitTime = 0;

HWND GetWndHandle()
{
    return g_WndHandle;
}

bool CreateWndAndInitInput(HINSTANCE hInstance, int cmdShow)
{
    if (!WindowInterface::StartUp())
    {
        return false;
    }
    if (!WindowInterface::CreateInitWindow("a test window",
        hInstance, cmdShow))
    {
        return false;
    }
    if (!InputInterface::StartUp())
    {
        return false;
    }

    g_ShouldQuit = false;
    g_InitTime = GetTickCount64();

    return true;
}

float GoRunLoopProcess()
{
    float timer = 0.f;
    timer = ((float)(GetTickCount64() - g_InitTime)) / 1000.f;

    if (InputInterface::IsKeyPushedInSingle(KB_ESCAPE))
    {
        g_ShouldQuit = true;
    }

    return timer;
}

bool ShouldWndQuit()
{
    return g_ShouldQuit;
}
