#include "BulletCoin.h"

void BulletInit(AInteractionComponent* _aitc)
{
    ActorObject* owner = _aitc->GetActorObjOwner();
    if (owner)
    {
        std::string name = owner->GetObjectName();
        ((ATimerComponent*)(owner->
            GetAComponent(name + "-timer")))->
            StartTimer("life-time");
    }
}

void BulletUpdate(AInteractionComponent* _aitc, float _deltatime)
{
    ActorObject* owner = _aitc->GetActorObjOwner();
    if (owner)
    {
        std::string name = owner->GetObjectName();
        ((ATransformComponent*)(owner->
            GetAComponent(name + "-transform")))->
            TranslateXAsix(700.f * _deltatime);

        if (((ATimerComponent*)(owner->
            GetAComponent(name + "-timer")))->
            GetTimer("life-time")->IsGreaterThan(1.f))
        {
            owner->SetObjectActive(STATUS::NEED_DESTORY);
        }
    }
}

void BulletDestory(AInteractionComponent* _aitc)
{

}
