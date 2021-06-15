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
#include "ObjectFactory.h"
#include "main.h"

RootSystem::RootSystem() :
    mSceneManagerPtr(nullptr), mPropertyManagerPtr(nullptr),
    mObjectFactoryPtr(nullptr), mLastTime(0.f), mDeltaTime(0.16f)
{

}

RootSystem::~RootSystem()
{

}

bool RootSystem::StartUp()
{
    NN_LOG("[START UP] : starting up ROOT SYSTEM\n");

    mSceneManagerPtr = new SceneManager();
    mPropertyManagerPtr = new PropertyManager();
    mObjectFactoryPtr = new ObjectFactory();

    bool result = InitSystem();

    result = mSceneManagerPtr->StartUp();
    result = mPropertyManagerPtr->StartUp();
    result = mObjectFactoryPtr->StartUp(
        mPropertyManagerPtr, mSceneManagerPtr);
    mSceneManagerPtr->PostStartUp(
        mPropertyManagerPtr, mObjectFactoryPtr);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glFrontFace(GL_CCW);

    if (result)
    {
        NN_LOG("[START UP] : start up ROOT SYSTEM successed\n");
    }
    else
    {
        NN_LOG("[START UP] : start up ROOT SYSTEM failed\n");
    }

    return result;
}

void RootSystem::ClearAndStop()
{
    if (mSceneManagerPtr)
    {
        mSceneManagerPtr->CleanAndStop();
        delete mSceneManagerPtr;
        mSceneManagerPtr = nullptr;
    }
    if (mPropertyManagerPtr)
    {
        mPropertyManagerPtr->CleanAndStop();
        delete mPropertyManagerPtr;
        mPropertyManagerPtr = nullptr;
    }
    if (mObjectFactoryPtr)
    {
        mObjectFactoryPtr->CleanAndStop();
        delete mObjectFactoryPtr;
        mObjectFactoryPtr = nullptr;
    }

    UninitSystem();

    NN_LOG("[CLEAN STOP] : stop ROOT SYSTEM successed\n");
}

void RootSystem::RunGameLoop()
{
    while (true)
    {
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mSceneManagerPtr->UpdateSceneManager(mDeltaTime);

        SwapAndClacDeltaTime();

        if (ShouldQuit())
        {
            break;
        }
    }
}

void RootSystem::SwapAndClacDeltaTime()
{
    float time = SwapBuffers();
    mDeltaTime = time - mLastTime;
    mLastTime = time;
    time = MAX_DELTA - mDeltaTime;
    //NN_LOG("current delta : %f , delta with max %f\n",
        //mDeltaTime, time);
    if (time > 0.001f)
    {
        mLastTime += time;
        Sleep((int)(1000.f * time));
        mDeltaTime = MAX_DELTA;
    }
    else if (time < 0.f)
    {
        mDeltaTime = MAX_DELTA;
    }
    //NN_LOG("final delta : %f\n", mDeltaTime);
}
