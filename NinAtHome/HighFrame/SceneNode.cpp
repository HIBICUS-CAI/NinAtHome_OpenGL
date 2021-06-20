//---------------------------------------------------------------
// File: SceneNode.cpp
// Proj: NinAtHome
// Info: 単一のシーンを管理、代表するの節点
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "SceneNode.h"
#include "SceneManager.h"
#include "ActorObject.h"
#include "UiObject.h"
#include "ASpriteComponent.h"
#include "USpriteComponent.h"

SceneNode::SceneNode(std::string _name, SceneManager* smPtr) :
    mName(_name), mSceneManagerPtr(smPtr), mCamera(nullptr),
    mSceneLoopFuncPtr(nullptr),
    mActorObjectsMap({}), mActorObjectsArray({}),
    mUiObjectsMap({}), mUiObjectsArray({}),
    mActorSpritesArray({}), mUiSpritesArray({}),
    mNewActorObjectsArray({}), mNewUiObjectsArray({}),
    mRetiredActorObjectsArray({}), mRetiredUiObjectsArray({})
{
    mActorObjectsMap.clear();
    mActorObjectsArray.clear();
    mUiObjectsMap.clear();
    mUiObjectsArray.clear();
    mActorSpritesArray.clear();
    mUiSpritesArray.clear();
    mNewActorObjectsArray.clear();
    mNewUiObjectsArray.clear();
    mRetiredActorObjectsArray.clear();
    mRetiredUiObjectsArray.clear();
}

SceneNode::~SceneNode()
{

}

std::string SceneNode::GetSceneName() const
{
    return mName;
}

SceneManager* SceneNode::GetSceneManagerPtr() const
{
    return mSceneManagerPtr;
}

ActorObject* SceneNode::GetActorObject(std::string _name)
{
    if (mActorObjectsMap.find(_name) == mActorObjectsMap.end())
    {
        MY_NN_LOG(LOG_WARNING,
            "cannot find this Aobject : [ %s ]\n", _name.c_str());
        return nullptr;
    }

    return mActorObjectsMap[_name];
}

UiObject* SceneNode::GetUiObject(std::string _name)
{
    if (mUiObjectsMap.find(_name) == mUiObjectsMap.end())
    {
        MY_NN_LOG(LOG_WARNING,
            "cannot find this Uobject : [ %s ]\n", _name.c_str());
        return nullptr;
    }

    return mUiObjectsMap[_name];
}

void SceneNode::LoadSceneInitFile(std::string _path)
{

}

void SceneNode::UpdateScene(float _deltatime)
{
    InitAllNewObjects();

    for (auto aci = mActorObjectsArray.begin();
        aci != mActorObjectsArray.end();)
    {
        if ((*aci)->IsObjectActive() == STATUS::NEED_DESTORY)
        {
            mRetiredActorObjectsArray.push_back(*aci);
            for (auto spi = mActorSpritesArray.begin();
                spi != mActorSpritesArray.end(); spi++)
            {
                if ((*spi) == (*aci))
                {
                    mActorSpritesArray.erase(spi);
                    break;
                }
            }
            mActorObjectsMap.erase((*aci)->GetObjectName());
            aci = mActorObjectsArray.erase(aci);
        }
        else
        {
            if ((*aci)->IsObjectActive() == STATUS::ACTIVE)
            {
                (*aci)->Update(_deltatime);
                (*aci)->UpdateComponents(_deltatime);
            }
            aci++;
        }
    }
    for (auto uii = mUiObjectsArray.begin();
        uii != mUiObjectsArray.end();)
    {
        if ((*uii)->IsObjectActive() == STATUS::NEED_DESTORY)
        {
            mRetiredUiObjectsArray.push_back(*uii);
            for (auto spi = mUiSpritesArray.begin();
                spi != mUiSpritesArray.end(); spi++)
            {
                if ((*spi) == (*uii))
                {
                    mUiSpritesArray.erase(spi);
                    break;
                }
            }
            mUiObjectsMap.erase((*uii)->GetObjectName());
            uii = mUiObjectsArray.erase(uii);
        }
        else
        {
            if ((*uii)->IsObjectActive() == STATUS::ACTIVE)
            {
                (*uii)->Update(_deltatime);
                (*uii)->UpdateComponents(_deltatime);
            }
            uii++;
        }
    }

    DestoryAllRetiredObjects();
}

void SceneNode::DrawScene()
{
    for (auto actor : mActorSpritesArray)
    {
        if (actor->IsObjectActive() == STATUS::ACTIVE)
        {
            actor->Draw();
        }
    }
    for (auto ui : mUiSpritesArray)
    {
        if (ui->IsObjectActive() == STATUS::ACTIVE)
        {
            ui->Draw();
        }
    }
}

void SceneNode::ReleaseScene()
{
    while (!mNewActorObjectsArray.empty())
    {
        auto newActor = mNewActorObjectsArray.back();
        delete newActor;
        mNewActorObjectsArray.pop_back();
    }

    while (!mNewUiObjectsArray.empty())
    {
        auto newUi = mNewUiObjectsArray.back();
        delete newUi;
        mNewUiObjectsArray.pop_back();
    }

    while (!mActorObjectsArray.empty())
    {
        auto retireActor = mActorObjectsArray.back();
        retireActor->Destory();
        delete retireActor;
        mActorObjectsArray.pop_back();
    }
    mActorSpritesArray.clear();
    mActorObjectsMap.clear();

    while (!mUiObjectsArray.empty())
    {
        auto retireUi = mUiObjectsArray.back();
        retireUi->Destory();
        delete retireUi;
        mUiObjectsArray.pop_back();
    }
    mUiSpritesArray.clear();
    mUiObjectsMap.clear();

    delete mCamera;
}

