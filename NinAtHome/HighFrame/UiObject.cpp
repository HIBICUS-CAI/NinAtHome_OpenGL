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
    mChildrenArray({}), mChildrenMap({}),
    mParentUiObject(nullptr), mSpriteCompArray({}),
    mTextCompArray({})
{
    mUCompMap.clear();
    mUCompArray.clear();
    mChildrenArray.clear();
    mChildrenMap.clear();
    mSpriteCompArray.clear();
    mTextCompArray.clear();
}

UiObject::~UiObject()
{

}

UComponent* UiObject::GetUComponent(std::string _name)
{
    if (mUCompMap.find(_name) == mUCompMap.end())
    {
        MY_NN_LOG(LOG_MESSAGE,
            "cannot find this Ucomponent : [ %s ]\n", _name.c_str());
        return nullptr;
    }

    return mUCompMap[_name];
}

void UiObject::AddUComponent(UComponent* _comp)
{
    bool isInserted = false;
    for (auto comp = mUCompArray.begin();
        comp != mUCompArray.end(); comp++)
    {
        if ((*comp)->GetUCUpdateOrder() >=
            _comp->GetUCUpdateOrder())
        {
            mUCompArray.insert(comp, _comp);
            isInserted = true;
            break;
        }
    }
    if (!isInserted)
    {
        mUCompArray.push_back(_comp);
    }

    mUCompMap.insert(std::make_pair(
        _comp->GetComponentName(), _comp));

    if (_comp->GetComponentName().find("sprite", 0) !=
        _comp->GetComponentName().npos)
    {
        bool isSpriteInserted = false;
        for (auto comp = mSpriteCompArray.begin();
            comp != mSpriteCompArray.end(); comp++)
        {
            if (((*comp))->GetDrawOrder() >=
                ((USpriteComponent*)_comp)->GetDrawOrder())
            {
                mSpriteCompArray.insert(comp,
                    (USpriteComponent*)_comp);
                isSpriteInserted = true;
                break;
            }
        }
        if (!isSpriteInserted)
        {
            mSpriteCompArray.push_back((USpriteComponent*)_comp);
        }
    }

    if (_comp->GetComponentName().find("text", 0) !=
        _comp->GetComponentName().npos)
    {
        bool isTextInserted = false;
        for (auto comp = mTextCompArray.begin();
            comp != mTextCompArray.end(); comp++)
        {
            if (((*comp))->GetUCUpdateOrder() >=
                ((UTextComponent*)_comp)->GetUCUpdateOrder())
            {
                mTextCompArray.insert(comp,
                    (UTextComponent*)_comp);
                isTextInserted = true;
                break;
            }
        }
        if (!isTextInserted)
        {
            mTextCompArray.push_back((UTextComponent*)_comp);
        }
    }
}

int UiObject::GetUpdateOrder() const
{
    return mUiUpdateOrder;
}

void UiObject::Init()
{
    for (auto& comp : mUCompArray)
    {
        comp->CompInit();
        comp->SetCompActive(STATUS::ACTIVE);
    }
}

void UiObject::Update(float _deltatime)
{

}

void UiObject::UpdateComponents(float _deltatime)
{
    if (IsObjectActive() == STATUS::ACTIVE)
    {
        for (auto& comp : mUCompArray)
        {
            if (comp->IsCompActive() == STATUS::ACTIVE)
            {
                comp->CompUpdate(_deltatime);
            }
        }
    }
}

void UiObject::Destory()
{
    while (mUCompArray.size())
    {
        auto comp = mUCompArray.back();
        comp->CompDestory();
        delete comp;
        mUCompArray.pop_back();
    }

    mUCompMap.clear();

    mSpriteCompArray.clear();

    mTextCompArray.clear();

    mChildrenMap.clear();

    mChildrenArray.clear();
}

void UiObject::AddChild(UiObject* _obj)
{
    _obj->SetObjectActive(STATUS::NEED_INIT);

    mChildrenArray.push_back(_obj);

    mChildrenMap.insert(std::make_pair(_obj->GetObjectName(),
        _obj));

    GetSceneNodePtr()->AddUiObject(_obj);
}

void UiObject::AddParent(UiObject* _obj)
{
    mParentUiObject = _obj;
}

void UiObject::ClearParent()
{
    mParentUiObject = nullptr;
}

void UiObject::ClearChild(std::string _name)
{
    if (mChildrenMap.find(_name) == mChildrenMap.end())
    {
        MY_NN_LOG(LOG_WARNING,
            "cannot find this child : [ %s ]\n", _name.c_str());
        return;
    }

    if (mChildrenMap[_name]->GetChildrenArray()->size())
    {
        mChildrenMap[_name]->ClearChildren();
    }

    for (auto child = mChildrenArray.begin();
        child != mChildrenArray.end(); child++)
    {
        if ((*child)->GetObjectName() == _name)
        {
            (*child)->SetObjectActive(STATUS::PAUSE);
            mChildrenArray.erase(child);
            break;
        }
    }

    mChildrenMap.erase(_name);
}

void UiObject::ClearChildren()
{
    for (auto& child : mChildrenArray)
    {
        if (child->GetChildrenArray()->size())
        {
            child->ClearChildren();
        }
        child->SetObjectActive(STATUS::PAUSE);
    }

    mChildrenArray.clear();

    mChildrenMap.clear();
}

UiObject* UiObject::GetChild(std::string _name)
{
    if (mChildrenMap.find(_name) == mChildrenMap.end())
    {
        MY_NN_LOG(LOG_WARNING,
            "cannot find this child : [ %s ]\n", _name.c_str());
        return nullptr;
    }

    return mChildrenMap[_name];
}

std::vector<UiObject*>* UiObject::GetChildrenArray()
{
    return &mChildrenArray;
}

std::vector<USpriteComponent*>* UiObject::GetSpriteArray()
{
    return &mSpriteCompArray;
}

std::vector<UTextComponent*>* UiObject::GetTextArray()
{
    return &mTextCompArray;
}

UiObject* UiObject::GetParent() const
{
    return mParentUiObject;
}

void UiObject::Draw()
{
    for (auto& sc : mSpriteCompArray)
    {
        if (sc->IsCompActive() == STATUS::ACTIVE)
        {
            sc->DrawUSprite();
        }
    }

    for (auto& tc : mTextCompArray)
    {
        if (tc->IsCompActive() == STATUS::ACTIVE)
        {
            tc->DrawUText();
        }
    }
}
