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

bool PropertyManager::StartUp()
{
    bool result = true;

    return result;
}

void PropertyManager::CleanAndStop()
{

}

PropertyNode* PropertyManager::GetPropertyNode(std::string _name)
{
    if (mPropertyMap.find(_name) == mPropertyMap.end())
    {
        MY_NN_LOG(LOG_WARNING,
            "cannot find this property node : [ %s ]\n", _name.c_str());
        return nullptr;
    }

    return mPropertyMap[_name];
}
