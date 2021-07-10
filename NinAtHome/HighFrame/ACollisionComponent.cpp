//---------------------------------------------------------------
// File: ACollisionComponent.cpp
// Proj: NinAtHome
// Info: ACTORオブジェクトにあたる判定に関してのコンポーネント
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "ACollisionComponent.h"
#include "ActorObject.h"
#include "ATransformComponent.h"
#include "SceneNode.h"
#include "texture.h"
#include "sprite.h"

static const Float4 NOT_COLLIED = MakeFloat4(0.f, 1.f, 0.f, 1.f);
static const Float4 IS_COLLIED = MakeFloat4(1.f, 1.f, 0.f, 1.f);

ACollisionComponent::ACollisionComponent(std::string _name,
    ActorObject* _owner, int _order) :
    AComponent(_name, _owner, _order),
    mCollisionType(COLLISION_TYPE::NULLTYPE),
    mCollisionSize(MakeFloat2(0.f, 0.f)), mShowCollisionFlg(false),
    mCircleTexture(nullptr), mRectangleTexture(nullptr),
    mColliedColor(MakeFloat4(1.f, 1.f, 1.f, 1.f)),
    mColliVertexBuffer(nullptr), mColliIndexBuffer(nullptr)
{

}

ACollisionComponent::~ACollisionComponent()
{

}

void ACollisionComponent::CompInit()
{
    ID3D11ShaderResourceView* exist =
        GetActorObjOwner()->GetSceneNodePtr()->
        CheckIfTexExist("rom:/Assets/Textures/collision-circ.tga");
    if (!exist)
    {
        mCircleTexture = LoadTexture(
            "rom:/Assets/Textures/collision-circ.tga");
        GetActorObjOwner()->GetSceneNodePtr()->
            InsertNewTex(
                "rom:/Assets/Textures/collision-circ.tga",
                mCircleTexture);
    }
    else
    {
        mCircleTexture = exist;
    }

    exist =
        GetActorObjOwner()->GetSceneNodePtr()->
        CheckIfTexExist("rom:/Assets/Textures/collision-rect.tga");
    if (!exist)
    {
        mRectangleTexture = LoadTexture(
            "rom:/Assets/Textures/collision-rect.tga");
        GetActorObjOwner()->GetSceneNodePtr()->
            InsertNewTex(
                "rom:/Assets/Textures/collision-rect.tga",
                mRectangleTexture);
    }
    else
    {
        mRectangleTexture = exist;
    }

    mColliedColor = NOT_COLLIED;

    CreateDefaultVertexIndexBuffer(&mColliVertexBuffer,
        &mColliIndexBuffer);
}

void ACollisionComponent::CompUpdate(float _deltatime)
{
    
}

void ACollisionComponent::CompDestory()
{
    if (mColliVertexBuffer)
    {
        mColliVertexBuffer->Release();
    }
    if (mColliIndexBuffer)
    {
        mColliIndexBuffer->Release();
    }
}

void ACollisionComponent::SetCollisionStatus(COLLISION_TYPE _type,
    Float2 _size, bool _showFlg)
{
    mCollisionType = _type;
    mCollisionSize = _size;
    mShowCollisionFlg = _showFlg;
}

COLLISION_TYPE ACollisionComponent::GetCollisionType() const
{
    return mCollisionType;
}

Float2 ACollisionComponent::GetCollisionSize() const
{
    return mCollisionSize;
}

bool ACollisionComponent::ShouldShowCollision() const
{
    return mShowCollisionFlg;
}

void ACollisionComponent::SetCollisionSize(Float2 _size)
{
    mCollisionSize = _size;
}

void ACollisionComponent::SetCollisionType(COLLISION_TYPE _type)
{
    mCollisionType = _type;
}

void ACollisionComponent::SetColliedColor(bool _isCollied)
{
    if (_isCollied)
    {
        mColliedColor = IS_COLLIED;
    }
    else
    {
        mColliedColor = NOT_COLLIED;
    }
}

void ACollisionComponent::SetShowCollisionFlg(bool _flag)
{
    mShowCollisionFlg = _flag;
}

