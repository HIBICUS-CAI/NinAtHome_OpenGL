//---------------------------------------------------------------
// File: ActorObject.h
// Proj: NinAtHome
// Info: ゲーム世界にACTORを代表する抽象
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "Object.h"
#include <vector>
#include <unordered_map>

class ActorObject :
    public Object
{
public:
    ActorObject(std::string _name,
        class SceneNode* _scene, int _order);
    virtual ~ActorObject();

    class AComponent* GetAComponent(std::string _name);

    void AddAComponent(class AComponent* _comp);

    int GetUpdateOrder() const;

    void AddChild(ActorObject* _obj);

    void AddParent(ActorObject* _obj);

    void ClearParent();

    void ClearChild(std::string _name);

    void ClearChildren();

    ActorObject* GetChild(std::string _name);

    std::vector<ActorObject*>* GetChildrenArray();

    std::vector<class ASpriteComponent*>* GetSpriteArray();

    ActorObject* GetParent() const;

    void Draw();

public:
    virtual void Init();

    virtual void Update(float _deltatime);

    virtual void UpdateComponents(float _deltatime);

    virtual void Destory();

private:
    std::unordered_map<std::string, class AComponent*> mACompMap;

    std::vector<class AComponent*> mACompArray;

    std::vector<class ASpriteComponent*> mSpriteCompArray;

    int mActorUpdateOrder;

    ActorObject* mParentActorObject;

    std::unordered_map<std::string, ActorObject*> mChildrenMap;

    std::vector<ActorObject*> mChildrenArray;
};

