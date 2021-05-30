#include "GlProcess.h"
#include <iostream>

GLFWwindow* gp_WndHandle = nullptr;

void ResizeCallback(
    GLFWwindow* wndHandle, int width, int height);

GLFWwindow* GetGlfwWndHandle()
{
    return gp_WndHandle;
}

bool InitGlAndCreateWindow(
    int width, int height, const char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    if (!title)
    {
        gp_WndHandle = glfwCreateWindow(
            width, height, "default title", nullptr, nullptr);
    }
    else
    {
        gp_WndHandle = glfwCreateWindow(
            width, height, title, nullptr, nullptr);
    }
    
    if (!gp_WndHandle)
    {
        std::cout << "failed to create glfw wnd" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(gp_WndHandle);
    glfwSetFramebufferSizeCallback(gp_WndHandle, ResizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "failed to init glad" << std::endl;
        return false;
    }
    else
    {
        glViewport(0, 0, width, height);
    }

    return true;
}

void ProcessInput(GLFWwindow* wndHandle)
{
    if (glfwGetKey(wndHandle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(wndHandle, true);
    }
}

void TerminateGLFW()
{
    glfwTerminate();
}

void ResizeCallback(
    GLFWwindow* wndHandle, int width, int height)
{
    glViewport(0, 0, width, height);
}

void GoRunLoopProcess()
{
    ProcessInput(gp_WndHandle);

    glfwPollEvents();
    glfwSwapBuffers(gp_WndHandle);
}

bool ShouldGlfwQuit()
{
    return glfwWindowShouldClose(gp_WndHandle);
}
