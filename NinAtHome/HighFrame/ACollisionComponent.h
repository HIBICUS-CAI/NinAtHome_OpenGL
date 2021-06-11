//---------------------------------------------------------------
// File: ACollisionComponent.h
// Proj: NinAtHome
// Info: ACTOR¥ª¥Ö¥¸¥§¥¯¥È¤Ë¤¢¤¿¤ëÅÐ¶¨¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
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

    bool CheckCollisionWith(class ActorObject* _obj);

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    COLLISION_TYPE mCollisionType;

    Float2 mCollisionSize;

    bool mShowCollisionFlg;
};
