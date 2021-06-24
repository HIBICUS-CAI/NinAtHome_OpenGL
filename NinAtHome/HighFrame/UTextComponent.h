//---------------------------------------------------------------
// File: UTextComponent.h
// Proj: NinAtHome
// Info: UI¥ª¥Ö¥¸¥§¥¯¥È¤ËÎÄ×Ö±íÊ¾¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "UComponent.h"

class UTextComponent :
    public UComponent
{
public:
    UTextComponent(std::string _name, class UiObject* _owner,
        int _order);
    virtual ~UTextComponent();

    void SetTextPosition(Float3 _pos);

    void SetFontSize(Float2 _size);

    Float2 GetFontSize() const;

    void LoadFontTexture(std::string _path);

    void ChangeTextString(std::string _text);

    void SetTextColor(Float4 _color);

    void DrawUText();

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    unsigned int mFontTexture;

    std::string mTextString;

    Float3 mTextPosition;

    Float2 mFontSize;

    Float4 mTextColor;
};
