#pragma once

#include <TP\glad\glad.h>
#include <TP\glfw\glfw3.h>

#define LEFT_ANGLE  (0)
#define RIGHT_ANGLE (1)

GLFWwindow* GetGlfwWndHandle();

bool InitGlAndCreateWindow(
    int width, int height, const char* title);

void ProcessInput(GLFWwindow* wndHandle);

void TerminateGLFW();

void GoRunLoopProcess();

bool ShouldGlfwQuit();

bool IsClickingMouseLeft();

int GetCursorPosX();

int GetCursorPosY();

float GetAngleX(int padIndex);

float GetAngleY(int padIndex);

float GetAngleZ(int padIndex);

int GetDeltaScroll(int padIndex);

int GetDeltaCursorX(int padIndex);

int GetDeltaCursorY(int padIndex);
