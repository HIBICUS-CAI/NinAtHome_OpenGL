#include "Flag.h"

void FlagInit(AInteractionComponent* _aitc)
{

}

void FlagUpdate(AInteractionComponent* _aitc, float _deltatime)
{
    ActorObject* owner = _aitc->GetActorObjOwner();
    ActorObject* runner = _aitc->GetActorObjOwner()->
        GetSceneNodePtr()->GetActorObject("runner-actor");
    if (!owner || !runner)
    {
        return;
    }

    if (((ACollisionComponent*)(owner->
        GetAComponent("flag-actor-collision")))->
        CheckCollisionWith(runner))
    {
        owner->GetSceneNodePtr()->GetSceneManagerPtr()->
            LoadSceneNode(
                "result-success-scene",
                "rom:/Configs/Scenes/result-success-scene.json");
    }
}

void FlagDestory(AInteractionComponent* _aitc)
{

}
