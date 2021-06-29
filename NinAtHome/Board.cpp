#include "Board.h"

void BoardInit(AInteractionComponent* _aitc)
{

}

void BoardUpdate(AInteractionComponent* _aitc, float _deltatime)
{
    if (((ATimerComponent*)(_aitc->GetActorObjOwner()->
        GetAComponent(_aitc->GetActorObjOwner()->
            GetObjectName() + "-timer")))->
        GetTimer("explosion")->IsGreaterThan(1.5f))
    {
        _aitc->GetActorObjOwner()->SetObjectActive(
            STATUS::NEED_DESTORY);
    }
}

void BoardDestory(AInteractionComponent* _aitc)
{

}

void SetToExplosion(ActorObject* _board)
{
    if (!((ATimerComponent*)(_board->GetAComponent(
        _board->GetObjectName() + "-timer")))->
        GetTimer("explosion")->Active)
    {
        ((ATransformComponent*)(_board->GetAComponent(
            _board->GetObjectName() + "-transform")))->
            RotateZAsix(-90.f);
        ((ASpriteComponent*)(_board->GetAComponent(
            _board->GetObjectName() + "-sprite")))->
            SetTexWidth(100.f);
        ((ASpriteComponent*)(_board->GetAComponent(
            _board->GetObjectName() + "-sprite")))->
            SetTexHeight(100.f);
        ((ACollisionComponent*)(_board->GetAComponent(
            _board->GetObjectName() + "-collision")))->
            SetCollisionSize(MakeFloat2(100.f, 100.f));
        ((AAnimateComponent*)(_board->GetAComponent(
            _board->GetObjectName() + "-animate")))->
            ChangeAnimateTo("explosion");
        ((ATimerComponent*)(_board->GetAComponent(
            _board->GetObjectName() + "-timer")))->
            StartTimer("explosion");
    }
}
