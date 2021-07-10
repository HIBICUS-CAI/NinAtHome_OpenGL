#include "main.h"
#include <iostream>

DxHelper* gp_DxHelper = nullptr;

bool InitSystem(HINSTANCE hInstance, int cmdShow)
{
    if (!CreateWndAndInitInput(hInstance, cmdShow))
    {
        std::cout << "failed to create wnd input" << std::endl;
        return false;
    }

    gp_DxHelper = new DxHelper();
    if (FAILED((gp_DxHelper->StartUp(GetWndHandle()))))
    {
        std::cout << "failed to init dx" << std::endl;
        delete gp_DxHelper;
        gp_DxHelper = nullptr;
        return false;
    }

    return true;
}

void UninitSystem()
{
    gp_DxHelper->CleanAndStop();
}

float SwapBuffers()
{
    float timer = GoRunLoopProcess();

    gp_DxHelper->SwapBufferChain();

    return timer;
}

bool ShouldQuit()
{
    return ShouldWndQuit();
}

DxHelper* GetDxHelperPtr()
{
    return gp_DxHelper;
}

void SetVertexAttr(
    ID3D11Buffer* const* ppVertexBuffers,
    ID3D11Buffer* ppIndexBuffers)
{
    gp_DxHelper->BindVertexIndexBuffer(
        ppVertexBuffers, ppIndexBuffers);
}
