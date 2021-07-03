//---------------------------------------------------------------
// File: UInteractionComponent.h
// Proj: NinAtHome
// Info: UIオブジェクトに自身特有に関してのコンポーネント
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "UComponent.h"

class UInteractionComponent :
    public UComponent
{
public:
    UInteractionComponent(std::string _name,
        class UiObject* _owner, int _order);
    virtual ~UInteractionComponent();

    void SetInitFunc(UiInterInitFuncType _func);

    void SetUpdateFunc(UiInterUpdateFuncType _func);

    void SetDestoryFunc(UiInterDestoryFuncType _func);

    void ClearInitFunc();

    void ClearUpdateFunc();

    void ClearDestoryFunc();

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    UiInterInitFuncType mInterInitFuncPtr;

    UiInterUpdateFuncType mInterUpdateFuncPtr;

    UiInterDestoryFuncType mInterDestoryFuncPtr;
};
