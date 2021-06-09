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

extern "C" int nnMain()
{
    if (g_RootSystem.StartUp())
    {
        g_RootSystem.RunGameLoop();
    }

    g_RootSystem.ClearAndStop();

    return 0;
}
