//---------------------------------------------------------------
// File: ObjectFactory.cpp
// Proj: NinAtHome
// Info: オブジェクトを生成するのファクトリー
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "ObjectFactory.h"
#include "PropertyManager.h"
#include "PropertyNode.h"
#include "SceneManager.h"
#include "SceneNode.h"
#include "Actor_all.h"
#include "Ui_all.h"

// TEMP---------------------------------------------
#include "..\TempTest.h"
#include "..\TitleStartBtn.h"
#include "..\ResultBtn.h"
#include "..\RunnerAndBg.h"
// TEMP---------------------------------------------

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
    node->InitCamera(
        MakeFloat2(0.f, 0.f), MakeFloat2(1920.f, 1080.f));

    if (config.HasMember("camera") && config["actor"].Size() == 4)
    {
        node->InitCamera(
            MakeFloat2(
                config["camera"][0].GetFloat(),
                config["camera"][1].GetFloat()),
            MakeFloat2(
                config["camera"][2].GetFloat(),
                config["camera"][3].GetFloat()));
    }

    if (config.HasMember("actor") &&
        !config["actor"].IsNull() && config["actor"].Size())
    {
        for (unsigned int i = 0; i < config["actor"].Size(); i++)
        {
            ActorObject* actor = CreateNewAObject(&config,
                "/actor/" + std::to_string(i), node);
            if (actor)
            {
                node->AddActorObject(actor);
            }
        }
    }
    if (config.HasMember("ui") &&
        !config["ui"].IsNull() && config["ui"].Size())
    {
        for (unsigned int i = 0; i < config["ui"].Size(); i++)
        {
            UiObject* ui = CreateNewUObject(&config,
                "/ui/" + std::to_string(i), node);
            if (ui)
            {
                node->AddUiObject(ui);
            }
        }
    }

    return node;
}

ActorObject* ObjectFactory::CreateNewAObject(JsonFile* _file,
    std::string _nodePath, SceneNode* _scene)
{
    ActorObject* aObj = CreateActorItself(
        _file, _nodePath, _scene);

    JsonNode compNode = GetJsonNode(
        _file, _nodePath + "/components");
    if (compNode && !compNode->IsNull() && compNode->Size())
    {
        for (unsigned int i = 0; i < compNode->Size(); i++)
        {
            std::string path =
                _nodePath + "/components/" + std::to_string(i);
            AddACompToActor(aObj, _file, path);
        }
    }

    compNode = GetJsonNode(_file, _nodePath + "/parent");
    if (compNode && compNode->IsString())
    {
        _scene->GetActorObject(compNode->GetString())->
            AddChild(aObj);

        return nullptr;
    }

    return aObj;
}

UiObject* ObjectFactory::CreateNewUObject(JsonFile* _file,
    std::string _nodePath, SceneNode* _scene)
{
    UiObject* uObj = CreateUiItself(
        _file, _nodePath, _scene);

    JsonNode compNode = GetJsonNode(
        _file, _nodePath + "/components");
    if (compNode && !compNode->IsNull() && compNode->Size())
    {
        for (unsigned int i = 0; i < compNode->Size(); i++)
        {
            std::string path =
                _nodePath + "/components/" + std::to_string(i);
            AddUCompToUi(uObj, _file, path);
        }
    }

    compNode = GetJsonNode(_file, _nodePath + "/parent");
    if (compNode && compNode->IsString())
    {
        _scene->GetUiObject(compNode->GetString())->
            AddChild(uObj);

        return nullptr;
    }

    return uObj;
}

