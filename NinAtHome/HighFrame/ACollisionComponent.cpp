//---------------------------------------------------------------
// File: ACollisionComponent.cpp
// Proj: NinAtHome
// Info: ACTOR¥ª¥Ö¥¸¥§¥¯¥È¤Ë¤¢¤¿¤ëÅÐ¶¨¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "ACollisionComponent.h"
#include "ActorObject.h"

ACollisionComponent::ACollisionComponent(std::string _name,
    ActorObject* _owner, int _order) :
    AComponent(_name, _owner, _order),
    mCollisionType(COLLISION_TYPE::NULLTYPE),
    mCollisionSize({ 0.f,0.f }), mShowCollisionFlg(false)
{

}

ACollisionComponent::~ACollisionComponent()
{

}

void ACollisionComponent::CompInit()
{

}

void ACollisionComponent::CompUpdate(float _deltatime)
{

}

void ACollisionComponent::CompDestory()
{

}

void ACollisionComponent::SetCollisionStatus(COLLISION_TYPE _type,
    Float2 _size, bool _showFlg)
{
    mCollisionType = _type;
    mCollisionSize = _size;
    mShowCollisionFlg = _showFlg;
}

COLLISION_TYPE ACollisionComponent::GetCollisionType() const
{
    return mCollisionType;
}

Float2 ACollisionComponent::GetCollisionSize() const
{
    return mCollisionSize;
}

bool ACollisionComponent::ShouldShowCollision() const
{
    return mShowCollisionFlg;
}

void ACollisionComponent::SetCollisionSize(Float2 _size)
{
    mCollisionSize = _size;
}

void ACollisionComponent::SetCollisionType(COLLISION_TYPE _type)
{
    mCollisionType = _type;
}

void ACollisionComponent::SetShowCollisionFlg(bool _flag)
{
    mShowCollisionFlg = _flag;
}

bool ACollisionComponent::CheckCollisionWith(ActorObject* _obj)
{
    // TEMP-------------
    return false;
    // TEMP-------------
}
