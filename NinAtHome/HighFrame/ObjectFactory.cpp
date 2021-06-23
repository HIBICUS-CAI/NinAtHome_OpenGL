//---------------------------------------------------------------
// File: ObjectFactory.cpp
// Proj: NinAtHome
// Info: ¥ª¥Ö¥¸¥§¥¯¥È¤òÉú³É¤¹¤ë¤Î¥Õ¥¡¥¯¥È¥ê©`
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "ObjectFactory.h"
#include "PropertyManager.h"
#include "PropertyNode.h"
#include "SceneManager.h"
#include "SceneNode.h"
#include "ActorObject.h"
#include "UiObject.h"

ObjectFactory::ObjectFactory() :
    mPropertyManagerPtr(nullptr), mSceneManagerPtr(nullptr)
{

}

ObjectFactory::~ObjectFactory()
{

}

bool ObjectFactory::StartUp(PropertyManager* _pmPtr,
    SceneManager* _smPtr)
{
    mPropertyManagerPtr = _pmPtr;
    mSceneManagerPtr = _smPtr;

    bool result = true;

    return result;
}

void ObjectFactory::CleanAndStop()
{

}

SceneNode* ObjectFactory::CreateNewScene(std::string _name,
    std::string _configPath)
{
    JsonFile config = {};
    LoadJsonFile(&config, _configPath);
    if (config.HasParseError())
    {
        MY_NN_LOG(LOG_ERROR,
            "failed to parse json file [ %s ] with error [ %d ]\n",
            _configPath.c_str(), config.GetParseError());
        return nullptr;
    }

    if (config["scene-name"].IsNull() ||
        strcmp(config["scene-name"].GetString(), _name.c_str()))
    {
        MY_NN_LOG(LOG_ERROR,
            "do not have a scene name in config [ %s ]\n",
            _name.c_str());
        return nullptr;
    }
    SceneNode* node = new SceneNode(_name, mSceneManagerPtr);

    // TODO add object here
    if (config.HasMember("actor") &&
        !config["actor"].IsNull() && config["actor"].Size())
    {
        for (unsigned int i = 0; i < config["actor"].Size(); i++)
        {
            node->AddActorObject(
                CreateNewAObject(&config,
                    "/actor/" + std::to_string(i), node));
        }
    }
    if (config.HasMember("ui") &&
        !config["ui"].IsNull() && config["ui"].Size())
    {
        for (unsigned int i = 0; i < config["ui"].Size(); i++)
        {
            node->AddUiObject(
                CreateNewUObject(&config,
                    "/ui/" + std::to_string(i), node));
        }
    }

    return node;
}

ActorObject* ObjectFactory::CreateNewAObject(JsonFile* _file,
    std::string _nodePath, SceneNode* _scene)
{
    ActorObject* aObj = nullptr;
    JsonNode node = nullptr;
    {
        std::string name = "";
        int objOrder = 0;
        node = GetJsonNode(_file, _nodePath + "/actor-name");
        if (node && node->IsString())
        {
            name = node->GetString();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get actor name in [ %s ]\n",
                _nodePath.c_str());
        }
        node = GetJsonNode(_file, _nodePath + "/update-order");
        if (node && node->IsInt())
        {
            objOrder = node->GetInt();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get actor update order in [ %s ]\n",
                _nodePath.c_str());
        }

        aObj = new ActorObject(name, _scene, objOrder);
    }

    return aObj;
}

UiObject* ObjectFactory::CreateNewUObject(JsonFile* _file,
    std::string _nodePath, SceneNode* _scene)
{
    // TEMP-------------------
    return nullptr;
    // TEMP-------------------
}
