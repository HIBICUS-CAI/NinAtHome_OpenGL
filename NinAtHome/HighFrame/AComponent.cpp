//---------------------------------------------------------------
// File: AComponent.cpp
// Proj: NinAtHome
// Info: ACTORオブジェクトに搭載されるコンポーネント
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "AComponent.h"
#include "ActorObject.h"

AComponent::AComponent(std::string _name,
    ActorObject* _owner, int _order) :
    Component(_name, STATUS::NEED_INIT), mAObjectOwner(_owner),
    mACUpdateOrder(_order)
{

}

AComponent::~AComponent()
{

}

ActorObject* AComponent::GetActorObjOwner() const
{
    return mAObjectOwner;
}

int AComponent::GetACUpdateOrder() const
{
    return mACUpdateOrder;
}

void AComponent::CompInit()
{

}

void AComponent::CompUpdate(float _deltatime)
{

}

void AComponent::CompDestory()
{

}
