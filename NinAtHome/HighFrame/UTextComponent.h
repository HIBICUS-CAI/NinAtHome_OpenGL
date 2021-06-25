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
#include <unordered_map>

#define MOJI_TEX_H_NUM  (19)
#define MOJI_TEX_V_NUM  (10)
#define MOJI_U          (1.f / (float)MOJI_TEX_H_NUM)
#define MOJI_V          (1.f / (float)MOJI_TEX_V_NUM)

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

    const char* mTextPtr;

    std::unordered_map<std::string, Float3> mKanaUV;
};
