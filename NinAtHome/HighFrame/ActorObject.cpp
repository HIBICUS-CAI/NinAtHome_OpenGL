//---------------------------------------------------------------
// File: ActorObject.cpp
// Proj: NinAtHome
// Info: ゲーム世界にACTORを代表する抽象
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "ActorObject.h"
#include "SceneNode.h"
#include "AComponent.h"
#include "ASpriteComponent.h"
#include "ACollisionComponent.h"

ActorObject::ActorObject(std::string _name,
    class SceneNode* _scene, int _order) :
    Object(_name, _scene, STATUS::NEED_INIT), mACompMap({}),
    mACompArray({}), mActorUpdateOrder(_order),
    mChildrenArray({}), mChildrenMap({}),
    mSpriteCompArray({}), mParentActorObject(nullptr)
{
    mACompMap.clear();
    mACompArray.clear();
    mSpriteCompArray.clear();
    mChildrenArray.clear();
    mChildrenMap.clear();
}

ActorObject::~ActorObject()
{

}

AComponent* ActorObject::GetAComponent(std::string _name)
{
    if (mACompMap.find(_name) == mACompMap.end())
    {
        MY_NN_LOG(LOG_MESSAGE,
            "cannot find this Acomponent : [ %s ]\n", _name.c_str());
        return nullptr;
    }

    return mACompMap[_name];
}

void ActorObject::AddAComponent(AComponent* _comp)
{
    bool isInserted = false;
    for (auto comp = mACompArray.begin();
        comp != mACompArray.end(); comp++)
    {
        if ((*comp)->GetACUpdateOrder() >=
            _comp->GetACUpdateOrder())
        {
            mACompArray.insert(comp, _comp);
            isInserted = true;
            break;
        }
    }
    if (!isInserted)
    {
        mACompArray.push_back(_comp);
    }

    mACompMap.insert(std::make_pair(
        _comp->GetComponentName(), _comp));

    if (_comp->GetComponentName().find("sprite", 0) !=
        _comp->GetComponentName().npos)
    {
        bool isSpriteInserted = false;
        for (auto comp = mSpriteCompArray.begin();
            comp != mSpriteCompArray.end(); comp++)
        {
            if (((*comp))->GetDrawOrder() >=
                ((ASpriteComponent*)_comp)->GetDrawOrder())
            {
                mSpriteCompArray.insert(comp,
                    (ASpriteComponent*)_comp);
                isSpriteInserted = true;
                break;
            }
        }
        if (!isSpriteInserted)
        {
            mSpriteCompArray.push_back((ASpriteComponent*)_comp);
        }
    }
}

int ActorObject::GetUpdateOrder() const
{
    return mActorUpdateOrder;
}

void ActorObject::Init()
{
    for (auto& comp : mACompArray)
    {
        comp->CompInit();
        comp->SetCompActive(STATUS::ACTIVE);
    }
}

void ActorObject::Update(float _deltatime)
{

}

void ActorObject::UpdateComponents(float _deltatime)
{
    if (IsObjectActive() == STATUS::ACTIVE)
    {
        for (auto& comp : mACompArray)
        {
            if (comp->IsCompActive() == STATUS::ACTIVE)
            {
                comp->CompUpdate(_deltatime);
            }
        }
    }
}

void ActorObject::Destory()
{
    while (mACompArray.size())
    {
        auto comp = mACompArray.back();
        comp->CompDestory();
        delete comp;
        mACompArray.pop_back();
    }

    mACompMap.clear();

    mSpriteCompArray.clear();

    mChildrenMap.clear();

    mChildrenArray.clear();
}

void ActorObject::AddChild(ActorObject* _obj)
{
    _obj->SetObjectActive(STATUS::NEED_INIT);

    mChildrenArray.push_back(_obj);

    mChildrenMap.insert(std::make_pair(_obj->GetObjectName(),
        _obj));

    GetSceneNodePtr()->AddActorObject(_obj);
}

void ActorObject::AddParent(ActorObject* _obj)
{
    mParentActorObject = _obj;
}

void ActorObject::ClearParent()
{
    mParentActorObject = nullptr;
}

void ActorObject::ClearChild(std::string _name)
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

void ActorObject::ClearChildren()
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

ActorObject* ActorObject::GetChild(std::string _name)
{
    if (mChildrenMap.find(_name) == mChildrenMap.end())
    {
        MY_NN_LOG(LOG_WARNING,
            "cannot find this child : [ %s ]\n", _name.c_str());
        return nullptr;
    }

    return mChildrenMap[_name];
}

std::vector<ActorObject*>* ActorObject::GetChildrenArray()
{
    return &mChildrenArray;
}

std::vector<ASpriteComponent*>* ActorObject::GetSpriteArray()
{
    return &mSpriteCompArray;
}

ActorObject* ActorObject::GetParent() const
{
    return mParentActorObject;
}

void ActorObject::Draw()
{
    for (auto& sc : mSpriteCompArray)
    {
        if (sc->IsCompActive() == STATUS::ACTIVE)
        {
            sc->DrawASprite();
        }
    }

    auto acc = (ACollisionComponent*)(GetAComponent(
        GetObjectName() + "-collision"));
    if (acc && (acc->IsCompActive() == STATUS::ACTIVE))
    {
        acc->DrawACollision();
    }
}
