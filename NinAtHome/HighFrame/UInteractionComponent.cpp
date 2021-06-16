//---------------------------------------------------------------
// File: UInteractionComponent.cpp
// Proj: NinAtHome
// Info: UI���֥������Ȥ��������Ф��v���ƤΥ���ݩ`�ͥ��
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

}

void UInteractionComponent::CompUpdate(float _deltatime)
{

}

void UInteractionComponent::CompDestory()
{

}

void UInteractionComponent::SetInitFunc(UiInterInitFuncType _func)
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