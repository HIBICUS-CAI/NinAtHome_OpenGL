//---------------------------------------------------------------
// File: ATransformComponent.cpp
// Proj: NinAtHome
// Info: ACTORオブジェクトに動く位置に関してのコンポーネント
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "ATransformComponent.h"
#include "ActorObject.h"
#include "SceneNode.h"

ATransformComponent::ATransformComponent(std::string _name,
    ActorObject* _owner, int _order, Float3 _initValue) :
    AComponent(_name, _owner, _order),
    mPosition(_initValue), mRotation(_initValue),
    mScale(MakeFloat3(1.f, 1.f, 1.f)), mWorldMatrix(Matrix4x4f())
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
    if (GetActorObjOwner()->GetChildrenArray()->size())
    {
        for (auto& child :
            *(GetActorObjOwner()->GetChildrenArray()))
        {
            std::string childName = child->GetObjectName();
            if (child->GetSpriteArray()->size() > 1)
            {
                for (int i = 0;
                    i < child->GetSpriteArray()->size(); i++)
                {
                    childName = childName + "-transform-" +
                        std::to_string(i + 1);
                    auto comp = child->GetAComponent(childName);
                    if (!comp)
                    {
                        return;
                    }
                    ATransformComponent* atc =
                        (ATransformComponent*)comp;
                    atc->Translate(_pos);
                }
            }
            else
            {
                childName = childName + "-transform";
                auto comp = child->GetAComponent(childName);
                if (!comp)
                {
                    return;
                }
                ATransformComponent* atc =
                    (ATransformComponent*)comp;
                atc->Translate(_pos);
            }
        }
    }

    mPosition.x += _pos.x;
    mPosition.y += _pos.y;
    mPosition.z += _pos.z;
}

void ATransformComponent::TranslateXAsix(float _posx)
{
    if (GetActorObjOwner()->GetChildrenArray()->size())
    {
        for (auto& child :
            *(GetActorObjOwner()->GetChildrenArray()))
        {
            std::string childName = child->GetObjectName();
            if (child->GetSpriteArray()->size() > 1)
            {
                for (int i = 0;
                    i < child->GetSpriteArray()->size(); i++)
                {
                    childName = childName + "-transform-" +
                        std::to_string(i + 1);
                    auto comp = child->GetAComponent(childName);
                    if (!comp)
                    {
                        return;
                    }
                    ATransformComponent* atc =
                        (ATransformComponent*)comp;
                    atc->TranslateXAsix(_posx);
                }
            }
            else
            {
                childName = childName + "-transform";
                auto comp = child->GetAComponent(childName);
                if (!comp)
                {
                    return;
                }
                ATransformComponent* atc =
                    (ATransformComponent*)comp;
                atc->TranslateXAsix(_posx);
            }
        }
    }

    mPosition.x += _posx;
}

void ATransformComponent::TranslateYAsix(float _posy)
{
    if (GetActorObjOwner()->GetChildrenArray()->size())
    {
        for (auto& child :
            *(GetActorObjOwner()->GetChildrenArray()))
        {
            std::string childName = child->GetObjectName();
            if (child->GetSpriteArray()->size() > 1)
            {
                for (int i = 0;
                    i < child->GetSpriteArray()->size(); i++)
                {
                    childName = childName + "-transform-" +
                        std::to_string(i + 1);
                    auto comp = child->GetAComponent(childName);
                    if (!comp)
                    {
                        return;
                    }
                    ATransformComponent* atc =
                        (ATransformComponent*)comp;
                    atc->TranslateYAsix(_posy);
                }
            }
            else
            {
                childName = childName + "-transform";
                auto comp = child->GetAComponent(childName);
                if (!comp)
                {
                    return;
                }
                ATransformComponent* atc =
                    (ATransformComponent*)comp;
                atc->TranslateYAsix(_posy);
            }
        }
    }

    mPosition.y += _posy;
}

