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
#include "controller.h"

RootSystem::RootSystem() :
    mSceneManagerPtr(nullptr), mPropertyManagerPtr(nullptr),
    mObjectFactoryPtr(nullptr), mLastTime(0.f), mDeltaTime(0.16f)
{

}

RootSystem::~RootSystem()
{

}

bool RootSystem::StartUp(HINSTANCE hInstance, int cmdShow)
{
    MY_NN_LOG(LOG_MESSAGE,
        "[START UP] : starting up ROOT SYSTEM\n");

    mSceneManagerPtr = new SceneManager();
    mPropertyManagerPtr = new PropertyManager();
    mObjectFactoryPtr = new ObjectFactory();

    bool result = InitSystem(hInstance, cmdShow);

    result = mSceneManagerPtr->StartUp();
    result = mPropertyManagerPtr->StartUp();
    result = mObjectFactoryPtr->StartUp(
        mPropertyManagerPtr, mSceneManagerPtr);
    mSceneManagerPtr->PostStartUp(
        mPropertyManagerPtr, mObjectFactoryPtr);

    InitController();

    if (result)
    {
        MY_NN_LOG(LOG_MESSAGE,
            "[START UP] : start up ROOT SYSTEM successed\n");
    }
    else
    {
        MY_NN_LOG(LOG_ERROR,
            "[START UP] : start up ROOT SYSTEM failed\n");
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

    UninitController();

    UninitSystem();

    MY_NN_LOG(LOG_MESSAGE,
        "[CLEAN STOP] : stop ROOT SYSTEM successed\n");
}

void RootSystem::RunGameLoop()
{
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            GetDxHelperPtr()->ClearBuffer();

            UpdateController();

            mSceneManagerPtr->UpdateSceneManager(mDeltaTime);

            SwapAndClacDeltaTime();

            if (ShouldQuit())
            {
                PostQuitMessage(0);
            }
        }
    }
}

void RootSystem::SwapAndClacDeltaTime()
{
    float time = 0.f;
#ifdef NIN_AT_HOME
    time = SwapBuffers();
#else
    SwapBuffers();
    nn::os::Tick t = nn::os::GetSystemTick();
    time = (float)(t.ToTimeSpan().GetMilliSeconds()) / 1000.f;
#endif // NIN_AT_HOME
    mDeltaTime = time - mLastTime;
    mLastTime = time;
    time = MAX_DELTA - mDeltaTime;
    //NN_LOG("current delta : %f , delta with max %f\n",
        //mDeltaTime, time);
    if (time > 0.001f)
    {
        mLastTime += time;
#ifdef NIN_AT_HOME
        Sleep((int)(1000.f * time));
#else

#endif // NIN_AT_HOME
        mDeltaTime = MAX_DELTA;
    }
    else if (time < 0.f)
    {
        mDeltaTime = MAX_DELTA;
    }
    //NN_LOG("final delta : %f\n", mDeltaTime);
}
