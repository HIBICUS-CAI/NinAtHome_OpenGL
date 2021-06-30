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
#include "json.h"

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
};

