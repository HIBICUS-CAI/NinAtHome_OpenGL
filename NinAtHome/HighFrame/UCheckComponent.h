//---------------------------------------------------------------
// File: UCheckComponent.h
// Proj: NinAtHome
// Info: UI¥ª¥Ö¥¸¥§¥¯¥È¤ËÅÐ¶¨¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "UComponent.h"

// TEMP---------------
using UiCheckFuncType = void (*)();
// TEMP---------------

class UCheckComponent :
    public UComponent
{
public:
    UCheckComponent(std::string _name, class UiObject* _owner,
        int _order);
    virtual ~UCheckComponent();

    void SetCheckFunc(UiCheckFuncType _func);

    void ClearCheckFunc();

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    UiCheckFuncType mCheckFuncPtr;
};

