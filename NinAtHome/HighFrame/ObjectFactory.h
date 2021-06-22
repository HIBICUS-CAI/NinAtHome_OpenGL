//---------------------------------------------------------------
// File: ObjectFactory.h
// Proj: NinAtHome
// Info: ¥ª¥Ö¥¸¥§¥¯¥È¤òÉú³É¤¹¤ë¤Î¥Õ¥¡¥¯¥È¥ê©`
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

class ObjectFactory
{
public:
    ObjectFactory();
    ~ObjectFactory();

    bool StartUp(class PropertyManager* _pmPtr,
        class SceneManager* _smPtr);

    void CleanAndStop();

    // TODO public create new scene node
    // TODO move auobj create to private

    class ActorObject* CreateNewAObject(
        class PropertyNode* _property);

    class UiObject* CreateNewUObject(
        class PropertyNode* _property);

private:
    class PropertyManager* mPropertyManagerPtr;

    class SceneManager* mSceneManagerPtr;
};

