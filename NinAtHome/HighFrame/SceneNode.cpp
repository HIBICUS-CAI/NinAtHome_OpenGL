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

SceneNode::SceneNode(std::string _name, SceneManager* smPtr) :
    mName(_name), mSceneManagerPtr(smPtr), mCamera(nullptr),
    mSceneLoopFuncPtr(nullptr),
    mActorObjectsMap({}), mActorObjectsArray({}),
    mUiObjectsMap({}), mUiObjectsArray({}),
    mNewActorObjectsArray({}), mNewUiObjectsArray({}),
    mRetiredActorObjectsArray({}), mRetiredUiObjectsArray({})
{
    mActorObjectsMap.clear();
    mActorObjectsArray.clear();
    mUiObjectsMap.clear();
    mUiObjectsArray.clear();
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
    return mActorObjectsMap[_name];
}

UiObject* SceneNode::GetUiObject(std::string _name)
{
    return mUiObjectsMap[_name];
}

void SceneNode::LoadSceneInitFile(std::string _path)
{

}

void SceneNode::UpdateScene()
{

}

void SceneNode::ReleaseScene()
{

}

void SceneNode::AddActorObject(ActorObject* _aObj)
{

}

void SceneNode::AddUiObject(UiObject* _uObj)
{

}

void SceneNode::DeleteActorObject(std::string _name)
{

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

}

void SceneNode::DestoryAllRetiredObjects()
{

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
