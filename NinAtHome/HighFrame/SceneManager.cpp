//---------------------------------------------------------------
// File: SceneManager.cpp
// Proj: NinAtHome
// Info: ¥·©`¥ó¹ÜÀí¤¹¤ë™CÄÜ¤ÎŒê
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
// TEMP--------------------
#include "ActorObject.h"
#include "ASpriteComponent.h"
// TEMP--------------------

SceneManager::SceneManager() :
    mPropertyManagerPtr(nullptr), mObjectFactoryPtr(nullptr),
    mLoadingScenePtr(nullptr), mCurrentScenePtr(nullptr),
    mNextScenePtr(nullptr), mLoadSceneFlg(false),
    mLoadSceneInfo({ "","" })
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
    /*NN_LOG(LOG_MESSAGE,
        "final delta : %f\n", _deltatime);*/

    if (mLoadSceneFlg)
    {
        mLoadSceneFlg = false;
        mCurrentScenePtr = mLoadingScenePtr;
        std::thread loadThread(
            &SceneManager::LoadNextScene, this);
        loadThread.detach();
    }

    // TEMP---------------------------
    mCurrentScenePtr = mLoadingScenePtr;
    mCurrentScenePtr->UpdateScene(_deltatime);
    mCurrentScenePtr->DrawScene();
    // TEMP---------------------------
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
    // TEMP---------------------------
    mLoadingScenePtr = new SceneNode("load-scene", this);
    ActorObject* actor = new ActorObject(
        "test", mLoadingScenePtr, 0);
    ASpriteComponent* asc = new ASpriteComponent("test-sprite",
        actor, 0, 0);
    asc->LoadTextureByPath("rom:/Assets/Textures/texture.tga");
    actor->AddAComponent(asc);
    mLoadingScenePtr->AddActorObject(actor);
    // TEMP---------------------------
}

void SceneManager::ReleaseLoadingScene()
{
    mLoadingScenePtr->ReleaseScene();
}

void SceneManager::LoadNextScene()
{
    NN_LOG(LOG_MESSAGE, "ready to load next scene\n");

    mCurrentScenePtr = nullptr;
}
