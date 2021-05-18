#pragma once
#include <TP\glad\glad.h>

#define RUN_WITHOUT_NINSDK

#define DEFAULT_WIDTH   (1920)
#define DEFAULT_HEIGHT  (1080)

bool InitSystem(
    int width = DEFAULT_WIDTH,
    int height = DEFAULT_HEIGHT,
    const char* title = nullptr);

void UninitSystem();

void SwapBuffers();

bool ShouldQuit();
