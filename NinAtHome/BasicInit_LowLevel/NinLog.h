#pragma once

#include <stdio.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN (1)
#endif // !WIN32_LEAN_AND_MEAN

#include <Windows.h>

#define LOG_TO_VS

#ifdef LOG_TO_VS
#define NN_LOG DebugPrintF
#else
#define NN_LOG printf
#endif // LOG_TO_VS

int DebugPrintF(const char* format, ...);

