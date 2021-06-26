//---------------------------------------------------------------
// File: UInputComponent.cpp
// Proj: NinAtHome
// Info: UIオブジェクトに入力に関してのコンポーネント
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "UInputComponent.h"
#include "UiObject.h"

UInputComponent::UInputComponent(std::string _name,
    UiObject* _owner, int _order) :
    UComponent(_name, _owner, _order),
    mInputProcessFuncPtr(nullptr)
{

}

UInputComponent::~UInputComponent()
{

}

void UInputComponent::CompInit()
{

}

void UInputComponent::CompUpdate(float _deltatime)
{
    if (mInputProcessFuncPtr)
    {
        mInputProcessFuncPtr(this, _deltatime);
    }
}

void UInputComponent::CompDestory()
{

}

void UInputComponent::SetInputProcessFunc(
    UiInputProcessFuncType _func)
{
    mInputProcessFuncPtr = _func;
}

void UInputComponent::ClearInputProcessFunc()
{
    mInputProcessFuncPtr = nullptr;
}
