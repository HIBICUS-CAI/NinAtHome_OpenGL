#pragma once
#include <Windows.h>
#include <TP\glad\glad.h>
#include "GlHelper.h"
#include "GlProcess.h"
#include <math.h>
#include "NinLog.h"

#define NIN_AT_HOME

#define nnMain main

#define DEFAULT_WIDTH   (1920)
#define DEFAULT_HEIGHT  (1080)
#define SCREEN_WIDTH    DEFAULT_WIDTH
#define SCREEN_HEIGHT   DEFAULT_HEIGHT

bool InitSystem(
    int width = DEFAULT_WIDTH,
    int height = DEFAULT_HEIGHT,
    const char* title = nullptr);

void UninitSystem();

float SwapBuffers();

bool ShouldQuit();

GlHelper* GetGlHelperPtr();

void SetVertexAttr(const VERTEX* v, int arraySize);
