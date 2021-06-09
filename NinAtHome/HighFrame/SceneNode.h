//---------------------------------------------------------------
// File: SceneNode.h
// Proj: NinAtHome
// Info: 単一のシーンを管理、代表するの節点
// Date: 2021.06.09
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "HFCommon.h"
#include <string>
#include <vector>
#include <unordered_map>

// TEMP----------------
using SceneLoopFuncType = void (*)();
// TEMP----------------

class SceneNode
{
public:
    SceneNode(std::string _name, class SceneManager* smPtr);
    ~SceneNode();

    std::string GetSceneName() const;

    class SceneManager* GetSceneManagerPtr() const;

    class ActorObject* GetActorObject(std::string _name);

    class UiObject* GetUiObject(std::string _name);

    void LoadSceneInitFile(std::string _path);

    void UpdateScene();

    void DrawScene();

    void ReleaseScene();

    void AddActorObject(class ActorObject* _aObj);

    void AddUiObject(class UiObject* _uObj);

    void DeleteActorObject(std::string _name);

    void DeleteUiObject(std::string _name);

    void SetSceneLoopFunc(SceneLoopFuncType _func);

    void ClearSceneLoopFunc();

    void InitCamera(Float2 _pos, Float2 _size);

    class Camera* GetCamera() const;

    Float4x4 GetCameraMat() const;

private:
    void InitAllNewObjects();

    void DestoryAllRetiredObjects();

private:
    const std::string mName;

    class SceneManager* mSceneManagerPtr;

    std::unordered_map<std::string, class ActorObject*>
        mActorObjectsMap;

    std::vector<class ActorObject*> mActorObjectsArray;

    std::unordered_map<std::string, class UiObject*>
        mUiObjectsMap;

    std::vector<class UiObject*> mUiObjectsArray;

    std::vector<class ActorObject*> mNewActorObjectsArray;

    std::vector<class UiObject*> mNewUiObjectsArray;

    std::vector<class ActorObject*> mRetiredActorObjectsArray;

    std::vector<class UiObject*> mRetiredUiObjectsArray;

    SceneLoopFuncType mSceneLoopFuncPtr;

    class Camera* mCamera;
};

class Camera
{
public:
    Camera(Float2 _pos, Float2 _size);
    ~Camera();

    void CheckMatUpdate();

    void TranslateCameraPos(Float2 _deltaPos);

    void ChangeCameraSize(Float2 _size);

private:
    void CalcViewMat();

    void CalcOPMat();

private:
    Float2 mCameraPosition;

    Float2 mCameraSize;

    Float4x4 mViewMat;

    Float4x4 mOPMat;

    bool mViewMatDirtyFlg;

    bool mOPMatDirtyFlg;
};
