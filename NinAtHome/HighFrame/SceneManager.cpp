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
static int g_scene = 1;
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

    // TEMP-------------------
    g_scene = 0;
    LoadSceneNode(
        "first-scene",
        "rom:/Configs/Scenes/1-scene.json");
    // TEMP-------------------
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

        if (mCurrentScenePtr)
        {
            mCurrentScenePtr->ReleaseScene();
            delete mCurrentScenePtr;
        }

        mCurrentScenePtr = mLoadingScenePtr;
        /*std::thread loadThread(
            &SceneManager::LoadNextScene, this);
        loadThread.detach();*/
    }

    if (mNextScenePtr)
    {
#ifdef SHOW_LOADING
        Sleep(500);
#endif // SHOW_LOADING
        mCurrentScenePtr = mNextScenePtr;
        mNextScenePtr = nullptr;
    }

    // TEMP---------------------------
    if (GetControllerTrigger(NpadButton::StickL::Index))
    {
        g_scene = (++g_scene) % 3;
        std::string name = "";
        std::string path = "";
        switch (g_scene)
        {
        case 0:
            name = "first-scene";
            path = "rom:/Configs/Scenes/1-scene.json";
            break;
        case 1:
            name = "second-scene";
            path = "rom:/Configs/Scenes/2-scene.json";
            break;
        case 2:
            name = "third-scene";
            path = "rom:/Configs/Scenes/3-scene.json";
            break;
        default:
            break;
        }
        LoadSceneNode(name, path);
    }
    // TEMP---------------------------

    mCurrentScenePtr->UpdateScene(_deltatime);
    mCurrentScenePtr->DrawScene();

    if (mCurrentScenePtr == mLoadingScenePtr)
    {
        LoadNextScene();
    }
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

    mNextScenePtr = mObjectFactoryPtr->CreateNewScene(
        mLoadSceneInfo[0], mLoadSceneInfo[1]);
}
