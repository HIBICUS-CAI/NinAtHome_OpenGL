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
    SceneNode(std::string _name, std::string _path,
        class SceneManager* smPtr);
    ~SceneNode();

    std::string GetSceneName() const;

    class SceneManager* GetSceneManagerPtr() const;

    void ResetSceneNode();

    class ActorObject* GetActorObject(std::string _name);

    class UiObject* GetUiObject(std::string _name);

    std::vector<class ActorObject*>* GetActorArray();

    std::vector<class UiObject*>* GetUiArray();

    void LoadSceneInitFile(std::string _path);

    void UpdateScene(float _deltatime);

    void DrawScene();

    void ReleaseScene();

    void AddActorObject(class ActorObject* _aObj);

    void AddUiObject(class UiObject* _uObj);

    void DeleteActorObject(std::string _name);

    void DeleteUiObject(std::string _name);

    ID3D11ShaderResourceView* CheckIfTexExist(std::string _path);

    void InsertNewTex(std::string _path, 
        ID3D11ShaderResourceView* _tex);

    void SetSceneLoopFunc(SceneLoopFuncType _func);

    void ClearSceneLoopFunc();

    void InitCamera(Float2 _pos, Float2 _size);

    class Camera* GetCamera() const;

private:
    void InitAllNewObjects();

    void DestoryAllRetiredObjects();

    void ClearTexPool();

private:
    const std::string mName;

    const std::string mConfigPath;

    class SceneManager* mSceneManagerPtr;

    std::unordered_map<std::string, class ActorObject*>
        mActorObjectsMap;

    std::vector<class ActorObject*> mActorObjectsArray;

    std::unordered_map<std::string, class UiObject*>
        mUiObjectsMap;

    std::vector<class UiObject*> mUiObjectsArray;

    std::vector<class ActorObject*> mActorSpritesArray;

    std::vector<class UiObject*> mUiSpritesArray;

    std::vector<class ActorObject*> mNewActorObjectsArray;

    std::vector<class UiObject*> mNewUiObjectsArray;

    std::vector<class ActorObject*> mRetiredActorObjectsArray;

    std::vector<class UiObject*> mRetiredUiObjectsArray;

    std::unordered_map<std::string, ID3D11ShaderResourceView*> 
        mTexPool;

    SceneLoopFuncType mSceneLoopFuncPtr;

    class Camera* mCamera;
};

class Camera
{
public:
    Camera(Float2 _pos, Float2 _size);
    ~Camera();

    void ResetCameraPos(Float2 _pos);

    void TranslateCameraPos(Float2 _deltaPos);

    void ChangeCameraSize(Float2 _size);

    Float3 GetRelativePosWithCam(Float3 _absolutePos);

private:
    Float2 mCameraPosition;

    Float2 mCameraSize;
};
