//---------------------------------------------------------------
// File: UiObject.h
// Proj: NinAtHome
// Info: ゲーム世界にUIを代表する抽象
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "Object.h"
#include <vector>
#include <unordered_map>

class UiObject :
    public Object
{
public:
    UiObject(std::string _name,
        class SceneNode* _scene, int _order);
    virtual ~UiObject();

    class UComponent* GetUComponent(std::string _name);

    void AddUComponent(class UComponent* _comp);

    int GetUpdateOrder() const;

public:
    virtual void Init();

    virtual void Update(float _deltatime);

    virtual void UpdateComponents(float _deltatime);

    virtual void Destory();

private:
    std::unordered_map<std::string, class UComponent*> mUCompMap;

    std::vector<class UComponent*> mUCompArray;

    int mUiUpdateOrder;
};

