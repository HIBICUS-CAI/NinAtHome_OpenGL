#include "GlProcess.h"
#include <iostream>
#include "main.h"

GLFWwindow* gp_WndHandle = nullptr;

bool g_ClearMouseBtn = false;
bool g_ClickingMouseLeft = false;
int g_CursorPosX = 0;
int g_CursorPosY = 0;

bool g_IsUsingLeftAngleSensor = false;
float g_AngleX[2] = { 0.f,0.f };
float g_AngleY[2] = { 0.f,0.f };
float g_AngleZ[2] = { 0.f,0.f };

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

float GetAngleX(int padIndex)
{
    if (padIndex == LEFT_ANGLE || padIndex == RIGHT_ANGLE)
    {
        return g_AngleX[padIndex];
    }
    else
    {
        return 0.f;
    }
}

float GetAngleY(int padIndex)
{
    if (padIndex == LEFT_ANGLE || padIndex == RIGHT_ANGLE)
    {
        return g_AngleY[padIndex];
    }
    else
    {
        return 0.f;
    }
}

float GetAngleZ(int padIndex)
{
    if (padIndex == LEFT_ANGLE || padIndex == RIGHT_ANGLE)
    {
        return g_AngleZ[padIndex];
    }
    else
    {
        return 0.f;
    }
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

    if (glfwGetKey(wndHandle, GLFW_KEY_LEFT_BRACKET) ==
        GLFW_PRESS)
    {
        g_IsUsingLeftAngleSensor = true;
    }
    if (glfwGetKey(wndHandle, GLFW_KEY_RIGHT_BRACKET) ==
        GLFW_PRESS)
    {
        g_IsUsingLeftAngleSensor = false;
    }
    if (glfwGetKey(wndHandle, GLFW_KEY_F1) == GLFW_PRESS)
    {
        for (int i = 0; i < 2; i++)
        {
            g_AngleX[i] = 0.f;
            g_AngleY[i] = 0.f;
            g_AngleZ[i] = 0.f;
        }
    }
    // TODO need to check whether this is correct or not
    if (glfwGetKey(wndHandle, GLFW_KEY_I) == GLFW_PRESS)
    {
        if (g_IsUsingLeftAngleSensor)
        {
            g_AngleX[LEFT_ANGLE] += 0.01f;
        }
        else
        {
            g_AngleX[RIGHT_ANGLE] += 0.01f;
        }
    }
    if (glfwGetKey(wndHandle, GLFW_KEY_K) == GLFW_PRESS)
    {
        if (g_IsUsingLeftAngleSensor)
        {
            g_AngleX[LEFT_ANGLE] -= 0.01f;
        }
        else
        {
            g_AngleX[RIGHT_ANGLE] -= 0.01f;
        }
    }
    if (glfwGetKey(wndHandle, GLFW_KEY_J) == GLFW_PRESS)
    {
        if (g_IsUsingLeftAngleSensor)
        {
            g_AngleY[LEFT_ANGLE] += 0.01f;
        }
        else
        {
            g_AngleY[RIGHT_ANGLE] += 0.01f;
        }
    }
    if (glfwGetKey(wndHandle, GLFW_KEY_L) == GLFW_PRESS)
    {
        if (g_IsUsingLeftAngleSensor)
        {
            g_AngleY[LEFT_ANGLE] -= 0.01f;
        }
        else
        {
            g_AngleY[RIGHT_ANGLE] -= 0.01f;
        }
    }
    if (glfwGetKey(wndHandle, GLFW_KEY_U) == GLFW_PRESS)
    {
        if (g_IsUsingLeftAngleSensor)
        {
            g_AngleZ[LEFT_ANGLE] += 0.01f;
        }
        else
        {
            g_AngleZ[RIGHT_ANGLE] += 0.01f;
        }
    }
    if (glfwGetKey(wndHandle, GLFW_KEY_O) == GLFW_PRESS)
    {
        if (g_IsUsingLeftAngleSensor)
        {
            g_AngleZ[LEFT_ANGLE] -= 0.01f;
        }
        else
        {
            g_AngleZ[RIGHT_ANGLE] -= 0.01f;
        }
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
