//---------------------------------------------------------------
// File: USpriteComponent.h
// Proj: NinAtHome
// Info: UI¥ª¥Ö¥¸¥§¥¯¥È¤Ë¥¹¥×¥é¥¤¥È¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "UComponent.h"

class USpriteComponent :
    public UComponent
{
public:
    USpriteComponent(std::string _name, class UiObject* _owner,
        int _order, int _drawOrder);
    virtual ~USpriteComponent();

    void LoadTextureByPath(std::string _path);

    void DeleteTexture();

    unsigned int GetTexture() const;

    void SetTexWidth(float _width);

    void SetTexHeight(float _height);

    unsigned int GetTexWidth() const;

    unsigned int GetTexHeight() const;

    void SetOffsetColor(Float4 _color);

    Float4 GetOffsetColor() const;

    void SetVisible(bool _visible);

    bool GetVisible() const;

    int GetDrawOrder() const;

    void ResetDrawOrder(int _order);

    void DrawUSprite();

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
