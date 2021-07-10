#pragma once

#include <Windows.h>

HWND GetWndHandle();

bool CreateWndAndInitInput(HINSTANCE hInstance, int cmdShow);

float GoRunLoopProcess();

bool ShouldWndQuit();
