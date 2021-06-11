//---------------------------------------------------------------
// File: ASpriteComponent.cpp
// Proj: NinAtHome
// Info: ACTOR¥ª¥Ö¥¸¥§¥¯¥È¤Ë¥¹¥×¥é¥¤¥È¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "ASpriteComponent.h"
#include "ActorObject.h"

ASpriteComponent::ASpriteComponent(std::string _name,
    ActorObject* _owner, int _order, int _drawOrder) :
    AComponent(_name, _owner, _order), mDrawOrder(_drawOrder),
    mTexture(0), mOffsetColor({ 1.f,1.f,1.f,1.f }), mVisible(true),
    mTexWidth(0), mTexHeight(0)
{

}

ASpriteComponent::~ASpriteComponent()
{

}

void ASpriteComponent::CompInit()
{

}

void ASpriteComponent::CompUpdate(float _deltatime)
{

}

void ASpriteComponent::CompDestory()
{

}

void ASpriteComponent::LoadTexture(std::string _path)
{

}

void ASpriteComponent::DeleteTexture()
{

}

unsigned int ASpriteComponent::GetTexture() const
{
    return mTexture;
}

unsigned int ASpriteComponent::GetTexWidth() const
{
    return mTexWidth;
}

unsigned int ASpriteComponent::GetTexHeight() const
{
    return mTexHeight;
}

void ASpriteComponent::SetOffsetColor(Float4 _color)
{
    mOffsetColor = _color;
}

Float4 ASpriteComponent::GetOffsetColor() const
{
    return mOffsetColor;
}

void ASpriteComponent::SetVisible(bool _visible)
{
    mVisible = _visible;
}

bool ASpriteComponent::GetVisible() const
{
    return mVisible;
}

int ASpriteComponent::GetDrawOrder() const
{
    return mDrawOrder;
}

void ASpriteComponent::ResetDrawOrder(int _order)
{
    mDrawOrder = _order;
}
