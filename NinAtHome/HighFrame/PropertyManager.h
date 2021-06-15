//---------------------------------------------------------------
// File: PropertyManager.h
// Proj: NinAtHome
// Info: ロード用プロパティ節点管理する機能の対応
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class PropertyManager
{
public:
    PropertyManager();
    ~PropertyManager();

    bool StartUp();

    void CleanAndStop();

    class PropertyNode* GetPropertyNode(std::string _name);

private:
    std::unordered_map<std::string, class PropertyNode*>
        mPropertyMap;
};
