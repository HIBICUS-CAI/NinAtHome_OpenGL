//---------------------------------------------------------------
// File: SceneManager.h
// Proj: NinAtHome
// Info: ���`���������C�ܤΌ���
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include <array>
#include <string>

class SceneManager
{
public:
    SceneManager();
    ~SceneManager();

    bool StartUp();

    void CleanAndStop();

    void UpdateSceneManager();

    void LoadSceneNode(std::string _name, std::string _path);

    class PropertyManager* GetPropertyManager() const;

    class ObjectFactory* GetObjectFactory() const;

private:
    void LoadLoadingScene();

    void ReleaseLoadingScene();

    void LoadNextScene();

private:
    class PropertyManager* mPropertyManagerPtr;

    class ObjectFactory* mObjectFactoryPtr;

    class SceneNode* mLoadingScenePtr;

    class SceneNode* mCurrentScenePtr;

    class SceneNode* mNextScenePtr;

    bool mLoadSceneFlg;

    std::array<std::string, 2> mLoadSceneInfo;
};