void ACollisionComponent::DrawACollision()
{
    if (mShowCollisionFlg)
    {
        ATransformComponent* thisAtc = nullptr;
        Float4x4 pworld = Float4x4();
        {
            std::string keywordThisT = "";
            keywordThisT = GetActorObjOwner()->GetObjectName() +
                "-transform";
            thisAtc = (ATransformComponent*)(GetActorObjOwner()->
                GetAComponent(keywordThisT));
            if (!thisAtc)
            {
                MY_NN_LOG(LOG_ERROR,
                    "cannot find transform comp in this obj : [ %s ]\n",
                    GetActorObjOwner()->GetObjectName());
                return;
            }
            Matrix4x4f world = thisAtc->GetWorldMatrix();
            GetDxHelperPtr()->PassWorldMatrixToVS(&world);
        }

        switch (mCollisionType)
        {
        case COLLISION_TYPE::CIRCLE:
            SetTexture(&mCircleTexture);
            DrawSprite(&mColliVertexBuffer, mColliIndexBuffer,
                0.f, 0.f,
                mCollisionSize.x * 2.f, mCollisionSize.y * 2.f,
                0.f, 0.f, 1.f, 1.f, mColliedColor);
            return;
        case COLLISION_TYPE::RECTANGLE:
            SetTexture(&mRectangleTexture);
            DrawSprite(&mColliVertexBuffer, mColliIndexBuffer,
                0.f, 0.f,
                mCollisionSize.x, mCollisionSize.y,
                0.f, 0.f, 1.f, 1.f, mColliedColor);
            return;
        default:
            MY_NN_LOG(LOG_ERROR,
                "this collison type is null in obj : [ %s ]\n",
                GetActorObjOwner()->GetObjectName().c_str());
            return;
        }
    }
}

bool ACollisionComponent::CheckCollisionWith(ActorObject* _obj)
{
    if (GetActorObjOwner()->IsObjectActive() != STATUS::ACTIVE ||
        _obj->IsObjectActive() != STATUS::ACTIVE)
    {
        return false;
    }

    SetColliedColor(false);

    if (!_obj)
    {
        MY_NN_LOG(LOG_ERROR,
            "pass a nullptr obj to this obj name : [ %s ]\n",
            GetActorObjOwner()->GetObjectName().c_str());
        return false;
    }

    ATransformComponent* thisAtc = nullptr;
    ATransformComponent* atc = nullptr;
    ACollisionComponent* acc = nullptr;
    {
        std::string keywordC = "";
        keywordC = _obj->GetObjectName() + "-collision";
        acc = (ACollisionComponent*)(_obj->
            GetAComponent(keywordC));
        if (acc)
        {
            acc->SetColliedColor(false);
        }
    }

    if (_obj->GetChildrenArray()->size())
    {
        for (auto& child : *(_obj->GetChildrenArray()))
        {
            if (CheckCollisionWith(child))
            {
                return true;
            }
        }
    }

    {
        std::string keywordThisT = "";
        std::string keywordT = "";
        keywordThisT = GetActorObjOwner()->GetObjectName() +
            "-transform";
        keywordT = _obj->GetObjectName() + "-transform";
        thisAtc = (ATransformComponent*)(GetActorObjOwner()->
            GetAComponent(keywordThisT));
        atc = (ATransformComponent*)(_obj->
            GetAComponent(keywordT));
    }

    if (!thisAtc)
    {
        MY_NN_LOG(LOG_ERROR,
            "cannot find transform or collison comp in this obj : [ %s ]\n",
            GetActorObjOwner()->GetObjectName());
        return false;
    }
    if (!(atc && acc))
    {
        MY_NN_LOG(LOG_ERROR,
            "cannot find transform or collison comp in this obj : [ %s ]\n",
            _obj->GetObjectName());
        return false;
    }

    bool result = ClacCollisonWith(thisAtc, atc, acc);
    SetColliedColor(result);
    acc->SetColliedColor(result);

    return result;
}

bool ACollisionComponent::ClacCollisonWith(
    const ATransformComponent* _thisAtc,
    const ATransformComponent* _atc,
    const ACollisionComponent* _acc)
{
    Float3 thisPos = _thisAtc->GetPosition();
    Float3 thatPos = _atc->GetPosition();
    Float2 thisSize = mCollisionSize;
    Float2 thatSize = _acc->GetCollisionSize();
    thisSize.x *= _thisAtc->GetScale().x;
    thisSize.y *= _thisAtc->GetScale().y;
    thatSize.x *= _atc->GetScale().x;
    thatSize.y *= _atc->GetScale().y;

    switch (mCollisionType)
    {
    case COLLISION_TYPE::CIRCLE:
        if (_acc->GetCollisionType() == COLLISION_TYPE::CIRCLE)
        {
            return ClacC2C(thisPos, thatPos, thisSize, thatSize);
        }
        else if (_acc->GetCollisionType() == COLLISION_TYPE::RECTANGLE)
        {
            return ClacC2R(thisPos, thatPos, thisSize, thatSize);
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "this collison type is null in obj : [ %s ]\n",
                _acc->GetActorObjOwner()->GetObjectName().c_str());
            return false;
        }

    case COLLISION_TYPE::RECTANGLE:
        if (_acc->GetCollisionType() == COLLISION_TYPE::CIRCLE)
        {
            return ClacR2C(thisPos, thatPos, thisSize, thatSize);
        }
        else if (_acc->GetCollisionType() == COLLISION_TYPE::RECTANGLE)
        {
            return ClacR2R(thisPos, thatPos, thisSize, thatSize);
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "this collison type is null in obj : [ %s ]\n",
                _acc->GetActorObjOwner()->GetObjectName().c_str());
            return false;
        }

    default:
        MY_NN_LOG(LOG_ERROR,
            "this collison type is null in obj : [ %s ]\n",
            GetActorObjOwner()->GetObjectName().c_str());
        return false;
    }
}

