//---------------------------------------------------------------
// File: PropertyNode.h
// Proj: NinAtHome
// Info: ロード用オブジェクトプロパティ節点
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "HFCommon.h"
#include <string>
#include <vector>

class PropertyNode
{
public:
    PropertyNode(std::string _name, std::string _path);
    ~PropertyNode();

    std::string GetPropertyName() const;

private:
    void LoadPropertyFile(std::string _path);

private:
    const std::string mName;

    OBJ_TYPE mObjectType;

    std::vector<COMP_TYPE> mComponentSet;
};

