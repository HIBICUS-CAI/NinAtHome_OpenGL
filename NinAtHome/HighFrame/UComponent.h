//---------------------------------------------------------------
// File: UComponent.h
// Proj: NinAtHome
// Info: UIオブジェクトに搭載されるコンポーネント
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "Component.h"

class UComponent :
    public Component
{
public:
    UComponent(std::string _name, 
        class UiObject* _owner, int _order);
    virtual ~UComponent();

    class UiObject* GetUiObjOwner() const;

    int GetUCUpdateOrder() const;

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    class UiObject* mUObjectOwner;
    
    int mUCUpdateOrder;
};

