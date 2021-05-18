#pragma once
#include <Windows.h>
#include <TP\glad\glad.h>
#include "GlHelper.h"
#include "GlProcess.h"

#define RUN_WITHOUT_NINSDK

#define nnMain main

#define DEFAULT_WIDTH   (1920)
#define DEFAULT_HEIGHT  (1080)

bool InitSystem(
    int width = DEFAULT_WIDTH,
    int height = DEFAULT_HEIGHT,
    const char* title = nullptr);

void UninitSystem();

void SwapBuffers();

bool ShouldQuit();

GlHelper* GetGlHelperPtr();

void SetVertexAttr(const VERTEX* v, int arraySize);
