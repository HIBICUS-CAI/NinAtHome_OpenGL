//---------------------------------------------------------------
// File: UiObject.cpp
// Proj: NinAtHome
// Info: ゲーム世界にUIを代表する抽象
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "UiObject.h"
#include "SceneNode.h"
#include "UComponent.h"
#include "USpriteComponent.h"
#include "UTextComponent.h"

UiObject::UiObject(std::string _name,
    class SceneNode* _scene, int _order) :
    Object(_name, _scene, STATUS::NEED_INIT), mUCompMap({}),
    mUCompArray({}), mUiUpdateOrder(_order),
    mChildrenArray({}), mChildrenMap({}), mParentUiObject(nullptr)
{
    mUCompMap.clear();
    mUCompArray.clear();
    mChildrenArray.clear();
    mChildrenMap.clear();
}

UiObject::~UiObject()
{

}

UComponent* UiObject::GetUComponent(std::string _name)
{
    if (mUCompMap.find(_name) == mUCompMap.end())
    {
        MY_NN_LOG(LOG_WARNING,
            "cannot find this Ucomponent : [ %s ]\n", _name.c_str());
        return nullptr;
    }

    return mUCompMap[_name];
}

void UiObject::AddUComponent(UComponent* _comp)
{

}

int UiObject::GetUpdateOrder() const
{
    return mUiUpdateOrder;
}

void UiObject::Init()
{

}

void UiObject::Update(float _deltatime)
{

}

void UiObject::UpdateComponents(float _deltatime)
{

}

void UiObject::Destory()
{

}

void UiObject::AddChild(UiObject* _obj)
{

}

void UiObject::AddParent(UiObject* _obj)
{

}

void UiObject::ClearParent()
{

}

void UiObject::ClearChild(std::string _name)
{

}

void UiObject::ClearChildren()
{

}

UiObject* UiObject::GetChild(std::string _name)
{
    // TEMP------------------------
    return nullptr;
    // TEMP------------------------
}

std::vector<UiObject*>* UiObject::GetChildrenArray()
{
    return &mChildrenArray;
}

UiObject* UiObject::GetParent() const
{
    return mParentUiObject;
}

void UiObject::Draw()
{
    for (auto sc : mSpriteCompArray)
    {
        sc->DrawUSprite();
    }

    for (auto tc : mTextCompArray)
    {
        tc->DrawUText();
    }
}
