//---------------------------------------------------------------
// File: Component.h
// Proj: NinAtHome
// Info: 各オブジェクトに搭載されるコンポーネント抽象
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include <string>
#include "HFCommon.h"

class Component
{
public:
    Component(std::string _name, STATUS _active);
    virtual ~Component();

    std::string GetComponentName() const;

    STATUS IsCompActive() const;

    void SetCompActive(STATUS _active);

public:
    virtual void CompInit() = 0;

    virtual void CompUpdate(float _deltatime) = 0;

    virtual void CompDestory() = 0;

private:
    const std::string mName;

    STATUS mActive;
};

