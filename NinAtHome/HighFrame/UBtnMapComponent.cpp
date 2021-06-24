//---------------------------------------------------------------
// File: UBtnMapComponent.cpp
// Proj: NinAtHome
// Info: UI¥ª¥Ö¥¸¥§¥¯¥È¤Ë¥Ü¥¿¥óµØ‡í¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "UBtnMapComponent.h"
#include "UiObject.h"

UBtnMapComponent::UBtnMapComponent(std::string _name,
    UiObject* _owner, int _order) :
    UComponent(_name, _owner, _order),
    mSurroundBtns({ nullptr,nullptr,nullptr,nullptr }),
    mIsSelected(false)
{

}

UBtnMapComponent::~UBtnMapComponent()
{

}

void UBtnMapComponent::CompInit()
{

}

void UBtnMapComponent::CompUpdate(float _deltatime)
{

}

void UBtnMapComponent::CompDestory()
{

}

bool UBtnMapComponent::IsBeingSelected()
{
    return mIsSelected;
}

void UBtnMapComponent::SelectUpBtn()
{

}

void UBtnMapComponent::SelectDownBtn()
{

}

void UBtnMapComponent::SelectLeftBtn()
{

}

void UBtnMapComponent::SelectRightBtn()
{

}

UiObject* UBtnMapComponent::GetUpBtn() const
{
    // TEMP---------------------
    return nullptr;
    // TEMP---------------------
}

UiObject* UBtnMapComponent::GetDownBtn() const
{
    // TEMP---------------------
    return nullptr;
    // TEMP---------------------
}

UiObject* UBtnMapComponent::GetLeftBtn() const
{
    // TEMP---------------------
    return nullptr;
    // TEMP---------------------
}

UiObject* UBtnMapComponent::GetRightBtn() const
{
    // TEMP---------------------
    return nullptr;
    // TEMP---------------------
}

void UBtnMapComponent::UpdateButtonMap()
{

}
