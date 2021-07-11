//---------------------------------------------------------------
// File: ASpriteComponent.cpp
// Proj: NinAtHome
// Info: ACTORオブジェクトにスプライトに関してのコンポーネント
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "ASpriteComponent.h"
#include "ActorObject.h"
#include "texture.h"
#include "sprite.h"
#include "ATransformComponent.h"
#include "SceneNode.h"

ASpriteComponent::ASpriteComponent(std::string _name,
    ActorObject* _owner, int _order, int _drawOrder) :
    AComponent(_name, _owner, _order), mDrawOrder(_drawOrder),
    mTexture(nullptr), mOffsetColor(MakeFloat4(1.f, 1.f, 1.f, 1.f)),
    mVisible(true), mTexWidth(0.f), mTexHeight(0.f),
    mUVValue(MakeFloat4(1.f, 1.f, 1.f, 1.f)),
    mFirstTexture(nullptr), mTexPath(""),
    mSpriteVertexBuffer(nullptr), mSpriteIndexBuffer(nullptr)
{

}

ASpriteComponent::~ASpriteComponent()
{

}

void ASpriteComponent::CompInit()
{
    mUVValue = MakeFloat4(0.f, 0.f, 1.f, 1.f);
    if (mTexPath != "")
    {
        LoadTextureByPath(mTexPath);
    }

    CreateDefaultVertexIndexBuffer(&mSpriteVertexBuffer,
        &mSpriteIndexBuffer);
}

void ASpriteComponent::CompUpdate(float _deltatime)
{

}

void ASpriteComponent::CompDestory()
{
    
}

void ASpriteComponent::SaveTexturePath(std::string _path)
{
    mTexPath = _path;
}

void ASpriteComponent::LoadTextureByPath(std::string _path)
{
    ID3D11ShaderResourceView* exist =
        GetActorObjOwner()->GetSceneNodePtr()->
        CheckIfTexExist(_path);
    if (!exist)
    {
        mTexture = LoadTexture(_path);
        GetActorObjOwner()->GetSceneNodePtr()->
            InsertNewTex(_path, mTexture);
    }
    else
    {
        mTexture = exist;
    }
}

void ASpriteComponent::DeleteTexture()
{
    if (mFirstTexture)
    {
        UnloadTexture(&mFirstTexture);
    }
    else
    {
        UnloadTexture(&mTexture);
    }
}

ID3D11ShaderResourceView* ASpriteComponent::GetTexture() const
{
    return mTexture;
}

void ASpriteComponent::SetTexWidth(float _width)
{
    if (_width < 0.f)
    {
        _width = -_width;
    }

    mTexWidth = _width;
}

void ASpriteComponent::SetTexHeight(float _height)
{
    if (_height < 0.f)
    {
        _height = -_height;
    }

    mTexHeight = _height;
}

float ASpriteComponent::GetTexWidth() const
{
    return mTexWidth;
}

float ASpriteComponent::GetTexHeight() const
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

void ASpriteComponent::ResetTexture(
    ID3D11ShaderResourceView* _texture)
{
    if (!mFirstTexture)
    {
        mFirstTexture = mTexture;
    }

    mTexture = _texture;
}

void ASpriteComponent::ResetFirstTexture()
{
    if (mFirstTexture)
    {
        mTexture = mFirstTexture;
        mFirstTexture = nullptr;
    }
}

void ASpriteComponent::SetUVValue(Float4 _value)
{
    mUVValue = _value;
}

void ASpriteComponent::DrawASprite()
{
    if (!mVisible)
    {
        return;
    }

    std::string transname = GetComponentName();
    auto offset = transname.rfind("sprite");
    transname.replace(offset, 6, "transform");
    auto transcomp = GetActorObjOwner()->GetAComponent(transname);
    if (!transcomp)
    {
        MY_NN_LOG(LOG_ERROR,
            "cannot find the transform component of [ %s ]\n",
            GetActorObjOwner()->GetObjectName().c_str());

        return;
    }

    Matrix4x4f world = ((ATransformComponent*)transcomp)->
        GetWorldMatrix();
    GetDxHelperPtr()->PassWorldMatrixToVS(&world);

    SetTexture(&mTexture);
    DrawSprite(&mSpriteVertexBuffer, mSpriteIndexBuffer,
        0.f, 0.f, mTexWidth, mTexHeight,
        mUVValue.x, mUVValue.y, mUVValue.z, mUVValue.w,
        mOffsetColor);
}
