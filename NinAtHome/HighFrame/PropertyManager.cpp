//---------------------------------------------------------------
// File: PropertyManager.cpp
// Proj: NinAtHome
// Info: ロード用プロパティ節点管理する機能の対応
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "PropertyManager.h"
#include "PropertyNode.h"

PropertyManager::PropertyManager() :mPropertyMap({})
{
    mPropertyMap.clear();
}

PropertyManager::~PropertyManager()
{

}

void PropertyManager::StartUp()
{

}

void PropertyManager::CleanAndStop()
{

}

PropertyNode* PropertyManager::GetPropertyNode(std::string _name)
{
    return mPropertyMap[_name];
}
