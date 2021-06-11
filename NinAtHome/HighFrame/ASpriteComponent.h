//---------------------------------------------------------------
// File: ASpriteComponent.h
// Proj: NinAtHome
// Info: ACTOR���֥������Ȥ˥��ץ饤�Ȥ��v���ƤΥ���ݩ`�ͥ��
// Date: 2021.06.11
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "AComponent.h"

class ASpriteComponent :
    public AComponent
{
public:
    ASpriteComponent(std::string _name, class ActorObject* _owner,
        int _order, int _drawOrder);
    virtual ~ASpriteComponent();

    void LoadTexture(std::string _path);

    void DeleteTexture();

    unsigned int GetTexture() const;

    unsigned int GetTexWidth() const;

    unsigned int GetTexHeight() const;

    void SetOffsetColor(Float4 _color);

    Float4 GetOffsetColor() const;

    void SetVisible(bool _visible);

    bool GetVisible() const;

    int GetDrawOrder() const;

    void ResetDrawOrder(int _order);

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    unsigned int mTexture;

    Float4 mOffsetColor;

    unsigned int mTexWidth;

    unsigned int mTexHeight;

    bool mVisible;

    int mDrawOrder;
};
