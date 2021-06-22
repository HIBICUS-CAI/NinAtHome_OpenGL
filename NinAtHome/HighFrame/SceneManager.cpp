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
#include "AInputComponent.h"
#include "ATimerComponent.h"
#include "AAnimateComponent.h"

void TempMove(AInputComponent* _aic, float _deltatime)
{
    ActorObject* owner = _aic->GetActorObjOwner();

    if (GetControllerTrigger(NpadButton::X::Index))
    {
        if (owner)
        {
            auto aac = (AAnimateComponent*)(owner->
                GetAComponent("test-animate"));
            if (aac)
            {
                aac->ChangeAnimateTo("run");
            }
        }
    }
    if (GetControllerTrigger(NpadButton::Y::Index))
    {
        if (owner)
        {
            auto aac = (AAnimateComponent*)(owner->
                GetAComponent("test-animate"));
            if (aac)
            {
                aac->ChangeAnimateTo("number");
            }
        }
    }
    if (GetControllerTrigger(NpadButton::A::Index))
    {
        if (owner)
        {
            auto atic = (ATimerComponent*)(owner->
                GetAComponent("test-timer"));
            if (atic)
            {
                atic->StartTimer("r");
                atic->StartTimer("g");
                atic->StartTimer("b");
            }
        }
    }
    if (GetControllerTrigger(NpadButton::B::Index))
    {
        if (owner)
        {
            auto atic = (ATimerComponent*)(owner->
                GetAComponent("test-timer"));
            if (atic)
            {
                atic->ResetTimer("r");
                atic->ResetTimer("g");
                atic->ResetTimer("b");
            }
        }
    }
    if (GetControllerPress(NpadButton::Left::Index) ||
        GetControllerPress(NpadButton::StickLLeft::Index))
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(owner->
                GetAComponent("test-transform")))->
                TranslateXAsix(-200.f * _deltatime);
        }
    }
    if (GetControllerPress(NpadButton::Right::Index) ||
        GetControllerPress(NpadButton::StickLRight::Index))
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(owner->
                GetAComponent("test-transform")))->
                TranslateXAsix(200.f * _deltatime);
        }
    }
    if (GetControllerPress(NpadButton::Up::Index) ||
        GetControllerPress(NpadButton::StickLUp::Index))
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(owner->
                GetAComponent("test-transform")))->
                TranslateYAsix(-200.f * _deltatime);
        }
    }
    if (GetControllerPress(NpadButton::Down::Index) ||
        GetControllerPress(NpadButton::StickLDown::Index))
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(owner->
                GetAComponent("test-transform")))->
                TranslateYAsix(200.f * _deltatime);
        }
    }
}
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

    auto ac = mCurrentScenePtr->GetActorObject("test");
    if (ac)
    {
        auto acc = (ACollisionComponent*)(ac->
            GetAComponent(ac->GetObjectName() + "-collision"));
        if (acc)
        {
            acc->CheckCollisionWith(mCurrentScenePtr->
                GetActorObject("test2"));
        }

        Float4 color = MakeFloat4(1.f, 1.f, 1.f, 1.f);
        auto atic = (ATimerComponent*)(ac->
            GetAComponent("test-timer"));
        if (atic)
        {
            if (atic->GetTimer("r")->IsGreaterThan(5.f))
            {
                color.x = 0.5f;
            }
            if (atic->GetTimer("g")->IsGreaterThan(10.f))
            {
                color.y = 0.5f;
            }
            if (atic->GetTimer("b")->IsGreaterThan(15.f))
            {
                color.z = 0.5f;
            }
        }

        auto asc = (ASpriteComponent*)(ac->
            GetAComponent("test-sprite"));
        if (asc)
        {
            asc->SetOffsetColor(color);
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
    AInputComponent* aic = new AInputComponent("test-input",
        actor, 0);
    aic->SetInputProcessFunc(TempMove);
    actor->AddAComponent(aic);
    ATimerComponent* atic = new ATimerComponent("test-timer",
        actor, 0);
    actor->AddAComponent(atic);
    atic->AddTimer("r");
    atic->AddTimer("g");
    atic->AddTimer("b");
    AAnimateComponent* aac = new AAnimateComponent("test-animate",
        actor, 0);
    actor->AddAComponent(aac);
    aac->LoadAnimate("number", "rom:/Assets/Textures/number.tga",
        MakeFloat2(0.2f, 0.2f), 13, false, 1.f);
    aac->LoadAnimate("run", "rom:/Assets/Textures/runman.tga",
        MakeFloat2(0.2f, 0.5f), 10, true, 0.1f);
    aac->ChangeAnimateTo("number");
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

    ActorObject* actor2 = new ActorObject(
        "test3", mLoadingScenePtr, 0);
    ATransformComponent* atc2 = new ATransformComponent(
        "test3-transform", actor2, -1, MakeFloat3(0.f, 0.f, 0.f));
    atc2->TranslateXAsix(100.f);
    actor2->AddAComponent(atc2);
    ASpriteComponent* asc2 = new ASpriteComponent("test3-sprite",
        actor2, 0, -2);
    asc2->LoadTextureByPath("rom:/Assets/Textures/player.tga");
    asc2->SetTexWidth(150.f);
    asc2->SetTexHeight(50.f);
    actor2->AddAComponent(asc2);
    ACollisionComponent* acc2 = new ACollisionComponent(
        "test3-collision", actor2, 0);
    acc2->SetCollisionStatus(COLLISION_TYPE::RECTANGLE,
        MakeFloat2(150.f, 50.f), true);
    actor2->AddAComponent(acc2);
    actor1->AddChild(actor2);
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
