#include "RunnerAndBg.h"
#include "controller.h"

void HiddenCommandInput(AInputComponent* _aic, float _deltatime)
{
    if (GetControllerTrigger(NpadButton::StickL::Index))
    {
        _aic->GetActorObjOwner()->GetSceneNodePtr()->
            GetSceneManagerPtr()->LoadSceneNode(
                "result-success-scene",
                "rom:/Configs/Scenes/result-success-scene.json");
    }
    else if (GetControllerTrigger(NpadButton::StickR::Index))
    {
        _aic->GetActorObjOwner()->GetSceneNodePtr()->
            GetSceneManagerPtr()->LoadSceneNode(
                "result-fail-scene",
                "rom:/Configs/Scenes/result-fail-scene.json");
    }
}

static float g_Gravity = 0.f;
static float g_VVel = 0.f;
static float g_HVel = 0.f;
static bool g_CanJump = true;

void RunnerInput(AInputComponent* _aic, float _deltatime)
{
    ActorObject* owner = _aic->GetActorObjOwner();

    if (GetControllerPress(NpadButton::StickLLeft::Index))
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(owner->
                GetAComponent("runner-actor-transform")))->
                TranslateXAsix(-g_HVel * _deltatime);
            owner->GetSceneNodePtr()->GetCamera()->
                TranslateCameraPos(MakeFloat2(
                    -g_HVel * _deltatime, 0.f));
        }
    }
    else if (GetControllerPress(NpadButton::StickLRight::Index))
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(owner->
                GetAComponent("runner-actor-transform")))->
                TranslateXAsix(g_HVel * _deltatime);
            owner->GetSceneNodePtr()->GetCamera()->
                TranslateCameraPos(MakeFloat2(
                    g_HVel * _deltatime, 0.f));
        }
    }
    else
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((AAnimateComponent*)(owner->
                GetAComponent("runner-actor-animate")))->
                ChangeAnimateTo("stand");
        }
    }

    if (GetControllerTrigger(NpadButton::StickLLeft::Index) ||
        GetControllerTrigger(NpadButton::StickLRight::Index))
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((AAnimateComponent*)(owner->
                GetAComponent("runner-actor-animate")))->
                ChangeAnimateTo("walk");
        }
    }

    static bool shouldSetWalk = true;
    if (GetControllerTrigger(NpadButton::B::Index))
    {
        if (owner && g_CanJump)
        {
            ((ATransformComponent*)(owner->
                GetAComponent("runner-actor-transform")))->
                TranslateYAsix(-15.f);
            g_CanJump = false;
            g_VVel = 600.f;
            shouldSetWalk = true;
        }
    }

    if (!g_CanJump)
    {
        ((AAnimateComponent*)(owner->
            GetAComponent("runner-actor-animate")))->
            ChangeAnimateTo("jump");
    }
    else
    {
        if (shouldSetWalk)
        {
            shouldSetWalk = false;
            ((AAnimateComponent*)(owner->
                GetAComponent("runner-actor-animate")))->
                ChangeAnimateTo("walk");
        }
    }
}

void RunnerInit(AInteractionComponent* _aitc)
{
    g_Gravity = -1500.f;
    g_VVel = 0.f;
    g_HVel = 300.f;
}

bool CheckWithLand(ActorObject* _runner, ActorObject* _land,
    float _deltatime)
{
    if (!_land)
    {
        return false;
    }

    bool shouldFall = true;

    std::string landTransName = _land->GetObjectName() +
        "-transform";

    bool canStand = false;
    float deltaX = 0.f;
    float deltaY = 0.f;
    {
        float thisX = ((ATransformComponent*)(_runner->
            GetAComponent("runner-actor-transform")))->
            GetPosition().x;
        float thatX = ((ATransformComponent*)(_land->
            GetAComponent(landTransName)))->GetPosition().x;
        deltaX = thisX - thatX;

        float thatY = ((ATransformComponent*)(_runner->
            GetAComponent("runner-actor-transform")))->
            GetPosition().y;
        float thisY = ((ATransformComponent*)(_land->
            GetAComponent(landTransName)))->GetPosition().y;
        deltaY = thisY - thatY;
        deltaY -= 84.f;

        if (deltaX > -200.f && deltaX < 200.f && deltaY > 7.5f)
        {
            canStand = true;
        }
    }

    if (((ACollisionComponent*)(_runner->
        GetAComponent("runner-actor-collision")))->
        CheckCollisionWith(_land) && canStand)
    {
        g_VVel = 0.f;
        shouldFall = false;
    }

    if (((ACollisionComponent*)(_runner->
        GetAComponent("runner-actor-collision")))->
        CheckCollisionWith(_land) && !canStand)
    {
        if (deltaX > 195.f)
        {
            if (deltaY < 7.5f)
            {
                ((ATransformComponent*)(_runner->
                    GetAComponent("runner-actor-transform")))->
                    TranslateXAsix(5.f);
                _runner->GetSceneNodePtr()->GetCamera()->
                    TranslateCameraPos(MakeFloat2(
                        5.f, 0.f));
            }
        }
        else if (deltaX < -195.f)
        {
            if (deltaY < 7.5f)
            {
                ((ATransformComponent*)(_runner->
                    GetAComponent("runner-actor-transform")))->
                    TranslateXAsix(-5.f);
                _runner->GetSceneNodePtr()->GetCamera()->
                    TranslateCameraPos(MakeFloat2(
                        -5.f, 0.f));
            }
        }
        else
        {
            g_VVel = 0.f;
            ((ATransformComponent*)(_runner->
                GetAComponent("runner-actor-transform")))->
                TranslateYAsix(5.f);
        }
    }

    return shouldFall;
}

void RunnerUpdate(AInteractionComponent* _aitc, float _deltatime)
{
    ActorObject* owner = _aitc->GetActorObjOwner();
    ActorObject* land1 = owner->GetSceneNodePtr()->
        GetActorObject("midland-1-actor");
    ActorObject* land2 = owner->GetSceneNodePtr()->
        GetActorObject("midland-2-actor");
    ActorObject* land3 = owner->GetSceneNodePtr()->
        GetActorObject("midland-3-actor");

    bool should1 = CheckWithLand(owner, land1, _deltatime);
    bool should2 = CheckWithLand(owner, land2, _deltatime);
    bool should3 = CheckWithLand(owner, land3, _deltatime);

    if (should1 && should2 && should3)
    {
        float distance = g_VVel * _deltatime -
            g_Gravity * _deltatime * _deltatime;
        g_VVel = g_VVel + g_Gravity * _deltatime;

        ((ATransformComponent*)(owner->
            GetAComponent("runner-actor-transform")))->
            TranslateYAsix(-distance);
    }

    if (should1 && should2 && should3)
    {
        g_CanJump = false;
    }
    else
    {
        g_CanJump = true;
    }
}

void RunnerDestory(AInteractionComponent* _aitc)
{

}
