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

void RunnerInput(AInputComponent* _aic, float _deltatime)
{
    ActorObject* owner = _aic->GetActorObjOwner();

    if (GetControllerPress(NpadButton::StickLLeft::Index))
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(owner->
                GetAComponent("runner-actor-transform")))->
                TranslateXAsix(-300.f * _deltatime);
            owner->GetSceneNodePtr()->GetCamera()->
                TranslateCameraPos(MakeFloat2(
                    -300.f * _deltatime, 0.f));
        }
    }
    else if (GetControllerPress(NpadButton::StickLRight::Index))
    {
        if (owner && owner->IsObjectActive() == STATUS::ACTIVE)
        {
            ((ATransformComponent*)(owner->
                GetAComponent("runner-actor-transform")))->
                TranslateXAsix(300.f * _deltatime);
            owner->GetSceneNodePtr()->GetCamera()->
                TranslateCameraPos(MakeFloat2(
                    300.f * _deltatime, 0.f));
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
}

void RunnerInit(AInteractionComponent* _aitc)
{

}

void RunnerUpdate(AInteractionComponent* _aitc, float _deltatime)
{

}

void RunnerDestory(AInteractionComponent* _aitc)
{

}
