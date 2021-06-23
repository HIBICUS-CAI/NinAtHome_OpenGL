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
#include "texture.h"
#include "sprite.h"
#include "UTransformComponent.h"

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
    DeleteTexture();
}

void USpriteComponent::LoadTextureByPath(std::string _path)
{
    mTexture = LoadTexture(_path);
}

void USpriteComponent::DeleteTexture()
{
    UnloadTexture(mTexture);
}

unsigned int USpriteComponent::GetTexture() const
{
    return mTexture;
}

void USpriteComponent::SetTexWidth(float _width)
{
    if (_width < 0.f)
    {
        _width = -_width;
    }

    mTexWidth = _width;
}

void USpriteComponent::SetTexHeight(float _height)
{
    if (_height < 0.f)
    {
        _height = -_height;
    }

    mTexHeight = _height;
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

void USpriteComponent::DrawUSprite()
{
    if (!mVisible)
    {
        return;
    }

    std::string transname = GetComponentName();
    auto offset = transname.rfind("sprite");
    transname.replace(offset, 6, "transform");
    auto transcomp = GetUiObjOwner()->GetUComponent(transname);
    if (!transcomp)
    {
        MY_NN_LOG(LOG_ERROR,
            "cannot find the transform component of [ %s ]\n",
            GetUiObjOwner()->GetObjectName().c_str());

        return;
    }

#ifdef NIN_AT_HOME
    {
        Matrix4x4f world = ((UTransformComponent*)transcomp)->
            GetWorldMatrix();
        Float4x4 pworld = nullptr;
        MatrixStore(&pworld, world);
        glUniformMatrix4fv(
            glGetUniformLocation(
                GetGlHelperPtr()->GetShaderID("default"),
                "uWorld"), 1, GL_TRUE, pworld);
    }
#else

#endif // NIN_AT_HOME

    SetTexture(mTexture);
    DrawSprite(0.f, 0.f, mTexWidth, mTexHeight,
        0.f, 0.f, 1.f, 1.f,
        mOffsetColor);
}
