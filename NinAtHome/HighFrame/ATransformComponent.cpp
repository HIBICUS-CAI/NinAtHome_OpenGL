//---------------------------------------------------------------
// File: ATransformComponent.cpp
// Proj: NinAtHome
// Info: ACTOR¥ª¥Ö¥¸¥§¥¯¥È¤Ë„Ó¤¯Î»ÖÃ¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "ATransformComponent.h"
#include "ActorObject.h"

ATransformComponent::ATransformComponent(std::string _name,
    ActorObject* _owner, int _order, Float3 _initValue) :
    AComponent(_name, _owner, _order),
    mPosition(_initValue), mRotation(_initValue),
    mScale(_initValue), mWorldMatrixPtr(nullptr),
    mWorldMatrix({})
{

}

ATransformComponent::~ATransformComponent()
{

}

void ATransformComponent::CompInit()
{

}

void ATransformComponent::CompUpdate(float _deltatime)
{

}

void ATransformComponent::CompDestory()
{

}

void ATransformComponent::SetPosition(Float3 _pos)
{
    mPosition = _pos;
}

Float3 ATransformComponent::GetPosition() const
{
    return mPosition;
}

void ATransformComponent::SetRotation(Float3 _angle)
{
    mRotation = _angle;
}

Float3 ATransformComponent::GetRotation() const
{
    return mRotation;
}

void ATransformComponent::SetScale(Float3 _factor)
{
    mScale = _factor;
}

Float3 ATransformComponent::GetScale() const
{
    return mScale;
}

Matrix4x4f ATransformComponent::GetWorldMatrix() const
{
    return mWorldMatrix;
}

Float4x4 ATransformComponent::GetWorldMatrixPtr() const
{
    return mWorldMatrixPtr;
}

void ATransformComponent::Translate(Float3 _pos)
{

}

void ATransformComponent::TranslateXAsix(float _posx)
{

}

void ATransformComponent::TranslateYAsix(float _posy)
{

}

void ATransformComponent::TranslateZAsix(float _posz)
{

}

void ATransformComponent::Rotate(Float3 _angle)
{

}

void ATransformComponent::RotateXAsix(float _anglex)
{

}

void ATransformComponent::RotateYAsix(float _angley)
{

}

void ATransformComponent::RotateZAsix(float _anglez)
{

}

void ATransformComponent::Scale(Float3 _factor)
{

}

void ATransformComponent::Scale(float _factor)
{

}

void ATransformComponent::ScaleXAsix(float _factorx)
{

}

void ATransformComponent::ScaleYAsix(float _factory)
{

}

void ATransformComponent::ScaleZAsix(float _factorz)
{

}

void ATransformComponent::UpdateWorldMatrix()
{

}
