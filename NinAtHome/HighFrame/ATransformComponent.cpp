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
    mScale(MakeFloat3(1.f, 1.f, 1.f)), mWorldMatrix({})
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
    // TODO child's transform!
    UpdateWorldMatrix();
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

void ATransformComponent::Translate(Float3 _pos)
{
    mPosition += _pos;
}

void ATransformComponent::TranslateXAsix(float _posx)
{
    mPosition.x += _posx;
}

void ATransformComponent::TranslateYAsix(float _posy)
{
    mPosition.y += _posy;
}

void ATransformComponent::TranslateZAsix(float _posz)
{
    mPosition.z += _posz;
}

void ATransformComponent::Rotate(Float3 _angle)
{
    mRotation += _angle;
}

void ATransformComponent::RotateXAsix(float _anglex)
{
    mRotation.x += _anglex;
}

void ATransformComponent::RotateYAsix(float _angley)
{
    mRotation.y += _angley;
}

void ATransformComponent::RotateZAsix(float _anglez)
{
    mRotation.z += _anglez;
}

void ATransformComponent::Scale(Float3 _factor)
{
    mScale *= _factor;
}

void ATransformComponent::Scale(float _factor)
{
    mScale.x *= _factor;
    mScale.y *= _factor;
    mScale.z *= _factor;
}

void ATransformComponent::ScaleXAsix(float _factorx)
{
    mScale.x *= _factorx;
}

void ATransformComponent::ScaleYAsix(float _factory)
{
    mScale.y *= _factory;
}

void ATransformComponent::ScaleZAsix(float _factorz)
{
    mScale.z *= _factorz;
}

void ATransformComponent::UpdateWorldMatrix()
{
    mWorldMatrix =
    {
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    };

#ifdef RUN_WITHOUT_NINSDK
    mWorldMatrix = glm::translate(mWorldMatrix, mPosition);
    mWorldMatrix = glm::rotate(mWorldMatrix,
        glm::radians(mRotation.x), Float3(1.f, 0.f, 0.f));
    mWorldMatrix = glm::rotate(mWorldMatrix,
        glm::radians(mRotation.y), Float3(0.f, 1.f, 0.f));
    mWorldMatrix = glm::rotate(mWorldMatrix,
        glm::radians(mRotation.z), Float3(0.f, 0.f, 1.f));
    mWorldMatrix = glm::scale(mWorldMatrix, mScale);
#else

#endif // NIN_AT_HOME
}