void ATransformComponent::TranslateZAsix(float _posz)
{
    if (GetActorObjOwner()->GetChildrenArray()->size())
    {
        for (auto& child :
            *(GetActorObjOwner()->GetChildrenArray()))
        {
            std::string childName = child->GetObjectName();
            if (child->GetSpriteArray()->size() > 1)
            {
                for (int i = 0;
                    i < child->GetSpriteArray()->size(); i++)
                {
                    childName = childName + "-transform-" +
                        std::to_string(i + 1);
                    auto comp = child->GetAComponent(childName);
                    if (!comp)
                    {
                        return;
                    }
                    ATransformComponent* atc =
                        (ATransformComponent*)comp;
                    atc->TranslateZAsix(_posz);
                }
            }
            else
            {
                childName = childName + "-transform";
                auto comp = child->GetAComponent(childName);
                if (!comp)
                {
                    return;
                }
                ATransformComponent* atc =
                    (ATransformComponent*)comp;
                atc->TranslateZAsix(_posz);
            }
        }
    }

    mPosition.z += _posz;
}

void ATransformComponent::Rotate(Float3 _angle)
{
    if (GetActorObjOwner()->GetChildrenArray()->size())
    {
        for (auto& child :
            *(GetActorObjOwner()->GetChildrenArray()))
        {
            std::string childName = child->GetObjectName();
            if (child->GetSpriteArray()->size() > 1)
            {
                for (int i = 0;
                    i < child->GetSpriteArray()->size(); i++)
                {
                    childName = childName + "-transform-" +
                        std::to_string(i + 1);
                    auto comp = child->GetAComponent(childName);
                    if (!comp)
                    {
                        return;
                    }
                    ATransformComponent* atc =
                        (ATransformComponent*)comp;
                    atc->Rotate(_angle);
                }
            }
            else
            {
                childName = childName + "-transform";
                auto comp = child->GetAComponent(childName);
                if (!comp)
                {
                    return;
                }
                ATransformComponent* atc =
                    (ATransformComponent*)comp;
                atc->Rotate(_angle);
            }
        }
    }

    mRotation.x += _angle.x;
    mRotation.y += _angle.y;
    mRotation.z += _angle.z;
}

void ATransformComponent::RotateXAsix(float _anglex)
{
    if (GetActorObjOwner()->GetChildrenArray()->size())
    {
        for (auto& child :
            *(GetActorObjOwner()->GetChildrenArray()))
        {
            std::string childName = child->GetObjectName();
            if (child->GetSpriteArray()->size() > 1)
            {
                for (int i = 0;
                    i < child->GetSpriteArray()->size(); i++)
                {
                    childName = childName + "-transform-" +
                        std::to_string(i + 1);
                    auto comp = child->GetAComponent(childName);
                    if (!comp)
                    {
                        return;
                    }
                    ATransformComponent* atc =
                        (ATransformComponent*)comp;
                    atc->RotateXAsix(_anglex);
                }
            }
            else
            {
                childName = childName + "-transform";
                auto comp = child->GetAComponent(childName);
                if (!comp)
                {
                    return;
                }
                ATransformComponent* atc =
                    (ATransformComponent*)comp;
                atc->RotateXAsix(_anglex);
            }
        }
    }

    mRotation.x += _anglex;
}

void ATransformComponent::RotateYAsix(float _angley)
{
    if (GetActorObjOwner()->GetChildrenArray()->size())
    {
        for (auto& child :
            *(GetActorObjOwner()->GetChildrenArray()))
        {
            std::string childName = child->GetObjectName();
            if (child->GetSpriteArray()->size() > 1)
            {
                for (int i = 0;
                    i < child->GetSpriteArray()->size(); i++)
                {
                    childName = childName + "-transform-" +
                        std::to_string(i + 1);
                    auto comp = child->GetAComponent(childName);
                    if (!comp)
                    {
                        return;
                    }
                    ATransformComponent* atc =
                        (ATransformComponent*)comp;
                    atc->RotateYAsix(_angley);
                }
            }
            else
            {
                childName = childName + "-transform";
                auto comp = child->GetAComponent(childName);
                if (!comp)
                {
                    return;
                }
                ATransformComponent* atc =
                    (ATransformComponent*)comp;
                atc->RotateYAsix(_angley);
            }
        }
    }

    mRotation.y += _angley;
}