ActorObject* ObjectFactory::CreateActorItself(JsonFile* _file,
    std::string _nodePath, SceneNode* _scene)
{
    ActorObject* aObj = nullptr;

    {
        JsonNode node = nullptr;
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

UiObject* ObjectFactory::CreateUiItself(JsonFile* _file,
    std::string _nodePath, SceneNode* _scene)
{
    UiObject* uObj = nullptr;

    {
        JsonNode node = nullptr;
        std::string name = "";
        int objOrder = 0;
        node = GetJsonNode(_file, _nodePath + "/ui-name");
        if (node && node->IsString())
        {
            name = node->GetString();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get ui name in [ %s ]\n",
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
                "cannot get ui update order in [ %s ]\n",
                _nodePath.c_str());
        }

        uObj = new UiObject(name, _scene, objOrder);
    }

    return uObj;
}

void ObjectFactory::AddACompToActor(ActorObject* _actor,
    JsonFile* _file, std::string _nodePath)
{
    JsonNode compNode = GetJsonNode(_file, _nodePath + "/type");
    if (!compNode || !compNode->IsString())
    {
        MY_NN_LOG(LOG_ERROR,
            "cannot get comp type in [ %s ]\n",
            _nodePath.c_str());
        return;
    }
    std::string compType = compNode->GetString();

    // TRANSFORM----------------------------
    if (compType == "transform")
    {
        std::string name =
            _actor->GetObjectName() + "-" + compType;
        int updateOrder = 0;
        Float3 initValue = MakeFloat3(0.f, 0.f, 0.f);

        compNode = GetJsonNode(
            _file, _nodePath + "/update-order");
        if (compNode && compNode->IsInt())
        {
            updateOrder = compNode->GetInt();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get update order in [ %s ]\n",
                _nodePath.c_str());
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/init-value");
        if (compNode && (compNode->Size() == 3))
        {
            float temp[3] = {};
            for (int i = 0; i < 3; i++)
            {
                compNode = GetJsonNode(_file,
                    _nodePath + "/init-value/" +
                    std::to_string(i));
                temp[i] = compNode->GetFloat();
            }
            initValue = MakeFloat3(temp[0], temp[1], temp[2]);
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get init value in [ %s ]\n",
                _nodePath.c_str());
        }

        ATransformComponent* atc = new ATransformComponent(name,
            _actor, updateOrder, initValue);
        _actor->AddAComponent(atc);

        compNode = GetJsonNode(
            _file, _nodePath + "/position/0");
        if (!(!compNode || compNode->IsNull()))
        {
            float temp[3] = {};
            temp[0] = GetJsonNode(
                _file, _nodePath + "/position/0")->GetFloat();
            temp[1] = GetJsonNode(
                _file, _nodePath + "/position/1")->GetFloat();
            temp[2] = GetJsonNode(
                _file, _nodePath + "/position/2")->GetFloat();

            Float3 pos = MakeFloat3(temp[0], temp[1], temp[2]);
            atc->SetPosition(pos);
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/rotation/0");
        if (!(!compNode || compNode->IsNull()))
        {
            float temp[3] = {};
            temp[0] = GetJsonNode(
                _file, _nodePath + "/rotation/0")->GetFloat();
            temp[1] = GetJsonNode(
                _file, _nodePath + "/rotation/1")->GetFloat();
            temp[2] = GetJsonNode(
                _file, _nodePath + "/rotation/2")->GetFloat();

            Float3 angle = MakeFloat3(temp[0], temp[1], temp[2]);
            atc->SetRotation(angle);
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/scale/0");
        if (!(!compNode || compNode->IsNull()))
        {
            float temp[3] = {};
            temp[0] = GetJsonNode(
                _file, _nodePath + "/scale/0")->GetFloat();
            temp[1] = GetJsonNode(
                _file, _nodePath + "/scale/1")->GetFloat();
            temp[2] = GetJsonNode(
                _file, _nodePath + "/scale/2")->GetFloat();

            Float3 scale = MakeFloat3(temp[0], temp[1], temp[2]);
            atc->SetScale(scale);
        }
    }

    // SPRITE----------------------------
    else if (compType == "sprite")
    {
        std::string name =
            _actor->GetObjectName() + "-" + compType;
        int updateOrder = 0;
        int drawOrder = 0;

        compNode = GetJsonNode(
            _file, _nodePath + "/update-order");
        if (compNode && compNode->IsInt())
        {
            updateOrder = compNode->GetInt();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get update order in [ %s ]\n",
                _nodePath.c_str());
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/draw-order");
        if (compNode && compNode->IsInt())
        {
            drawOrder = compNode->GetInt();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get update order in [ %s ]\n",
                _nodePath.c_str());
        }

        ASpriteComponent* asc = new ASpriteComponent(name, _actor,
            updateOrder, drawOrder);
        _actor->AddAComponent(asc);

        compNode = GetJsonNode(
            _file, _nodePath + "/texture-path");
        if (compNode && compNode->IsString())
        {
            asc->LoadTextureByPath(compNode->GetString());
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/texture-width");
        if (compNode && compNode->IsFloat())
        {
            asc->SetTexWidth(compNode->GetFloat());
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/texture-height");
        if (compNode && compNode->IsFloat())
        {
            asc->SetTexHeight(compNode->GetFloat());
        }
    }

    // COLLISION----------------------------
    else if (compType == "collision")
    {
        std::string name =
            _actor->GetObjectName() + "-" + compType;
        int updateOrder = 0;

        compNode = GetJsonNode(
            _file, _nodePath + "/update-order");
        if (compNode && compNode->IsInt())
        {
            updateOrder = compNode->GetInt();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get update order in [ %s ]\n",
                _nodePath.c_str());
        }

        ACollisionComponent* acc = new ACollisionComponent(name,
            _actor, updateOrder);
        _actor->AddAComponent(acc);

        COLLISION_TYPE collType = COLLISION_TYPE::NULLTYPE;
        Float2 collSize = MakeFloat2(0.f, 0.f);
        bool showFlg = false;
        compNode = GetJsonNode(
            _file, _nodePath + "/collision-type");
        if (compNode && compNode->IsString())
        {
            std::string ctype = compNode->GetString();
            if (ctype == "circle")
            {
                collType = COLLISION_TYPE::CIRCLE;
            }
            else if (ctype == "rectangle")
            {
                collType = COLLISION_TYPE::RECTANGLE;
            }
        }
        compNode = GetJsonNode(
            _file, _nodePath + "/collision-size/0");
        if (compNode && compNode->IsFloat())
        {
            collSize.x = compNode->GetFloat();
        }
        compNode = GetJsonNode(
            _file, _nodePath + "/collision-size/1");
        if (compNode && compNode->IsFloat())
        {
            collSize.y = compNode->GetFloat();
        }
        compNode = GetJsonNode(
            _file, _nodePath + "/show-flag");
        if (compNode && compNode->IsBool())
        {
            showFlg = compNode->GetBool();
        }
        acc->SetCollisionStatus(collType, collSize, showFlg);
    }

    // INPUT----------------------------
    else if (compType == "input")
    {
        std::string name =
            _actor->GetObjectName() + "-" + compType;
        int updateOrder = 0;

        compNode = GetJsonNode(
            _file, _nodePath + "/update-order");
        if (compNode && compNode->IsInt())
        {
            updateOrder = compNode->GetInt();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get update order in [ %s ]\n",
                _nodePath.c_str());
        }

        AInputComponent* aic = new AInputComponent(name, _actor,
            updateOrder);
        _actor->AddAComponent(aic);

        compNode = GetJsonNode(
            _file, _nodePath + "/func-name");
        if (compNode && compNode->IsString())
        {
            // TEMP----------------------------
            std::string funcName = compNode->GetString();
            if (funcName == "HiddenCommandInput")
            {
                aic->SetInputProcessFunc(HiddenCommandInput);
            }
            else if (funcName == "RunnerInput")
            {
                aic->SetInputProcessFunc(RunnerInput);
            }
            // TEMP----------------------------
        }
    }

    // TIMER----------------------------
    else if (compType == "timer")
    {
        std::string name =
            _actor->GetObjectName() + "-" + compType;
        int updateOrder = 0;

        compNode = GetJsonNode(
            _file, _nodePath + "/update-order");
        if (compNode && compNode->IsInt())
        {
            updateOrder = compNode->GetInt();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get update order in [ %s ]\n",
                _nodePath.c_str());
        }

        ATimerComponent* atic = new ATimerComponent(name, _actor,
            updateOrder);
        _actor->AddAComponent(atic);

        compNode = GetJsonNode(
            _file, _nodePath + "/timers");
        if (compNode && compNode->Size())
        {
            int len = compNode->Size();
            for (int i = 0; i < len; i++)
            {
                compNode = GetJsonNode(
                    _file, _nodePath + "/timers/" +
                    std::to_string(i));
                if (compNode && compNode->IsString())
                {
                    atic->AddTimer(compNode->GetString());
                }
                else
                {
                    MY_NN_LOG(LOG_ERROR,
                        "cannot get timer name in [ %s ]\n",
                        _nodePath.c_str());
                }
            }
        }
    }

    // ANIMATE ----------------------------
    else if (compType == "animate")
    {
        std::string name =
            _actor->GetObjectName() + "-" + compType;
        int updateOrder = 0;

        compNode = GetJsonNode(
            _file, _nodePath + "/update-order");
        if (compNode && compNode->IsInt())
        {
            updateOrder = compNode->GetInt();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get update order in [ %s ]\n",
                _nodePath.c_str());
        }

        AAnimateComponent* aac = new AAnimateComponent(name,
            _actor, updateOrder);
        _actor->AddAComponent(aac);

        compNode = GetJsonNode(
            _file, _nodePath + "/animates");
        if (compNode && compNode->Size())
        {
            int len = compNode->Size();
            for (int i = 0; i < len; i++)
            {
                std::string aname = "";
                std::string apath = "";
                Float2 stride = MakeFloat2(0.f, 0.f);
                unsigned int count = 0;
                bool repeat = false;
                float ftime = 0.f;

                compNode = GetJsonNode(
                    _file, _nodePath + "/animates/" +
                    std::to_string(i) + "/animate-name");
                if (compNode && compNode->IsString())
                {
                    aname = compNode->GetString();
                }
                else
                {
                    MY_NN_LOG(LOG_ERROR, "cannot get ani name\n");
                }

                compNode = GetJsonNode(
                    _file, _nodePath + "/animates/" +
                    std::to_string(i) + "/animate-path");
                if (compNode && compNode->IsString())
                {
                    apath = compNode->GetString();
                }
                else
                {
                    MY_NN_LOG(LOG_ERROR, "cannot get ani path\n");
                }

                compNode = GetJsonNode(
                    _file, _nodePath + "/animates/" +
                    std::to_string(i) + "/animate-stride/0");
                if (compNode && compNode->IsFloat())
                {
                    stride.x = compNode->GetFloat();
                }
                else
                {
                    MY_NN_LOG(LOG_ERROR,
                        "cannot get ani stride\n");
                }

                compNode = GetJsonNode(
                    _file, _nodePath + "/animates/" +
                    std::to_string(i) + "/animate-stride/1");
                if (compNode && compNode->IsFloat())
                {
                    stride.y = compNode->GetFloat();
                }
                else
                {
                    MY_NN_LOG(LOG_ERROR,
                        "cannot get ani stride\n");
                }

                compNode = GetJsonNode(
                    _file, _nodePath + "/animates/" +
                    std::to_string(i) + "/max-count");
                if (compNode && compNode->IsUint())
                {
                    count = compNode->GetUint();
                }
                else
                {
                    MY_NN_LOG(LOG_ERROR,
                        "cannot get ani max count\n");
                }

                compNode = GetJsonNode(
                    _file, _nodePath + "/animates/" +
                    std::to_string(i) + "/repeat-flag");
                if (compNode && compNode->IsBool())
                {
                    repeat = compNode->GetBool();
                }
                else
                {
                    MY_NN_LOG(LOG_ERROR,
                        "cannot get ani repeat flag\n");
                }

                compNode = GetJsonNode(
                    _file, _nodePath + "/animates/" +
                    std::to_string(i) + "/frame-time");
                if (compNode && compNode->IsFloat())
                {
                    ftime = compNode->GetFloat();
                }
                else
                {
                    MY_NN_LOG(LOG_ERROR,
                        "cannot get ani frame time\n");
                }

                aac->LoadAnimate(aname, apath, stride, count,
                    repeat, ftime);
            }
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/init-animate");
        if (compNode && compNode->IsString())
        {
            aac->ChangeAnimateTo(compNode->GetString());
        }
    }

    // INTERACTION----------------------------
    else if (compType == "interaction")
    {
        std::string name =
            _actor->GetObjectName() + "-" + compType;
        int updateOrder = 0;

        compNode = GetJsonNode(
            _file, _nodePath + "/update-order");
        if (compNode && compNode->IsInt())
        {
            updateOrder = compNode->GetInt();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get update order in [ %s ]\n",
                _nodePath.c_str());
        }

        AInteractionComponent* aitc = new AInteractionComponent(
            name, _actor, updateOrder);
        _actor->AddAComponent(aitc);

        compNode = GetJsonNode(
            _file, _nodePath + "/init-func-name");
        if (compNode && compNode->IsString())
        {
            // TEMP----------------------------
            std::string funcName = compNode->GetString();
            if (funcName == "RunnerInit")
            {
                aitc->SetInitFunc(RunnerInit);
            }
            // TEMP----------------------------
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/update-func-name");
        if (compNode && compNode->IsString())
        {
            // TEMP----------------------------
            std::string funcName = compNode->GetString();
            if (funcName == "RunnerUpdate")
            {
                aitc->SetUpdateFunc(RunnerUpdate);
            }
            // TEMP----------------------------
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/destory-func-name");
        if (compNode && compNode->IsString())
        {
            // TEMP----------------------------
            std::string funcName = compNode->GetString();
            if (funcName == "RunnerDestory")
            {
                aitc->SetDestoryFunc(RunnerDestory);
            }
            // TEMP----------------------------
        }
    }

    // ELSE----------------------------
    else
    {
        MY_NN_LOG(LOG_ERROR,
            "this comp type doesn't exist [ %s ]\n",
            compType.c_str());
        return;
    }
}

void ObjectFactory::AddUCompToUi(UiObject* _ui,
    JsonFile* _file, std::string _nodePath)
{
    JsonNode compNode = GetJsonNode(_file, _nodePath + "/type");
    if (!compNode || !compNode->IsString())
    {
        MY_NN_LOG(LOG_ERROR,
            "cannot get comp type in [ %s ]\n",
            _nodePath.c_str());
        return;
    }
    std::string compType = compNode->GetString();

    // TRANSFORM----------------------------
    if (compType == "transform")
    {
        std::string name =
            _ui->GetObjectName() + "-" + compType;
        int updateOrder = 0;
        Float3 initValue = MakeFloat3(0.f, 0.f, 0.f);

        compNode = GetJsonNode(
            _file, _nodePath + "/update-order");
        if (compNode && compNode->IsInt())
        {
            updateOrder = compNode->GetInt();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get update order in [ %s ]\n",
                _nodePath.c_str());
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/init-value");
        if (compNode && (compNode->Size() == 3))
        {
            float temp[3] = {};
            for (int i = 0; i < 3; i++)
            {
                compNode = GetJsonNode(_file,
                    _nodePath + "/init-value/" +
                    std::to_string(i));
                temp[i] = compNode->GetFloat();
            }
            initValue = MakeFloat3(temp[0], temp[1], temp[2]);
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get init value in [ %s ]\n",
                _nodePath.c_str());
        }

        UTransformComponent* utc = new UTransformComponent(name,
            _ui, updateOrder, initValue);
        _ui->AddUComponent(utc);

        compNode = GetJsonNode(
            _file, _nodePath + "/position/0");
        if (!(!compNode || compNode->IsNull()))
        {
            float temp[3] = {};
            temp[0] = GetJsonNode(
                _file, _nodePath + "/position/0")->GetFloat();
            temp[1] = GetJsonNode(
                _file, _nodePath + "/position/1")->GetFloat();
            temp[2] = GetJsonNode(
                _file, _nodePath + "/position/2")->GetFloat();

            Float3 pos = MakeFloat3(temp[0], temp[1], temp[2]);
            utc->SetPosition(pos);
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/rotation/0");
        if (!(!compNode || compNode->IsNull()))
        {
            float temp[3] = {};
            temp[0] = GetJsonNode(
                _file, _nodePath + "/rotation/0")->GetFloat();
            temp[1] = GetJsonNode(
                _file, _nodePath + "/rotation/1")->GetFloat();
            temp[2] = GetJsonNode(
                _file, _nodePath + "/rotation/2")->GetFloat();

            Float3 angle = MakeFloat3(temp[0], temp[1], temp[2]);
            utc->SetRotation(angle);
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/scale/0");
        if (!(!compNode || compNode->IsNull()))
        {
            float temp[3] = {};
            temp[0] = GetJsonNode(
                _file, _nodePath + "/scale/0")->GetFloat();
            temp[1] = GetJsonNode(
                _file, _nodePath + "/scale/1")->GetFloat();
            temp[2] = GetJsonNode(
                _file, _nodePath + "/scale/2")->GetFloat();

            Float3 scale = MakeFloat3(temp[0], temp[1], temp[2]);
            utc->SetScale(scale);
        }
    }

    // SPRITE----------------------------
    else if (compType == "sprite")
    {
        std::string name =
            _ui->GetObjectName() + "-" + compType;
        int updateOrder = 0;
        int drawOrder = 0;

        compNode = GetJsonNode(
            _file, _nodePath + "/update-order");
        if (compNode && compNode->IsInt())
        {
            updateOrder = compNode->GetInt();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get update order in [ %s ]\n",
                _nodePath.c_str());
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/draw-order");
        if (compNode && compNode->IsInt())
        {
            drawOrder = compNode->GetInt();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get update order in [ %s ]\n",
                _nodePath.c_str());
        }

        USpriteComponent* usc = new USpriteComponent(name, _ui,
            updateOrder, drawOrder);
        _ui->AddUComponent(usc);

        compNode = GetJsonNode(
            _file, _nodePath + "/texture-path");
        if (compNode && compNode->IsString())
        {
            usc->LoadTextureByPath(compNode->GetString());
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/texture-width");
        if (compNode && compNode->IsFloat())
        {
            usc->SetTexWidth(compNode->GetFloat());
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/texture-height");
        if (compNode && compNode->IsFloat())
        {
            usc->SetTexHeight(compNode->GetFloat());
        }
    }

    // INPUT----------------------------
    else if (compType == "input")
    {
        std::string name =
            _ui->GetObjectName() + "-" + compType;
        int updateOrder = 0;

        compNode = GetJsonNode(
            _file, _nodePath + "/update-order");
        if (compNode && compNode->IsInt())
        {
            updateOrder = compNode->GetInt();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get update order in [ %s ]\n",
                _nodePath.c_str());
        }

        UInputComponent* uic = new UInputComponent(name, _ui,
            updateOrder);
        _ui->AddUComponent(uic);

        compNode = GetJsonNode(
            _file, _nodePath + "/func-name");
        if (compNode && compNode->IsString())
        {
            // TEMP----------------------------
            std::string funcName = compNode->GetString();
            if (funcName == "TempUiInput")
            {
                uic->SetInputProcessFunc(TempUiInput);
            }
            else if (funcName == "TempUiInput")
            {
                uic->SetInputProcessFunc(TempUiInput);
            }
            else if (funcName == "StartBtnInput")
            {
                uic->SetInputProcessFunc(StartBtnInput);
            }
            else if (funcName == "RetryBtnInput")
            {
                uic->SetInputProcessFunc(RetryBtnInput);
            }
            else if (funcName == "TitleBtnInput")
            {
                uic->SetInputProcessFunc(TitleBtnInput);
            }
            // TEMP----------------------------
        }
    }

    // BTNMAP----------------------------
    else if (compType == "btnmap")
    {
        std::string name =
            _ui->GetObjectName() + "-" + compType;
        int updateOrder = 0;

        compNode = GetJsonNode(
            _file, _nodePath + "/update-order");
        if (compNode && compNode->IsInt())
        {
            updateOrder = compNode->GetInt();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get update order in [ %s ]\n",
                _nodePath.c_str());
        }

        UBtnMapComponent* ubmc = new UBtnMapComponent(name, _ui,
            updateOrder);
        _ui->AddUComponent(ubmc);

        compNode = GetJsonNode(
            _file, _nodePath + "/default-select");
        if (compNode && compNode->IsBool())
        {
            ubmc->SetIsSelected(compNode->GetBool());
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/left");
        if (compNode && compNode->IsString())
        {
            ubmc->SetLeftName(compNode->GetString());
        }
        compNode = GetJsonNode(
            _file, _nodePath + "/right");
        if (compNode && compNode->IsString())
        {
            ubmc->SetRightName(compNode->GetString());
        }
        compNode = GetJsonNode(
            _file, _nodePath + "/up");
        if (compNode && compNode->IsString())
        {
            ubmc->SetUpName(compNode->GetString());
        }
        compNode = GetJsonNode(
            _file, _nodePath + "/down");
        if (compNode && compNode->IsString())
        {
            ubmc->SetDownName(compNode->GetString());
        }
    }

    // INTERACTION----------------------------
    else if (compType == "interaction")
    {
        std::string name =
            _ui->GetObjectName() + "-" + compType;
        int updateOrder = 0;

        compNode = GetJsonNode(
            _file, _nodePath + "/update-order");
        if (compNode && compNode->IsInt())
        {
            updateOrder = compNode->GetInt();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get update order in [ %s ]\n",
                _nodePath.c_str());
        }

        UInteractionComponent* uitc = new UInteractionComponent(
            name, _ui, updateOrder);
        _ui->AddUComponent(uitc);

        compNode = GetJsonNode(
            _file, _nodePath + "/init-func-name");
        if (compNode && compNode->IsString())
        {
            // TEMP--------------------
            uitc->SetInitFunc(TestUiInit);
            // TEMP--------------------
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/update-func-name");
        if (compNode && compNode->IsString())
        {
            // TEMP--------------------
            uitc->SetUpdateFunc(TestUiUpdate);
            // TEMP--------------------
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/destory-func-name");
        if (compNode && compNode->IsString())
        {
            // TEMP--------------------
            uitc->SetDestoryFunc(TestUiDestory);
            // TEMP--------------------
        }
    }

    // TEXT----------------------------
    else if (compType == "text")
    {
        std::string name =
            _ui->GetObjectName() + "-" + compType;
        int updateOrder = 0;

        compNode = GetJsonNode(
            _file, _nodePath + "/update-order");
        if (compNode && compNode->IsInt())
        {
            updateOrder = compNode->GetInt();
        }
        else
        {
            MY_NN_LOG(LOG_ERROR,
                "cannot get update order in [ %s ]\n",
                _nodePath.c_str());
        }

        UTextComponent* utxc = new UTextComponent(
            name, _ui, updateOrder);
        _ui->AddUComponent(utxc);

        compNode = GetJsonNode(
            _file, _nodePath + "/moji-path");
        if (compNode && compNode->IsString())
        {
            utxc->LoadFontTexture(compNode->GetString());
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/init-text");
        if (compNode && compNode->IsString())
        {
            utxc->ChangeTextString(compNode->GetString());
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/init-size");
        if (compNode && (compNode->Size() == 2))
        {
            Float2 fontSize = MakeFloat2(0.f, 0.f);
            compNode = GetJsonNode(
                _file, _nodePath + "/init-size/0");
            if (compNode && compNode->IsFloat())
            {
                fontSize.x = compNode->GetFloat();
            }
            compNode = GetJsonNode(
                _file, _nodePath + "/init-size/1");
            if (compNode && compNode->IsFloat())
            {
                fontSize.y = compNode->GetFloat();
            }

            utxc->SetFontSize(fontSize);
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/init-position");
        if (compNode && (compNode->Size() == 3))
        {
            Float3 pos = MakeFloat3(0.f, 0.f, 0.f);
            compNode = GetJsonNode(
                _file, _nodePath + "/init-position/0");
            if (compNode && compNode->IsFloat())
            {
                pos.x = compNode->GetFloat();
            }
            compNode = GetJsonNode(
                _file, _nodePath + "/init-position/1");
            if (compNode && compNode->IsFloat())
            {
                pos.y = compNode->GetFloat();
            }
            compNode = GetJsonNode(
                _file, _nodePath + "/init-position/2");
            if (compNode && compNode->IsFloat())
            {
                pos.z = compNode->GetFloat();
            }

            utxc->SetTextPosition(pos);
        }

        compNode = GetJsonNode(
            _file, _nodePath + "/init-color");
        if (compNode && (compNode->Size() == 4))
        {
            Float4 color = MakeFloat4(0.f, 0.f, 0.f, 0.f);
            compNode = GetJsonNode(
                _file, _nodePath + "/init-color/0");
            if (compNode && compNode->IsFloat())
            {
                color.x = compNode->GetFloat();
            }
            compNode = GetJsonNode(
                _file, _nodePath + "/init-color/1");
            if (compNode && compNode->IsFloat())
            {
                color.y = compNode->GetFloat();
            }
            compNode = GetJsonNode(
                _file, _nodePath + "/init-color/2");
            if (compNode && compNode->IsFloat())
            {
                color.z = compNode->GetFloat();
            }
            compNode = GetJsonNode(
                _file, _nodePath + "/init-color/3");
            if (compNode && compNode->IsFloat())
            {
                color.w = compNode->GetFloat();
            }

            utxc->SetTextColor(color);
        }
    }

    // ELSE----------------------------
    else
    {
        MY_NN_LOG(LOG_ERROR,
            "this comp type doesn't exist [ %s ]\n",
            compType.c_str());
        return;
    }
}
