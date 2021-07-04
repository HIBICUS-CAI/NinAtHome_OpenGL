﻿//---------------------------------------------------------------
// File: SceneManager.cpp
// Proj: NinAtHome
// Info: シーン管理する機能の対応
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "SceneManager.h"
#include "SceneNode.h"
#include "PropertyManager.h"
#include "ObjectFactory.h"
#include <thread>
#include "controller.h"

SceneManager::SceneManager() :
    mPropertyManagerPtr(nullptr), mObjectFactoryPtr(nullptr),
    mLoadingScenePtr(nullptr), mCurrentScenePtr(nullptr),
    mNextScenePtr(nullptr), mLoadSceneFlg(false),
    mLoadSceneInfo({ "","" }), mScenePool({ nullptr,nullptr }),
    mReleaseScenePtr(nullptr)
{

}

SceneManager::~SceneManager()
{

}

bool SceneManager::StartUp()
{
    bool result = true;

    return result;
}

void SceneManager::PostStartUp(PropertyManager* _pmPtr,
    ObjectFactory* _ofPtr)
{
    mPropertyManagerPtr = _pmPtr;
    mObjectFactoryPtr = _ofPtr;

    LoadLoadingScene();

    LoadSceneNode(
        "title-scene",
        "rom:/Configs/Scenes/title-scene.json");
}

void SceneManager::CleanAndStop()
{
    mCurrentScenePtr->ReleaseScene();
    delete mCurrentScenePtr;

    if (mNextScenePtr)
    {
        mNextScenePtr->ReleaseScene();
        delete mNextScenePtr;
    }

    if (mCurrentScenePtr != mLoadingScenePtr)
    {
        ReleaseLoadingScene();
        delete mLoadingScenePtr;
    }
}

void SceneManager::UpdateSceneManager(float _deltatime)
{
    if (mLoadSceneFlg)
    {
        mLoadSceneFlg = false;

        mCurrentScenePtr = mLoadingScenePtr;
        std::thread loadThread(
            &SceneManager::LoadNextScene, this);
        loadThread.detach();
    }

    if (mReleaseScenePtr)
    {
        mReleaseScenePtr->ReleaseScene();
        delete mReleaseScenePtr;
        mReleaseScenePtr = nullptr;
    }

    if (mNextScenePtr)
    {
        mCurrentScenePtr = mNextScenePtr;
        mNextScenePtr = nullptr;
    }

    mCurrentScenePtr->UpdateScene(_deltatime);
    mCurrentScenePtr->DrawScene();
}

PropertyManager* SceneManager::GetPropertyManager() const
{
    return mPropertyManagerPtr;
}

ObjectFactory* SceneManager::GetObjectFactory() const
{
    return mObjectFactoryPtr;
}

void SceneManager::LoadSceneNode(
    std::string _name, std::string _path)
{
    mLoadSceneFlg = true;
    mLoadSceneInfo = { _name,_path };
}

void SceneManager::LoadLoadingScene()
{
    mLoadingScenePtr = mObjectFactoryPtr->CreateNewScene(
        "load-scene",
        "rom:/Configs/Scenes/load-scene.json");
}

void SceneManager::ReleaseLoadingScene()
{
    mLoadingScenePtr->ReleaseScene();
}

void SceneManager::LoadNextScene()
{
    MY_NN_LOG(LOG_MESSAGE, "ready to load next scene\n");

    for (int i = 0; i < 2; i++)
    {
        if (mScenePool[i] &&
            mScenePool[i]->GetSceneName() == mLoadSceneInfo[0])
        {
            SceneNode* node = mScenePool[i];
            node->ResetSceneNode();
            if (i)
            {
                SceneNode* temp = mScenePool[0];
                mScenePool[0] = mScenePool[1];
                mScenePool[1] = temp;
            }
            mNextScenePtr = node;
            return;
        }
    }

    SceneNode* node = mObjectFactoryPtr->CreateNewScene(
        mLoadSceneInfo[0], mLoadSceneInfo[1]);

    if (!mScenePool[0])
    {
        mScenePool[0] = node;
    }
    else if (!mScenePool[1])
    {
        mScenePool[1] = mScenePool[0];
        mScenePool[0] = node;
    }
    else
    {
        SceneNode* needRelease = mScenePool[1];
        mScenePool[1] = mScenePool[0];
        mScenePool[0] = node;
        mReleaseScenePtr = needRelease;
    }
    mNextScenePtr = node;
}
