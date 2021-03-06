#include "main.h"
#include <iostream>

GlHelper* gp_GlHelper = nullptr;

bool InitSystem(int width, int height, const char* title)
{
    if (!InitGlAndCreateWindow(width, height, title))
    {
        std::cout << "failed to init basic" << std::endl;
        return false;
    }

    gp_GlHelper = new GlHelper();
    if (!gp_GlHelper->StartUp())
    {
        std::cout << "failed to init gl" << std::endl;
        delete gp_GlHelper;
        gp_GlHelper = nullptr;
        return false;
    }

    return true;
}

void UninitSystem()
{
    TerminateGLFW();
}

float SwapBuffers()
{
    float timer = GoRunLoopProcess();
    gp_GlHelper->ClearVaoVbo();

    return timer;
}

bool ShouldQuit()
{
    return ShouldGlfwQuit();
}

GlHelper* GetGlHelperPtr()
{
    return gp_GlHelper;
}

void SetVertexAttr(const VERTEX* v, int arraySize)
{
    int bufferSize = 9 * arraySize;
    float* buffer = new float[bufferSize];
    GLuint* vao = new GLuint;
    GLuint* vbo = new GLuint;
    GetGlHelperPtr()->MoveDataToBuffer(
        v, arraySize, buffer);
    GetGlHelperPtr()->BindVAOWithVBO(vao, vbo,
        buffer, bufferSize);
    glBindVertexArray(*vao);
    delete vao, vbo;
    delete[] buffer;
}
