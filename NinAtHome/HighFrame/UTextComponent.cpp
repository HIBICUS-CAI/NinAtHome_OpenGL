//---------------------------------------------------------------
// File: UTextComponent.cpp
// Proj: NinAtHome
// Info: UI¥ª¥Ö¥¸¥§¥¯¥È¤ËÎÄ×Ö±íÊ¾¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "UTextComponent.h"
#include "UiObject.h"

UTextComponent::UTextComponent(std::string _name,
    UiObject* _owner, int _order) :
    UComponent(_name, _owner, _order), mSingleText(""),
    mMutiText({}), mTextPosition({ 0.f,0.f,0.f }), mFontSize(1),
    mFont({}), mUsingMutiTextFlg(false)
{
    mMutiText.clear();
}

UTextComponent::~UTextComponent()
{

}

void UTextComponent::CompInit()
{

}

void UTextComponent::CompUpdate(float _deltatime)
{

}

void UTextComponent::CompDestory()
{

}

void UTextComponent::SetTextPosition(Float3 _pos)
{
    mTextPosition = _pos;
}

void UTextComponent::SetFontSize(unsigned int _size)
{
    mFontSize = _size;
}

unsigned int UTextComponent::GetFontSize() const
{
    return mFontSize;
}

void UTextComponent::LoadFont(std::string _path)
{

}

void UTextComponent::ChangeSingleText(std::string _text)
{
    mSingleText = _text;
}

void UTextComponent::ReloadMutiText(std::string _path)
{

}

void UTextComponent::DrawUText()
{

}
