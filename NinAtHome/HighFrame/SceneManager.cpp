//---------------------------------------------------------------
// File: SceneManager.cpp
// Proj: NinAtHome
// Info: •∑©`•Ûπ‹¿Ì§π§ÎôCƒ‹§ŒåùèÍ
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "SceneManager.h"
#include "SceneNode.h"
#include "PropertyManager.h"
#include "ObjectFactory.h"

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

void SceneManager::CleanAndStop()
{

}

void SceneManager::UpdateSceneManager()
{

}

PropertyManager* SceneManager::GetPropertyManager() const
{
    return mPropertyManagerPtr;
}

ObjectFactory* SceneManager::GetObjectFactory() const
{
    return mObjectFactoryPtr;
}

void SceneManager::LoadSceneNode(std::string _name, std::string _path)
{
    mLoadSceneInfo = { _name,_path };
}

void SceneManager::LoadLoadingScene()
{

}

void SceneManager::ReleaseLoadingScene()
{

}

void SceneManager::LoadNextScene()
{

}
