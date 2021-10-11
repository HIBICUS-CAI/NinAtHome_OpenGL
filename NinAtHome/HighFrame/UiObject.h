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

    template <typename T>
    inline T* GetUComponent(COMP_TYPE _type)
    {
        static std::string compName = "";
        compName = GetObjectName();
        switch (_type)
        {
        case COMP_TYPE::UTRANSFORM:
            compName += "-transform";
            return (T*)(GetUComponent(compName));

        case COMP_TYPE::UINPUT:
            compName += "-input";
            return (T*)(GetUComponent(compName));

        case COMP_TYPE::UTEXT:
            compName += "-text";
            return (T*)(GetUComponent(compName));

        case COMP_TYPE::USPRITE:
            compName += "-sprite";
            return (T*)(GetUComponent(compName));

        case COMP_TYPE::UBTNMAP:
            compName += "-btnmap";
            return (T*)(GetUComponent(compName));

        case COMP_TYPE::UINTERACT:
            compName += "-interaction";
            return (T*)(GetUComponent(compName));

        default:
            MY_NN_LOG(LOG_ERROR,
                "cannot return this component type\n");
            return nullptr;
        }
    }

    void AddUComponent(class UComponent* _comp);

    int GetUpdateOrder() const;

    void AddChild(UiObject* _obj);

    void AddParent(UiObject* _obj);

    void ClearParent();

    void ClearChild(std::string _name);

    void ClearChildren();

    UiObject* GetChild(std::string _name);

    std::vector<UiObject*>* GetChildrenArray();

    std::vector<class USpriteComponent*>* GetSpriteArray();

    std::vector<class UTextComponent*>* GetTextArray();

    UiObject* GetParent() const;

    void Draw();

public:
    virtual void Init();

    virtual void Update(float _deltatime);

    virtual void UpdateComponents(float _deltatime);

    virtual void Destory();

private:
    std::unordered_map<std::string, class UComponent*> mUCompMap;

    std::vector<class UComponent*> mUCompArray;

    std::vector<class USpriteComponent*> mSpriteCompArray;

    std::vector<class UTextComponent*> mTextCompArray;

    int mUiUpdateOrder;

    UiObject* mParentUiObject;

    std::unordered_map<std::string, UiObject*> mChildrenMap;

    std::vector<UiObject*> mChildrenArray;
};

