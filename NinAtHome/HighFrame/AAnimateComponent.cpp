//---------------------------------------------------------------
// File: AAnimateComponent.cpp
// Proj: NinAtHome
// Info: ACTOR¥ª¥Ö¥¸¥§¥¯¥È¤Ë¥¢¥Ë¥á©`¥·¥ç¥ó¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "AAnimateComponent.h"
#include "ActorObject.h"

AAnimateComponent::AAnimateComponent(std::string _name,
    ActorObject* _owner, int _order) :
    AComponent(_name, _owner, _order), mAnimates({}),
    mCurrentAnimateCut(0)
{
    mAnimates.clear();
}

AAnimateComponent::~AAnimateComponent()
{

}

void AAnimateComponent::CompInit()
{

}

void AAnimateComponent::CompUpdate(float _deltatime)
{

}

void AAnimateComponent::CompDestory()
{

}

void AAnimateComponent::LoadAnimate(std::string _name,
    std::string _path, Float2 _stride, unsigned int _maxCount)
{

}

void AAnimateComponent::DeleteAnimate(std::string _name)
{

}

void AAnimateComponent::ResetCurrentAnimateCut()
{
    mCurrentAnimateCut = 0;
}

void AAnimateComponent::ChangeAnimateTo(std::string _name)
{

}

void AAnimateComponent::SetThisAnimateToTextureComp(
    std::string _name)
{

}
