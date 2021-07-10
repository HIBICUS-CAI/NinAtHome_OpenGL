//---------------------------------------------------------------
// File: ACollisionComponent.h
// Proj: NinAtHome
// Info: ACTORオブジェクトにあたる判定に関してのコンポーネント
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "AComponent.h"

enum class COLLISION_TYPE
{
    CIRCLE,
    RECTANGLE,
    NULLTYPE
};

class ACollisionComponent :
    public AComponent
{
public:
    ACollisionComponent(std::string _name,
        class ActorObject* _owner, int _order);
    virtual ~ACollisionComponent();

    void SetCollisionStatus(COLLISION_TYPE _type, Float2 _size,
        bool _showFlg);

    COLLISION_TYPE GetCollisionType() const;

    Float2 GetCollisionSize() const;

    bool ShouldShowCollision() const;

    void SetShowCollisionFlg(bool _flag);

    void SetCollisionSize(Float2 _size);

    void SetCollisionType(COLLISION_TYPE _type);

    void SetColliedColor(bool _isCollied);

    bool CheckCollisionWith(class ActorObject* _obj);

    void DrawACollision();

private:
    bool ClacCollisonWith(
        const class ATransformComponent* _thisAtc,
        const class ATransformComponent* _atc,
        const ACollisionComponent* _acc);

    bool ClacC2C(Float3 _thisPos, Float3 _thatPos,
        Float2 _thisSize, Float2 _thatSize);

    bool ClacC2R(Float3 _thisPos, Float3 _thatPos,
        Float2 _thisSize, Float2 _thatSize);

    bool ClacR2C(Float3 _thisPos, Float3 _thatPos,
        Float2 _thisSize, Float2 _thatSize);

    bool ClacR2R(Float3 _thisPos, Float3 _thatPos,
        Float2 _thisSize, Float2 _thatSize);

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    COLLISION_TYPE mCollisionType;

    Float2 mCollisionSize;

    bool mShowCollisionFlg;

    ID3D11ShaderResourceView* mCircleTexture;

    ID3D11ShaderResourceView* mRectangleTexture;

    Float4 mColliedColor;

    ID3D11Buffer* mColliVertexBuffer;

    ID3D11Buffer* mColliIndexBuffer;
};
