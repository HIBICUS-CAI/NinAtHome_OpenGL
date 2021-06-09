//---------------------------------------------------------------
// File: RootSystem.h
// Proj: NinAtHome
// Info: �����ƥ��ȫ��Ĥ˹�����
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

class RootSystem
{
public:
    RootSystem();
    ~RootSystem();

    bool StartUp();

    void ClearAndStop();

    void RunGameLoop();

private:
    class SceneManager* mSceneManagerPtr;

    class PropertyManager* mPropertyManagerPtr;

    class ObjectFactory* mObjectFactoryPtr;
};

