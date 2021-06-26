//---------------------------------------------------------------
// File: Object.h
// Proj: NinAtHome
// Info: ゲーム世界にものを代表する抽象
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include <string>
#include "HFCommon.h"

class Object
{
public:
    Object(std::string _name,
        class SceneNode* _scene, STATUS _active);
    virtual ~Object();

    std::string GetObjectName() const;

    STATUS IsObjectActive() const;

    void SetObjectActive(STATUS _active);

    class SceneNode* GetSceneNodePtr() const;

public:
    virtual void Init() = 0;

    virtual void Update(float _deltatime) = 0;

    virtual void UpdateComponents(float _deltatime) = 0;

    virtual void Destory() = 0;

private:
    const std::string mName;

    STATUS mActive;

    class SceneNode* mSceneNodePtr;
};

