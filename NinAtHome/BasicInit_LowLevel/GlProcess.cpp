#include "GlProcess.h"
#include <iostream>
#include "main.h"

GLFWwindow* gp_WndHandle = nullptr;

bool g_ClearMouseBtn = false;
bool g_ClickingMouseLeft = false;
int g_CursorPosX = 0;
int g_CursorPosY = 0;

void ResizeCallback(
    GLFWwindow* wndHandle, int width, int height);
void MouseButtonCallback(
    GLFWwindow* wndHandle, int button, int action, int mods);
void CursorPositionCallback(
    GLFWwindow* wndHandle, double x, double y);
void ScrollCallback(GLFWwindow* wndHandle, double x, double y);

GLFWwindow* GetGlfwWndHandle()
{
    return gp_WndHandle;
}

bool IsClickingMouseLeft()
{
    return g_ClickingMouseLeft;
}

int GetCursorPosX()
{
    return g_CursorPosX;
}

int GetCursorPosY()
{
    return g_CursorPosY;
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
    glfwSetMouseButtonCallback(gp_WndHandle, MouseButtonCallback);
    glfwSetCursorPosCallback(gp_WndHandle, CursorPositionCallback);
    glfwSetScrollCallback(gp_WndHandle, ScrollCallback);

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
    if (glfwGetMouseButton(
        gp_WndHandle, GLFW_MOUSE_BUTTON_LEFT) ==
        GLFW_PRESS)
    {
        return;
    }
    if (g_ClearMouseBtn)
    {
        g_ClickingMouseLeft = false;
        g_ClearMouseBtn = false;
    }
    if (g_ClickingMouseLeft)
    {
        g_ClearMouseBtn = true;
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

void MouseButtonCallback(
    GLFWwindow* wndHandle, int button, int action, int mods)
{
    if (action == GLFW_PRESS) switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
        g_ClickingMouseLeft = true;
        break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        break;
    default:
        return;
    }
    return;
}

void CursorPositionCallback(
    GLFWwindow* wndHandle, double x, double y)
{
    g_CursorPosX = (int)x - (SCREEN_WIDTH / 2);
    g_CursorPosY = (int)y - (SCREEN_HEIGHT / 2);
}

void ScrollCallback(GLFWwindow* wndHandle, double x, double y)
{
    return;
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
