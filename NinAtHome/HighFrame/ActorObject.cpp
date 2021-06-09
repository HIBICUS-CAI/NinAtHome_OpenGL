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

ActorObject::ActorObject(std::string _name,
    class SceneNode* _scene, int _order) :
    Object(_name, _scene, STATUS::NEED_INIT), mACompMap({}),
    mACompArray({}), mActorUpdateOrder(_order)
{
    mACompMap.clear();
    mACompArray.clear();
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
