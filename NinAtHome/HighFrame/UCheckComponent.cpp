//---------------------------------------------------------------
// File: UCheckComponent.cpp
// Proj: NinAtHome
// Info: UI¥ª¥Ö¥¸¥§¥¯¥È¤ËÅÐ¶¨¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "UCheckComponent.h"
#include "UiObject.h"

UCheckComponent::UCheckComponent(std::string _name,
    UiObject* _owner, int _order) :
    UComponent(_name, _owner, _order), mCheckFuncPtr(nullptr)
{

}

UCheckComponent::~UCheckComponent()
{

}

void UCheckComponent::CompInit()
{

}

void UCheckComponent::CompUpdate(float _deltatime)
{

}

void UCheckComponent::CompDestory()
{

}

void UCheckComponent::SetCheckFunc(UiCheckFuncType _func)
{
    mCheckFuncPtr = _func;
}

void UCheckComponent::ClearCheckFunc()
{
    mCheckFuncPtr = nullptr;
}
