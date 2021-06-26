//---------------------------------------------------------------
// File: AComponent.h
// Proj: NinAtHome
// Info: ACTORオブジェクトに搭載されるコンポーネント
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "Component.h"

class AComponent :
    public Component
{
public:
    AComponent(std::string _name,
        class ActorObject* _owner, int _order);
    virtual ~AComponent();

    class ActorObject* GetActorObjOwner() const;

    int GetACUpdateOrder() const;

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    class ActorObject* mAObjectOwner;

    int mACUpdateOrder;
};

