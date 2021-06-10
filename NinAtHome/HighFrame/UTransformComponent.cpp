//---------------------------------------------------------------
// File: UTransformComponent.cpp
// Proj: NinAtHome
// Info: UI¥ª¥Ö¥¸¥§¥¯¥È¤Ë„Ó¤¯Î»ÖÃ¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "UTransformComponent.h"
#include "UiObject.h"

UTransformComponent::UTransformComponent(std::string _name,
    UiObject* _owner, int _order, Float3 _initValue) :
    UComponent(_name, _owner, _order),
    mPosition(_initValue), mRotation(_initValue),
    mScale(_initValue), mWorldMatrixPtr(nullptr),
    mWorldMatrix({})
{

}

UTransformComponent::~UTransformComponent()
{

}

void UTransformComponent::CompInit()
{

}

void UTransformComponent::CompUpdate(float _deltatime)
{

}

void UTransformComponent::CompDestory()
{

}

void UTransformComponent::SetPosition(Float3 _pos)
{
    mPosition = _pos;
}

Float3 UTransformComponent::GetPosition() const
{
    return mPosition;
}

void UTransformComponent::SetRotation(Float3 _angle)
{
    mRotation = _angle;
}

Float3 UTransformComponent::GetRotation() const
{
    return mRotation;
}

void UTransformComponent::SetScale(Float3 _factor)
{
    mScale = _factor;
}

Float3 UTransformComponent::GetScale() const
{
    return mScale;
}

Matrix4x4f UTransformComponent::GetWorldMatrix() const
{
    return mWorldMatrix;
}

Float4x4 UTransformComponent::GetWorldMatrixPtr() const
{
    return mWorldMatrixPtr;
}

void UTransformComponent::Translate(Float3 _pos)
{

}

void UTransformComponent::TranslateXAsix(float _posx)
{

}

void UTransformComponent::TranslateYAsix(float _posy)
{

}

void UTransformComponent::TranslateZAsix(float _posz)
{

}

void UTransformComponent::Rotate(Float3 _angle)
{

}

void UTransformComponent::RotateXAsix(float _anglex)
{

}

void UTransformComponent::RotateYAsix(float _angley)
{

}

void UTransformComponent::RotateZAsix(float _anglez)
{

}

void UTransformComponent::Scale(Float3 _factor)
{

}

void UTransformComponent::Scale(float _factor)
{

}

void UTransformComponent::ScaleXAsix(float _factorx)
{

}

void UTransformComponent::ScaleYAsix(float _factory)
{

}

void UTransformComponent::ScaleZAsix(float _factorz)
{

}

void UTransformComponent::UpdateWorldMatrix()
{

}