void ATransformComponent::RotateZAsix(float _anglez)
{
    if (GetActorObjOwner()->GetChildrenArray()->size())
    {
        for (auto& child :
            *(GetActorObjOwner()->GetChildrenArray()))
        {
            std::string childName = child->GetObjectName();
            if (child->GetSpriteArray()->size() > 1)
            {
                for (int i = 0;
                    i < child->GetSpriteArray()->size(); i++)
                {
                    childName = childName + "-transform-" +
                        std::to_string(i + 1);
                    auto comp = child->GetAComponent(childName);
                    if (!comp)
                    {
                        return;
                    }
                    ATransformComponent* atc =
                        (ATransformComponent*)comp;
                    atc->RotateZAsix(_anglez);
                }
            }
            else
            {
                childName = childName + "-transform";
                auto comp = child->GetAComponent(childName);
                if (!comp)
                {
                    return;
                }
                ATransformComponent* atc =
                    (ATransformComponent*)comp;
                atc->RotateZAsix(_anglez);
            }
        }
    }

    mRotation.z += _anglez;
}

void ATransformComponent::Scale(Float3 _factor)
{
    if (GetActorObjOwner()->GetChildrenArray()->size())
    {
        for (auto& child :
            *(GetActorObjOwner()->GetChildrenArray()))
        {
            std::string childName = child->GetObjectName();
            if (child->GetSpriteArray()->size() > 1)
            {
                for (int i = 0;
                    i < child->GetSpriteArray()->size(); i++)
                {
                    childName = childName + "-transform-" +
                        std::to_string(i + 1);
                    auto comp = child->GetAComponent(childName);
                    if (!comp)
                    {
                        return;
                    }
                    ATransformComponent* atc =
                        (ATransformComponent*)comp;
                    atc->Scale(_factor);
                }
            }
            else
            {
                childName = childName + "-transform";
                auto comp = child->GetAComponent(childName);
                if (!comp)
                {
                    return;
                }
                ATransformComponent* atc =
                    (ATransformComponent*)comp;
                atc->Scale(_factor);
            }
        }
    }

    mScale.x *= _factor.x;
    mScale.y *= _factor.y;
    mScale.z *= _factor.z;
}

void ATransformComponent::Scale(float _factor)
{
    if (GetActorObjOwner()->GetChildrenArray()->size())
    {
        for (auto& child :
            *(GetActorObjOwner()->GetChildrenArray()))
        {
            std::string childName = child->GetObjectName();
            if (child->GetSpriteArray()->size() > 1)
            {
                for (int i = 0;
                    i < child->GetSpriteArray()->size(); i++)
                {
                    childName = childName + "-transform-" +
                        std::to_string(i + 1);
                    auto comp = child->GetAComponent(childName);
                    if (!comp)
                    {
                        return;
                    }
                    ATransformComponent* atc =
                        (ATransformComponent*)comp;
                    atc->Scale(_factor);
                }
            }
            else
            {
                childName = childName + "-transform";
                auto comp = child->GetAComponent(childName);
                if (!comp)
                {
                    return;
                }
                ATransformComponent* atc =
                    (ATransformComponent*)comp;
                atc->Scale(_factor);
            }
        }
    }

    mScale.x *= _factor;
    mScale.y *= _factor;
    mScale.z *= _factor;
}

