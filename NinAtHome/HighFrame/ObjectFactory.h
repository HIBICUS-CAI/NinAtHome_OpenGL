//---------------------------------------------------------------
// File: ObjectFactory.h
// Proj: NinAtHome
// Info: ¥ª¥Ö¥¸¥§¥¯¥È¤òÉú³É¤¹¤ë¤Î¥Õ¥¡¥¯¥È¥ê©`
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

private:
    class ActorObject* CreateNewAObject(JsonFile* _file,
        std::string _nodePath, class SceneNode* _scene);

    class UiObject* CreateNewUObject(JsonFile* _file,
        std::string _nodePath, class SceneNode* _scene);

private:
    class PropertyManager* mPropertyManagerPtr;

    class SceneManager* mSceneManagerPtr;
};

