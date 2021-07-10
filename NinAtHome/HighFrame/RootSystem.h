//---------------------------------------------------------------
// File: RootSystem.h
// Proj: NinAtHome
// Info: システムを全体的に管理する
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "HFCommon.h"

class RootSystem
{
public:
    RootSystem();
    ~RootSystem();

    bool StartUp(HINSTANCE hInstance, int cmdShow);

    void ClearAndStop();

    void RunGameLoop();

private:
    void SwapAndClacDeltaTime();

private:
    class SceneManager* mSceneManagerPtr;

    class PropertyManager* mPropertyManagerPtr;

    class ObjectFactory* mObjectFactoryPtr;

    float mLastTime;

    float mDeltaTime;
};

