#pragma once
#include <Windows.h>
#include "DxHelper.h"
#include "DxProcess.h"
#include <math.h>
#include "NinLog.h"

#define NIN_AT_HOME

#define nnMain WinMain

#define DEFAULT_WIDTH   (1920)
#define DEFAULT_HEIGHT  (1080)
#define SCREEN_WIDTH    DEFAULT_WIDTH
#define SCREEN_HEIGHT   DEFAULT_HEIGHT

bool InitSystem(HINSTANCE hInstance, int cmdShow);

void UninitSystem();

float SwapBuffers();

bool ShouldQuit();

DxHelper* GetDxHelperPtr();

void SetVertexAttr(
    ID3D11Buffer* const* ppVertexBuffers,
    ID3D11Buffer* ppIndexBuffers);
