//---------------------------------------------------------------
// File: ObjectFactory.cpp
// Proj: NinAtHome
// Info: ¥ª¥Ö¥¸¥§¥¯¥È¤òÉú³É¤¹¤ë¤Î¥Õ¥¡¥¯¥È¥ê©`
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "ObjectFactory.h"
#include "PropertyManager.h"
#include "PropertyNode.h"
#include "SceneManager.h"
#include "SceneNode.h"
#include "ActorObject.h"
#include "UiObject.h"

ObjectFactory::ObjectFactory() :
    mPropertyManagerPtr(nullptr), mSceneManagerPtr(nullptr)
{

}

ObjectFactory::~ObjectFactory()
{

}

bool ObjectFactory::StartUp(PropertyManager* _pmPtr,
    SceneManager* _smPtr)
{
    mPropertyManagerPtr = _pmPtr;
    mSceneManagerPtr = _smPtr;

    bool result = true;

    return result;
}

void ObjectFactory::CleanAndStop()
{

}

ActorObject* ObjectFactory::CreateNewAObject(
    PropertyNode* property)
{
    // TEMP-------------------
    return nullptr;
    // TEMP-------------------
}

UiObject* ObjectFactory::CreateNewUObject(
    PropertyNode* property)
{
    // TEMP-------------------
    return nullptr;
    // TEMP-------------------
}
