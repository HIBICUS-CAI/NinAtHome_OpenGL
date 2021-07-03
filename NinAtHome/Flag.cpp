#include "Flag.h"

void FlagRegister(ObjectFactory* _factory)
{
    auto init = _factory->GetActorInterInitPool();
    auto update = _factory->GetActorInterUpdatePool();
    auto destory = _factory->GetActorInterDestoryPool();

    init->insert(std::make_pair(
        FUNC_NAME(FlagInit), FlagInit));
    update->insert(std::make_pair(
        FUNC_NAME(FlagUpdate), FlagUpdate));
    destory->insert(std::make_pair(
        FUNC_NAME(FlagDestory), FlagDestory));
}

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
