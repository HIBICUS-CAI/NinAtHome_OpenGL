#pragma once

#include <TP\glad\glad.h>
#include <TP\glfw\glfw3.h>

GLFWwindow* GetGlfwWndHandle();

bool InitGlAndCreateWindow(
    int width, int height, const char* title);

void ProcessInput(GLFWwindow* wndHandle);

void TerminateGLFW();

void ResizeCallback(
    GLFWwindow* wndHandle, int width, int height);

void GoRunLoopProcess();

bool ShouldGlfwQuit();
