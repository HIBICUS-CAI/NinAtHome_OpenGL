#pragma once

#include <stdio.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN (1)
#endif // !WIN32_LEAN_AND_MEAN

#include <Windows.h>

#define LOG_MESSAGE             (0)
#define LOG_WARNING             (1)
#define LOG_ERROR               (2)

// FOR SETTING ------------------------------
#define LOG_LEVEL_FOR_SETTING   (LOG_MESSAGE)

#define LOG_TO_VS
// FOR SETTING ------------------------------

#ifdef LOG_TO_VS
#define NN_LOG DebugPrintF
#else
#define NN_LOG MyPrintF
#endif // LOG_TO_VS

int DebugPrintF(int level, const char* format, ...);

int MyPrintF(int level, const char* format, ...);

