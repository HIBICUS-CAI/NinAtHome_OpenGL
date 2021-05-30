#pragma once

#include <TP\glad\glad.h>
#include <TP\glfw\glfw3.h>

GLFWwindow* GetGlfwWndHandle();

bool InitGlAndCreateWindow(
    int width, int height, const char* title);

void ProcessInput(GLFWwindow* wndHandle);

void TerminateGLFW();

void GoRunLoopProcess();

bool ShouldGlfwQuit();
