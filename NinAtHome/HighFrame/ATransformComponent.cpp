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
#ifndef NIN_AT_HOME
#include <TP\glm\glm.hpp>
#include <TP\glm\gtc\type_ptr.hpp>
#endif // !NIN_AT_HOME


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
        for (auto child :
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
        for (auto child :
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
        for (auto child :
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
        for (auto child :
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
        for (auto child :
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
        for (auto child :
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
        for (auto child :
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
        for (auto child :
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
        for (auto child :
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
        for (auto child :
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
        for (auto child :
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
        for (auto child :
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
        for (auto child :
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

#ifdef NIN_AT_HOME
    mWorldMatrix = glm::translate(mWorldMatrix, relative);
    mWorldMatrix = glm::rotate(mWorldMatrix,
        glm::radians(mRotation.x), Float3(1.f, 0.f, 0.f));
    mWorldMatrix = glm::rotate(mWorldMatrix,
        glm::radians(mRotation.y), Float3(0.f, 1.f, 0.f));
    mWorldMatrix = glm::rotate(mWorldMatrix,
        glm::radians(mRotation.z), Float3(0.f, 0.f, 1.f));
    mWorldMatrix = glm::scale(mWorldMatrix, mScale);
#else
    glm::fmat4x4 world =
    {
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    };
    world = glm::translate(world, mPosition);
    world = glm::rotate(world,
        glm::radians(mRotation.x), Float3(1.f, 0.f, 0.f));
    world = glm::rotate(world,
        glm::radians(mRotation.y), Float3(0.f, 1.f, 0.f));
    world = glm::rotate(world,
        glm::radians(mRotation.z), Float3(0.f, 0.f, 1.f));
    world = glm::scale(world, mScale);
    float* matArray = glm::value_ptr(world);
    mWorldMatrix =
    {
        matArray[0],matArray[1],matArray[2],matArray[3],
        matArray[4],matArray[5],matArray[6],matArray[7],
        matArray[8],matArray[9],matArray[10],matArray[11],
        matArray[12],matArray[13],matArray[14],matArray[15]
    };
#endif // NIN_AT_HOME
}
