//---------------------------------------------------------------
// File: USpriteComponent.h
// Proj: NinAtHome
// Info: UIオブジェクトにスプライトに関してのコンポーネント
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

    void SaveTexturePath(std::string _path);

    void DeleteTexture();

    ID3D11ShaderResourceView* GetTexture() const;

    void SetTexWidth(float _width);

    void SetTexHeight(float _height);

    float GetTexWidth() const;

    float GetTexHeight() const;

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
    void LoadTextureByPath(std::string _path);

private:
    ID3D11ShaderResourceView* mTexture;

    ID3D11Buffer* mSpriteVertexBuffer;

    ID3D11Buffer* mSpriteIndexBuffer;

    std::string mTexPath;

    Float4 mOffsetColor;

    float mTexWidth;

    float mTexHeight;

    bool mVisible;

    int mDrawOrder;
};
