//---------------------------------------------------------------
// File: PropertyNode.cpp
// Proj: NinAtHome
// Info: ロード用プロパティ節点
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "PropertyNode.h"

PropertyNode::PropertyNode(std::string _name, std::string _path) :
    mName(_name), mObjectType(OBJ_TYPE::NULLTYPE),
    mComponentSet({})
{
    mComponentSet.clear();
}

PropertyNode::~PropertyNode()
{

}

std::string PropertyNode::GetPropertyName() const
{
    return mName;
}

void PropertyNode::LoadPropertyFile(std::string _path)
{

}
