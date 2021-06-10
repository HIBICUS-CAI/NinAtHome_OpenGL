//---------------------------------------------------------------
// File: UComponent.cpp
// Proj: NinAtHome
// Info: ¸÷UI¥ª¥Ö¥¸¥§¥¯¥È¤Ë´îÝd¤µ¤ì¤ë¥³¥ó¥Ý©`¥Í¥ó¥È³éÏó
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "UComponent.h"
#include "UiObject.h"

UComponent::UComponent(std::string _name,
    UiObject* _owner, int _order) :
    Component(_name, STATUS::NEED_INIT), mUObjectOwner(_owner),
    mUCUpdateOrder(_order)
{

}

UComponent::~UComponent()
{

}

UiObject* UComponent::GetUiObjOwner() const
{
    return mUObjectOwner;
}

int UComponent::GetUCUpdateOrder() const
{
    return mUCUpdateOrder;
}

void UComponent::CompInit()
{

}

void UComponent::CompUpdate(float _deltatime)
{

}

void UComponent::CompDestory()
{

}
