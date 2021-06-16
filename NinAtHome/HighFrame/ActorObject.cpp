//---------------------------------------------------------------
// File: ActorObject.h
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

ActorObject::ActorObject(std::string _name,
    class SceneNode* _scene, int _order) :
    Object(_name, _scene, STATUS::NEED_INIT), mACompMap({}),
    mACompArray({}), mActorUpdateOrder(_order),
    mChildrenArray({}), mChildrenMap({}),
    mParentActorObject(nullptr)
{
    mACompMap.clear();
    mACompArray.clear();
    mChildrenArray.clear();
    mChildrenMap.clear();
}

ActorObject::~ActorObject()
{

}

AComponent* ActorObject::GetAComponent(std::string _name)
{
    return mACompMap[_name];
}

void ActorObject::AddAComponent(AComponent* _comp)
{
    // TEMP-----------------------
    mACompArray.push_back(_comp);
    mACompMap.insert(std::make_pair(
        _comp->GetComponentName(), _comp));
    if (_comp->GetComponentName().find("sprite", 0) !=
        _comp->GetComponentName().npos)
    {
        mSpriteCompArray.push_back((ASpriteComponent*)_comp);
    }
    // TEMP-----------------------
}

int ActorObject::GetUpdateOrder() const
{
    return mActorUpdateOrder;
}

void ActorObject::Init()
{

}

void ActorObject::Update(float _deltatime)
{

}

void ActorObject::UpdateComponents(float _deltatime)
{

}

void ActorObject::Destory()
{

}

void ActorObject::AddChild(ActorObject* _obj)
{

}

void ActorObject::AddParent(ActorObject* _obj)
{

}

void ActorObject::ClearParent()
{

}

void ActorObject::ClearChild(std::string _name)
{

}

void ActorObject::ClearChildren()
{

}

ActorObject* ActorObject::GetChild(std::string _name)
{
    // TEMP------------------------
    return nullptr;
    // TEMP------------------------
}

std::vector<ActorObject*>* ActorObject::GetChildrenArray()
{
    return &mChildrenArray;
}

ActorObject* ActorObject::GetParent() const
{
    return mParentActorObject;
}

void ActorObject::Draw()
{
    for (auto sc : mSpriteCompArray)
    {
        sc->DrawASprite();
    }
}
