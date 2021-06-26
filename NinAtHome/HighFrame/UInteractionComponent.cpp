//---------------------------------------------------------------
// File: UInteractionComponent.cpp
// Proj: NinAtHome
// Info: UIオブジェクトに自身特有に関してのコンポーネント
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "UInteractionComponent.h"
#include "UiObject.h"

UInteractionComponent::UInteractionComponent(std::string _name,
    UiObject* _owner, int _order) :
    UComponent(_name, _owner, _order), mInterInitFuncPtr(nullptr),
    mInterUpdateFuncPtr(nullptr), mInterDestoryFuncPtr(nullptr)
{

}

UInteractionComponent::~UInteractionComponent()
{

}

void UInteractionComponent::CompInit()
{
    if (mInterInitFuncPtr)
    {
        mInterInitFuncPtr(this);
    }
}

void UInteractionComponent::CompUpdate(float _deltatime)
{
    if (mInterUpdateFuncPtr)
    {
        mInterUpdateFuncPtr(this, _deltatime);
    }
}

void UInteractionComponent::CompDestory()
{
    if (mInterDestoryFuncPtr)
    {
        mInterDestoryFuncPtr(this);
    }
}

void UInteractionComponent::SetInitFunc(
    UiInterInitFuncType _func)
{
    mInterInitFuncPtr = _func;
}

void UInteractionComponent::SetUpdateFunc(
    UiInterUpdateFuncType _func)
{
    mInterUpdateFuncPtr = _func;
}

void UInteractionComponent::SetDestoryFunc(
    UiInterDestoryFuncType _func)
{
    mInterDestoryFuncPtr = _func;
}

void UInteractionComponent::ClearInitFunc()
{
    mInterInitFuncPtr = nullptr;
}

void UInteractionComponent::ClearUpdateFunc()
{
    mInterUpdateFuncPtr = nullptr;
}

void UInteractionComponent::ClearDestoryFunc()
{
    mInterDestoryFuncPtr = nullptr;
}
