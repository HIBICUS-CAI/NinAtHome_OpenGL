//---------------------------------------------------------------
// File: Object.cpp
// Proj: NinAtHome
// Info: ゲーム世界にものを代表する抽象
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "Object.h"
#include "SceneNode.h"

Object::Object(std::string _name,
    class SceneNode* _scene, STATUS _active) :
    mName(_name), mSceneNodePtr(_scene), mActive(_active)
{

}

Object::~Object()
{

}

std::string Object::GetObjectName() const
{
    return mName;
}

STATUS Object::IsObjectActive() const
{
    return mActive;
}

void Object::SetObjectActive(STATUS _active)
{
    mActive = _active;
}

SceneNode* Object::GetSceneNodePtr() const
{
    return mSceneNodePtr;
}
