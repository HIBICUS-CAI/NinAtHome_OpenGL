//---------------------------------------------------------------
// File: USpriteComponent.cpp
// Proj: NinAtHome
// Info: UI¥ª¥Ö¥¸¥§¥¯¥È¤Ë¥¹¥×¥é¥¤¥È¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "USpriteComponent.h"
#include "UiObject.h"

USpriteComponent::USpriteComponent(std::string _name,
    UiObject* _owner, int _order, int _drawOrder) :
    UComponent(_name, _owner, _order), mDrawOrder(_drawOrder),
    mTexture(0), mOffsetColor({ 1.f,1.f,1.f,1.f }), mVisible(true),
    mTexWidth(0), mTexHeight(0)
{

}

USpriteComponent::~USpriteComponent()
{

}

void USpriteComponent::CompInit()
{

}

void USpriteComponent::CompUpdate(float _deltatime)
{

}

void USpriteComponent::CompDestory()
{

}

void USpriteComponent::LoadTexture(std::string _path)
{

}

void USpriteComponent::DeleteTexture()
{

}

unsigned int USpriteComponent::GetTexture() const
{
    return mTexture;
}

unsigned int USpriteComponent::GetTexWidth() const
{
    return mTexWidth;
}

unsigned int USpriteComponent::GetTexHeight() const
{
    return mTexHeight;
}

void USpriteComponent::SetOffsetColor(Float4 _color)
{
    mOffsetColor = _color;
}

Float4 USpriteComponent::GetOffsetColor() const
{
    return mOffsetColor;
}

void USpriteComponent::SetVisible(bool _visible)
{
    mVisible = _visible;
}

bool USpriteComponent::GetVisible() const
{
    return mVisible;
}

int USpriteComponent::GetDrawOrder() const
{
    return mDrawOrder;
}

void USpriteComponent::ResetDrawOrder(int _order)
{
    mDrawOrder = _order;
}
