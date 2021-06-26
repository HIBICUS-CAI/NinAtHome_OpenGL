//---------------------------------------------------------------
// File: ATransformComponent.h
// Proj: NinAtHome
// Info: ACTORオブジェクトに動く位置に関してのコンポーネント
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "AComponent.h"

class ATransformComponent :
    public AComponent
{
public:
    ATransformComponent(std::string _name,
        class ActorObject* _owner, int _order, Float3 _initValue);
    virtual ~ATransformComponent();

    void SetPosition(Float3 _pos);

    Float3 GetPosition() const;

    void SetRotation(Float3 _angle);

    Float3 GetRotation() const;

    void SetScale(Float3 _factor);

    Float3 GetScale() const;

    Matrix4x4f GetWorldMatrix() const;

    void Translate(Float3 _pos);

    void TranslateXAsix(float _posx);

    void TranslateYAsix(float _posy);

    void TranslateZAsix(float _posz);

    void Rotate(Float3 _angle);

    void RotateXAsix(float _anglex);

    void RotateYAsix(float _angley);

    void RotateZAsix(float _anglez);

    void Scale(Float3 _factor);

    void Scale(float _factor);

    void ScaleXAsix(float _factorx);

    void ScaleYAsix(float _factory);

    void ScaleZAsix(float _factorz);

private:
    void UpdateWorldMatrix();

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    Float3 mPosition;

    Float3 mRotation;

    Float3 mScale;

    Matrix4x4f mWorldMatrix;
};