void SceneNode::AddActorObject(ActorObject* _aObj)
{
    mNewActorObjectsArray.push_back(_aObj);
}

void SceneNode::AddUiObject(UiObject* _uObj)
{

}

void SceneNode::DeleteActorObject(std::string _name)
{
    if (mActorObjectsMap.find(_name) == mActorObjectsMap.end())
    {
        MY_NN_LOG(LOG_WARNING,
            "cannot find this Aobject : [ %s ]\n", _name.c_str());
        return;
    }

    for (auto aci = mActorObjectsArray.begin();
        aci != mActorObjectsArray.end(); aci++)
    {
        if ((*aci)->GetObjectName() == _name)
        {
            (*aci)->SetObjectActive(STATUS::NEED_DESTORY);
            (*aci)->ClearChildren();
            break;
        }
    }
}

void SceneNode::DeleteUiObject(std::string _name)
{

}

void SceneNode::SetSceneLoopFunc(SceneLoopFuncType _func)
{
    mSceneLoopFuncPtr = _func;
}

void SceneNode::ClearSceneLoopFunc()
{
    mSceneLoopFuncPtr = nullptr;
}

void SceneNode::InitCamera(Float2 _pos, Float2 _size)
{
    mCamera = new Camera(_pos, _size);
}

Camera* SceneNode::GetCamera() const
{
    return mCamera;
}

Float4x4 SceneNode::GetCameraMat() const
{
    // TEMP-------------------
    return nullptr;
    // TEMP-------------------
}

void SceneNode::InitAllNewObjects()
{
    while (!mNewActorObjectsArray.empty())
    {
        auto newActor = mNewActorObjectsArray.back();
        newActor->Init();
        newActor->SetObjectActive(STATUS::ACTIVE);
        mNewActorObjectsArray.pop_back();

        bool isInserted = false;
        for (auto actor = mActorObjectsArray.begin();
            actor != mActorObjectsArray.end(); actor++)
        {
            if ((*actor)->GetUpdateOrder() >=
                newActor->GetUpdateOrder())
            {
                mActorObjectsArray.insert(actor, newActor);
                isInserted = true;
                break;
            }
        }
        if (!isInserted)
        {
            mActorObjectsArray.push_back(newActor);
        }
        mActorObjectsMap.insert(std::make_pair(
            newActor->GetObjectName(), newActor));

        if (newActor->GetSpriteArray()->size())
        {
            isInserted = false;
            for (auto actor = mActorSpritesArray.begin();
                actor != mActorSpritesArray.end(); actor++)
            {
                if (((*actor)->GetSpriteArray())->front()->
                    GetDrawOrder() >=
                    newActor->GetSpriteArray()->front()->
                    GetDrawOrder())
                {
                    mActorSpritesArray.insert(actor, newActor);
                    isInserted = true;
                    break;
                }
            }
            if (!isInserted)
            {
                mActorSpritesArray.push_back(newActor);
            }
        }
    }

    while (!mNewUiObjectsArray.empty())
    {
        auto newUi = mNewUiObjectsArray.back();
        newUi->Init();
        newUi->SetObjectActive(STATUS::ACTIVE);
        mNewUiObjectsArray.pop_back();

        bool isInserted = false;
        for (auto ui = mUiObjectsArray.begin();
            ui != mUiObjectsArray.end(); ui++)
        {
            if ((*ui)->GetUpdateOrder() >=
                newUi->GetUpdateOrder())
            {
                mUiObjectsArray.insert(ui, newUi);
                isInserted = true;
                break;
            }
        }
        if (!isInserted)
        {
            mUiObjectsArray.push_back(newUi);
        }
        mUiObjectsMap.insert(std::make_pair(
            newUi->GetObjectName(), newUi));

        if (newUi->GetSpriteArray()->size())
        {
            isInserted = false;
            for (auto ui = mUiSpritesArray.begin();
                ui != mUiSpritesArray.end(); ui++)
            {
                if (((*ui)->GetSpriteArray())->front()->
                    GetDrawOrder() >=
                    newUi->GetSpriteArray()->front()->
                    GetDrawOrder())
                {
                    mUiSpritesArray.insert(ui, newUi);
                    isInserted = true;
                    break;
                }
            }
            if (!isInserted)
            {
                mUiSpritesArray.push_back(newUi);
            }
        }
    }
}

void SceneNode::DestoryAllRetiredObjects()
{
    while (!mRetiredActorObjectsArray.empty())
    {
        auto retireActor = mRetiredActorObjectsArray.back();
        retireActor->Destory();
        delete retireActor;
        mRetiredActorObjectsArray.pop_back();
    }

    while (!mRetiredUiObjectsArray.empty())
    {
        auto retireUi = mRetiredUiObjectsArray.back();
        retireUi->Destory();
        delete retireUi;
        mRetiredUiObjectsArray.pop_back();
    }
}

Camera::Camera(Float2 _pos, Float2 _size) :
    mCameraPosition(_pos), mCameraSize(_size),
    mViewMat(nullptr), mOPMat(nullptr),
    mViewMatDirtyFlg(true), mOPMatDirtyFlg(true)
{

}

Camera::~Camera()
{

}

void Camera::CheckMatUpdate()
{

}

void Camera::TranslateCameraPos(Float2 _deltaPos)
{

}

void Camera::ChangeCameraSize(Float2 _size)
{

}

void Camera::CalcViewMat()
{

}

void Camera::CalcOPMat()
{

}
