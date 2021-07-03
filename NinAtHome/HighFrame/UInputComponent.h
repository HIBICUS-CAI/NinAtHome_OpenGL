//---------------------------------------------------------------
// File: UInputComponent.h
// Proj: NinAtHome
// Info: UIオブジェクトに入力に関してのコンポーネント
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "UComponent.h"

class UInputComponent :
    public UComponent
{
public:
    UInputComponent(std::string _name, class UiObject* _owner,
        int _order);
    virtual ~UInputComponent();

    void SetInputProcessFunc(UiInputProcessFuncType _func);

    void ClearInputProcessFunc();

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    UiInputProcessFuncType mInputProcessFuncPtr;
};
