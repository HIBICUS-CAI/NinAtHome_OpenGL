//---------------------------------------------------------------
// File: AInputComponent.h
// Proj: NinAtHome
// Info: ACTOR•™•÷•∏•ß•Ø•»§À»Î¡¶§ÀÈv§∑§∆§Œ•≥•Û•›©`•Õ•Û•»
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "AComponent.h"

using ActorInputProcessFuncType = void(*)(
    class AInputComponent*, float);

class AInputComponent :
    public AComponent
{
public:
    AInputComponent(std::string _name, class ActorObject* _owner,
        int _order);
    virtual ~AInputComponent();

    void SetInputProcessFunc(ActorInputProcessFuncType _func);

    void ClearInputProcessFunc();

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    ActorInputProcessFuncType mInputProcessFuncPtr;
};
