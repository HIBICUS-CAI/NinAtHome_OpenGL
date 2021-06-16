//---------------------------------------------------------------
// File: AInteractionComponent.cpp
// Proj: NinAtHome
// Info: ACTOR���֥������Ȥ��������Ф��v���ƤΥ���ݩ`�ͥ��
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "AInteractionComponent.h"
#include "ActorObject.h"

AInteractionComponent::AInteractionComponent(std::string _name,
    ActorObject* _owner, int _order) :
    AComponent(_name, _owner, _order), mInterInitFuncPtr(nullptr),
    mInterUpdateFuncPtr(nullptr), mInterDestoryFuncPtr(nullptr)
{

}

AInteractionComponent::~AInteractionComponent()
{

}

void AInteractionComponent::CompInit()
{

}

void AInteractionComponent::CompUpdate(float _deltatime)
{

}

void AInteractionComponent::CompDestory()
{

}

void AInteractionComponent::SetInitFunc(
    ActorInterInitFuncType _func)
{
    mInterInitFuncPtr = _func;
}

void AInteractionComponent::SetUpdateFunc(
    ActorInterUpdateFuncType _func)
{
    mInterUpdateFuncPtr = _func;
}

void AInteractionComponent::SetDestoryFunc(
    ActorInterDestoryFuncType _func)
{
    mInterDestoryFuncPtr = _func;
}

void AInteractionComponent::ClearInitFunc()
{
    mInterInitFuncPtr = nullptr;
}

void AInteractionComponent::ClearUpdateFunc()
{
    mInterUpdateFuncPtr = nullptr;
}

void AInteractionComponent::ClearDestoryFunc()
{
    mInterDestoryFuncPtr = nullptr;
}