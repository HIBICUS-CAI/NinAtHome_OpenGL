//---------------------------------------------------------------
// File: AInputComponent.h
// Proj: NinAtHome
// Info: ACTOR•™•÷•∏•ß•Ø•»§À»Î¡¶§ÀÈv§∑§∆§Œ•≥•Û•›©`•Õ•Û•»
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "AInputComponent.h"
#include "ActorObject.h"

AInputComponent::AInputComponent(std::string _name,
    ActorObject* _owner, int _order) :
    AComponent(_name, _owner, _order),
    mInputProcessFuncPtr(nullptr)
{

}

AInputComponent::~AInputComponent()
{

}

void AInputComponent::CompInit()
{

}

void AInputComponent::CompUpdate(float _deltatime)
{
    if (mInputProcessFuncPtr)
    {
        mInputProcessFuncPtr(this, _deltatime);
    }
}

void AInputComponent::CompDestory()
{

}

void AInputComponent::SetInputProcessFunc(
    ActorInputProcessFuncType _func)
{
    mInputProcessFuncPtr = _func;
}

void AInputComponent::ClearInputProcessFunc()
{
    mInputProcessFuncPtr = nullptr;
}
