//---------------------------------------------------------------
// File: ObjectFactory.h
// Proj: NinAtHome
// Info: オブジェクトを生成するのファクトリー
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include <string>
#include <unordered_map>
#include "json.h"
#include "HFCommon.h"

class ObjectFactory
{
public:
    ObjectFactory();
    ~ObjectFactory();

    bool StartUp(class PropertyManager* _pmPtr,
        class SceneManager* _smPtr);

    void CleanAndStop();

    class SceneNode* CreateNewScene(std::string _name,
        std::string _configPath);

    void ResetSceneNode(class SceneNode* _scene,
        std::string _configPath);

    std::unordered_map<std::string, ActorInputProcessFuncType>*
        GetActorInputPool();

    std::unordered_map<std::string, UiInputProcessFuncType>*
        GetUiInputPool();

    std::unordered_map<std::string, ActorInterInitFuncType>*
        GetActorInterInitPool();

    std::unordered_map<std::string, ActorInterUpdateFuncType>*
        GetActorInterUpdatePool();

    std::unordered_map<std::string, ActorInterDestoryFuncType>*
        GetActorInterDestoryPool();

    std::unordered_map<std::string, UiInterInitFuncType>*
        GetUiInterInitPool();

    std::unordered_map<std::string, UiInterUpdateFuncType>*
        GetUiInterUpdatePool();

    std::unordered_map<std::string, UiInterDestoryFuncType>*
        GetUiInterDestoryPool();

private:
    class ActorObject* CreateNewAObject(JsonFile* _file,
        std::string _nodePath, class SceneNode* _scene);

    class UiObject* CreateNewUObject(JsonFile* _file,
        std::string _nodePath, class SceneNode* _scene);

    class ActorObject* CreateActorItself(JsonFile* _file,
        std::string _nodePath, class SceneNode* _scene);

    class UiObject* CreateUiItself(JsonFile* _file,
        std::string _nodePath, class SceneNode* _scene);

    void AddACompToActor(class ActorObject* _actor,
        JsonFile* _file, std::string _nodePath);

    void AddUCompToUi(class UiObject* _ui,
        JsonFile* _file, std::string _nodePath);

    void ResetAComp(class ActorObject* _actor,
        JsonFile* _file, std::string _nodePath);

    void ResetUComp(class UiObject* _ui,
        JsonFile* _file, std::string _nodePath);

private:
    class PropertyManager* mPropertyManagerPtr;

    class SceneManager* mSceneManagerPtr;

    std::unordered_map<std::string, ActorInputProcessFuncType>
        mActorInputFunctionPool;

    std::unordered_map<std::string, ActorInterInitFuncType>
        mActorInteractionInitFunctionPool;

    std::unordered_map<std::string, ActorInterUpdateFuncType>
        mActorInteractionUpdateFunctionPool;

    std::unordered_map<std::string, ActorInterDestoryFuncType>
        mActorInteractionDestoryFunctionPool;

    std::unordered_map<std::string, UiInputProcessFuncType>
        mUiInputFunctionPool;

    std::unordered_map<std::string, UiInterInitFuncType>
        mUiInteractionInitFunctionPool;

    std::unordered_map<std::string, UiInterUpdateFuncType>
        mUiInteractionUpdateFunctionPool;

    std::unordered_map<std::string, UiInterDestoryFuncType>
        mUiInteractionDestoryFunctionPool;
};

