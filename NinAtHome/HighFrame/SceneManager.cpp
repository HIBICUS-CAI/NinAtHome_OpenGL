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
#include "controller.h"
#include "ATransformComponent.h"
#include "ACollisionComponent.h"
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

    if (GetControllerTrigger(NpadButton::A::Index))
    {
        auto parent = mCurrentScenePtr->GetActorObject("test");
        if (parent)
        {
            parent->ClearChild("test2");
        }
    }
    if (GetControllerTrigger(NpadButton::B::Index))
    {
        auto obj = mCurrentScenePtr->GetActorObject("test");
        if (obj)
        {
            if (obj->IsObjectActive() == STATUS::ACTIVE)
            {
                obj->SetObjectActive(STATUS::PAUSE);
            }
            else
            {
                obj->SetObjectActive(STATUS::ACTIVE);
            }
        }
    }
    if (GetControllerPress(NpadButton::Left::Index) ||
        GetControllerPress(NpadButton::StickLLeft::Index))
    {
        auto obj = mCurrentScenePtr->GetActorObject("test");
        if (obj && obj->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(obj->
                GetAComponent("test-transform")))->
                TranslateXAsix(-5.f);
        }
    }
    if (GetControllerPress(NpadButton::Right::Index) ||
        GetControllerPress(NpadButton::StickLRight::Index))
    {
        auto obj = mCurrentScenePtr->GetActorObject("test");
        if (obj && obj->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(obj->
                GetAComponent("test-transform")))->
                TranslateXAsix(5.f);
        }
    }
    if (GetControllerPress(NpadButton::Up::Index) ||
        GetControllerPress(NpadButton::StickLUp::Index))
    {
        auto obj = mCurrentScenePtr->GetActorObject("test");
        if (obj && obj->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(obj->
                GetAComponent("test-transform")))->
                TranslateYAsix(-5.f);
        }
    }
    if (GetControllerPress(NpadButton::Down::Index) ||
        GetControllerPress(NpadButton::StickLDown::Index))
    {
        auto obj = mCurrentScenePtr->GetActorObject("test");
        if (obj && obj->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(obj->
                GetAComponent("test-transform")))->
                TranslateYAsix(5.f);
        }
    }

    auto ac = mCurrentScenePtr->GetActorObject("test");
    if (ac)
    {
        auto acc = (ACollisionComponent*)(ac->
            GetAComponent(ac->GetObjectName() + "-collision"));
        if (acc)
        {
            bool coll = acc->CheckCollisionWith(mCurrentScenePtr->
                GetActorObject("test2"));
            MY_NN_LOG(LOG_DEBUG, "%d\n", coll);
        }
    }

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
    ATransformComponent* atc = new ATransformComponent(
        "test-transform", actor, -1, MakeFloat3(0.f, 0.f, 0.f));
    atc->Scale(1.5f);
    actor->AddAComponent(atc);
    ASpriteComponent* asc = new ASpriteComponent("test-sprite",
        actor, 0, 0);
    asc->LoadTextureByPath("rom:/Assets/Textures/texture.tga");
    asc->SetTexWidth(200.f);
    asc->SetTexHeight(200.f);
    actor->AddAComponent(asc);
    ACollisionComponent* acc = new ACollisionComponent(
        "test-collision", actor, 0);
    acc->SetCollisionStatus(COLLISION_TYPE::CIRCLE,
        MakeFloat2(100.f, 100.f), true);
    actor->AddAComponent(acc);
    mLoadingScenePtr->AddActorObject(actor);

    ActorObject* actor1 = new ActorObject(
        "test2", mLoadingScenePtr, 0);
    ATransformComponent* atc1 = new ATransformComponent(
        "test2-transform", actor1, -1, MakeFloat3(0.f, 0.f, 0.f));
    actor1->AddAComponent(atc1);
    ASpriteComponent* asc1 = new ASpriteComponent("test2-sprite",
        actor1, 0, -2);
    asc1->LoadTextureByPath("rom:/Assets/Textures/player.tga");
    asc1->SetTexWidth(150.f);
    asc1->SetTexHeight(50.f);
    actor1->AddAComponent(asc1);
    ACollisionComponent* acc1 = new ACollisionComponent(
        "test2-collision", actor1, 0);
    acc1->SetCollisionStatus(COLLISION_TYPE::RECTANGLE,
        MakeFloat2(150.f, 50.f), true);
    actor1->AddAComponent(acc1);
    mLoadingScenePtr->AddActorObject(actor1);
    // TEMP---------------------------
}

void SceneManager::ReleaseLoadingScene()
{
    mLoadingScenePtr->ReleaseScene();
}

void SceneManager::LoadNextScene()
{
    MY_NN_LOG(LOG_MESSAGE, "ready to load next scene\n");

    mCurrentScenePtr = nullptr;
}