bool ACollisionComponent::ClacC2C(
    Float3 _thisPos, Float3 _thatPos,
    Float2 _thisSize, Float2 _thatSize)
{
    float thisR = _thisSize.x;
    float thatR = _thatSize.x;
    Float2 thisP = MakeFloat2(_thisPos.x, _thisPos.y);
    Float2 thatP = MakeFloat2(_thatPos.x, _thatPos.y);

    if ((thatP.x - thisP.x) * (thatP.x - thisP.x) +
        (thatP.y - thisP.y) * (thatP.y - thisP.y) <
        (thisR + thatR) * (thisR + thatR))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ACollisionComponent::ClacC2R(
    Float3 _thisPos, Float3 _thatPos,
    Float2 _thisSize, Float2 _thatSize)
{
    float deltaX = _thisPos.x - _thatPos.x;
    float deltaY = _thisPos.y - _thatPos.y;
    float boxW = _thatSize.x;
    float boxH = _thatSize.y + 2.f * _thisSize.x;
    if (deltaX < 0.f)
    {
        deltaX = -deltaX;
    }
    if (deltaY < 0.f)
    {
        deltaY = -deltaY;
    }

    if (deltaX < (boxW / 2.f) && deltaY < (boxH / 2.f))
    {
        return true;
    }

    boxW = _thatSize.x + 2.f * _thisSize.x;
    boxH = _thatSize.y;

    if (deltaX < (boxW / 2.f) && deltaY < (boxH / 2.f))
    {
        return true;
    }

    deltaX = _thisPos.x - _thatPos.x;
    deltaY = _thisPos.y - _thatPos.y;
    if (deltaX > 0.f)
    {
        deltaX -= (_thatSize.x / 2.f);
    }
    else
    {
        deltaX += (_thatSize.x / 2.f);
    }
    if (deltaY > 0.f)
    {
        deltaY -= (_thatSize.y / 2.f);
    }
    else
    {
        deltaY += (_thatSize.y / 2.f);
    }
    if (deltaX * deltaX + deltaY * deltaY <
        _thisSize.x * _thisSize.x)
    {
        return true;
    }

    return false;
}

bool ACollisionComponent::ClacR2C(
    Float3 _thisPos, Float3 _thatPos,
    Float2 _thisSize, Float2 _thatSize)
{
    float deltaX = _thatPos.x - _thisPos.x;
    float deltaY = _thatPos.y - _thisPos.y;
    float boxW = _thisSize.x;
    float boxH = _thisSize.y + 2.f * _thatSize.x;
    if (deltaX < 0.f)
    {
        deltaX = -deltaX;
    }
    if (deltaY < 0.f)
    {
        deltaY = -deltaY;
    }

    if (deltaX < (boxW / 2.f) && deltaY < (boxH / 2.f))
    {
        return true;
    }

    boxW = _thisSize.x + 2.f * _thatSize.x;
    boxH = _thisSize.y;

    if (deltaX < (boxW / 2.f) && deltaY < (boxH / 2.f))
    {
        return true;
    }

    deltaX = _thatPos.x - _thisPos.x;
    deltaY = _thatPos.y - _thisPos.y;
    if (deltaX > 0.f)
    {
        deltaX -= (_thisSize.x / 2.f);
    }
    else
    {
        deltaX += (_thisSize.x / 2.f);
    }
    if (deltaY > 0.f)
    {
        deltaY -= (_thisSize.y / 2.f);
    }
    else
    {
        deltaY += (_thisSize.y / 2.f);
    }
    if (deltaX * deltaX + deltaY * deltaY <
        _thatSize.x * _thatSize.x)
    {
        return true;
    }

    return false;
}

bool ACollisionComponent::ClacR2R(
    Float3 _thisPos, Float3 _thatPos,
    Float2 _thisSize, Float2 _thatSize)
{
    float deltaSWh = _thisSize.x / 2.f + _thatSize.x / 2.f;
    float deltaSHh = _thisSize.y / 2.f + _thatSize.y / 2.f;
    Float3 deltaPos = MakeFloat3(
        _thatPos.x - _thisPos.x,
        _thatPos.y - _thisPos.y,
        _thatPos.z - _thisPos.z);
    float deltaX = (deltaPos.x > 0 ? deltaPos.x : -deltaPos.x);
    float deltaY = (deltaPos.y > 0 ? deltaPos.y : -deltaPos.y);

    if (deltaX < deltaSWh && deltaY < deltaSHh)
    {
        return true;
    }
    else
    {
        return false;
    }
}
