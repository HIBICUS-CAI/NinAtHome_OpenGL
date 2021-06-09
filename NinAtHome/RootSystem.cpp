//---------------------------------------------------------------
// File: RootSystem.cpp
// Proj: NinAtHome
// Info: システムを全体的に管理する
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "RootSystem.h"
#include "SceneManager.h"
#include "PropertyManager.h"
#include "main.h"

RootSystem::RootSystem() :
    mpSceneManager(nullptr), mpPropertyManager(nullptr)
{

}

RootSystem::~RootSystem()
{

}

bool RootSystem::StartUp()
{
    mpSceneManager = new SceneManager();
    mpPropertyManager = new PropertyManager();

    bool result = InitSystem();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glFrontFace(GL_CCW);

    return result;
}

void RootSystem::ClearAndStop()
{
    if (mpSceneManager)
    {
        delete mpSceneManager;
        mpSceneManager = nullptr;
    }
    if (mpPropertyManager)
    {
        delete mpPropertyManager;
        mpPropertyManager = nullptr;
    }

    UninitSystem();
}

void RootSystem::RunGameLoop()
{
    // TEMP------------------
    while (true)
    {
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SwapBuffers();
        if (ShouldQuit())
        {
            break;
        }
        static short t = 0;
        NN_LOG("running game loop : [%d]\n", t++);
    }
    // TEMP------------------
}
