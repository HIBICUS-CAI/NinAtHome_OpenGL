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

    template <typename T>
    inline T* GetAComponent(COMP_TYPE _type)
    {
        static std::string compName = "";
        compName = GetObjectName();
        switch (_type)
        {
        case COMP_TYPE::ATRANSFORM:
            compName += "-transform";
            return (T*)(GetAComponent(compName));

        case COMP_TYPE::ATIMER:
            compName += "-timer";
            return (T*)(GetAComponent(compName));

        case COMP_TYPE::ASPRITE:
            compName += "-sprite";
            return (T*)(GetAComponent(compName));

        case COMP_TYPE::ACOLLISION:
            compName += "-collision";
            return (T*)(GetAComponent(compName));

        case COMP_TYPE::AINPUT:
            compName += "-input";
            return (T*)(GetAComponent(compName));

        case COMP_TYPE::AANIMATE:
            compName += "-animate";
            return (T*)(GetAComponent(compName));

        case COMP_TYPE::AINTERACT:
            compName += "-interaction";
            return (T*)(GetAComponent(compName));

        default:
            MY_NN_LOG(LOG_ERROR,
                "cannot return this component type\n");
            return nullptr;
        }
    }

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