void ATransformComponent::ScaleXAsix(float _factorx)
{
    if (GetActorObjOwner()->GetChildrenArray()->size())
    {
        for (auto& child :
            *(GetActorObjOwner()->GetChildrenArray()))
        {
            std::string childName = child->GetObjectName();
            if (child->GetSpriteArray()->size() > 1)
            {
                for (int i = 0;
                    i < child->GetSpriteArray()->size(); i++)
                {
                    childName = childName + "-transform-" +
                        std::to_string(i + 1);
                    auto comp = child->GetAComponent(childName);
                    if (!comp)
                    {
                        return;
                    }
                    ATransformComponent* atc =
                        (ATransformComponent*)comp;
                    atc->ScaleXAsix(_factorx);
                }
            }
            else
            {
                childName = childName + "-transform";
                auto comp = child->GetAComponent(childName);
                if (!comp)
                {
                    return;
                }
                ATransformComponent* atc =
                    (ATransformComponent*)comp;
                atc->ScaleXAsix(_factorx);
            }
        }
    }

    mScale.x *= _factorx;
}

void ATransformComponent::ScaleYAsix(float _factory)
{
    if (GetActorObjOwner()->GetChildrenArray()->size())
    {
        for (auto& child :
            *(GetActorObjOwner()->GetChildrenArray()))
        {
            std::string childName = child->GetObjectName();
            if (child->GetSpriteArray()->size() > 1)
            {
                for (int i = 0;
                    i < child->GetSpriteArray()->size(); i++)
                {
                    childName = childName + "-transform-" +
                        std::to_string(i + 1);
                    auto comp = child->GetAComponent(childName);
                    if (!comp)
                    {
                        return;
                    }
                    ATransformComponent* atc =
                        (ATransformComponent*)comp;
                    atc->ScaleYAsix(_factory);
                }
            }
            else
            {
                childName = childName + "-transform";
                auto comp = child->GetAComponent(childName);
                if (!comp)
                {
                    return;
                }
                ATransformComponent* atc =
                    (ATransformComponent*)comp;
                atc->ScaleYAsix(_factory);
            }
        }
    }

    mScale.y *= _factory;
}

void ATransformComponent::ScaleZAsix(float _factorz)
{
    if (GetActorObjOwner()->GetChildrenArray()->size())
    {
        for (auto& child :
            *(GetActorObjOwner()->GetChildrenArray()))
        {
            std::string childName = child->GetObjectName();
            if (child->GetSpriteArray()->size() > 1)
            {
                for (int i = 0;
                    i < child->GetSpriteArray()->size(); i++)
                {
                    childName = childName + "-transform-" +
                        std::to_string(i + 1);
                    auto comp = child->GetAComponent(childName);
                    if (!comp)
                    {
                        return;
                    }
                    ATransformComponent* atc =
                        (ATransformComponent*)comp;
                    atc->ScaleZAsix(_factorz);
                }
            }
            else
            {
                childName = childName + "-transform";
                auto comp = child->GetAComponent(childName);
                if (!comp)
                {
                    return;
                }
                ATransformComponent* atc =
                    (ATransformComponent*)comp;
                atc->ScaleZAsix(_factorz);
            }
        }
    }

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

    Float3 relative = MakeFloat3(0.f, 0.f, 0.f);
    relative = GetActorObjOwner()->GetSceneNodePtr()->
        GetCamera()->GetRelativePosWithCam(mPosition);

    Float4x4 world = DirectX::XMLoadFloat4x4(&mWorldMatrix);
    static const float PI = 3.14156f;
    Float3 angle = MakeFloat3(
        mRotation.x * PI / 180.f,
        mRotation.y * PI / 180.f,
        mRotation.z * PI / 180.f);

    world = DirectX::XMMatrixMultiply(
        DirectX::XMMatrixScaling(mScale.x, mScale.y, mScale.z),
        DirectX::XMMatrixRotationRollPitchYaw(
            angle.x, angle.y, angle.z)
    );
    world = DirectX::XMMatrixMultiply(
        world,
        DirectX::XMMatrixTranslation(
            relative.x, relative.y, relative.z)
    );
    world = DirectX::XMMatrixTranspose(world);

    DirectX::XMStoreFloat4x4(&mWorldMatrix, world);
}
