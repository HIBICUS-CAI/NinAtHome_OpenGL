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

void CheckWithLand(ActorObject* _runner, ActorObject* _land,
    float _deltatime)
{
    if (!_land)
    {
        return;
    }

    bool canStand = false;
    float deltaX = 0.f;
    {
        float thisX = ((ATransformComponent*)(_runner->
            GetAComponent("runner-actor-transform")))->
            GetPosition().x;
        float thatX = ((ATransformComponent*)(_land->
            GetAComponent("midland-1-actor-transform")))->
            GetPosition().x;
        deltaX = thisX - thatX;

        if (deltaX > -200.f && deltaX < 200.f)
        {
            canStand = true;
        }
    }

    if (((ACollisionComponent*)(_runner->
        GetAComponent("runner-actor-collision")))->
        CheckCollisionWith(_land) && canStand)
    {
        g_VVel = 0.f;
        g_CanJump = true;
    }
    else
    {
        float distance = g_VVel * _deltatime -
            g_Gravity * _deltatime * _deltatime;
        g_VVel = g_VVel + g_Gravity * _deltatime;

        ((ATransformComponent*)(_runner->
            GetAComponent("runner-actor-transform")))->
            TranslateYAsix(-distance);
        g_CanJump = false;
    }

    if (((ACollisionComponent*)(_runner->
        GetAComponent("runner-actor-collision")))->
        CheckCollisionWith(_land) && !canStand)
    {
        if (deltaX > 0.f)
        {
            ((ATransformComponent*)(_runner->
                GetAComponent("runner-actor-transform")))->
                TranslateXAsix(5.f);
        }
        else
        {
            ((ATransformComponent*)(_runner->
                GetAComponent("runner-actor-transform")))->
                TranslateXAsix(-5.f);
        }
    }
}

void RunnerUpdate(AInteractionComponent* _aitc, float _deltatime)
{
    ActorObject* owner = _aitc->GetActorObjOwner();
    ActorObject* land1 = owner->GetSceneNodePtr()->
        GetActorObject("midland-1-actor");

    CheckWithLand(owner, land1, _deltatime);
}

void RunnerDestory(AInteractionComponent* _aitc)
{

}
