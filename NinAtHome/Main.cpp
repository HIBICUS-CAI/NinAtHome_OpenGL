//---------------------------------------------------------------
// File: main.cpp
// Proj: NinAtHome
// Info: 入口ファイル
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "main.h"
#include "RootSystem.h"

RootSystem g_RootSystem = {};

extern "C" int nnMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR szCmdLine,
    _In_ int iCmdShow
)
{
    if (g_RootSystem.StartUp(hInstance, iCmdShow))
    {
        g_RootSystem.RunGameLoop();
    }

    g_RootSystem.ClearAndStop();

    return 0;
}
