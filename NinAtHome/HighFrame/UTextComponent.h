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
#include <vector>

// TEMP-----------------
using Font = RECT;
// TEMP-----------------

class UTextComponent :
    public UComponent
{
public:
    UTextComponent(std::string _name, class UiObject* _owner,
        int _order);
    virtual ~UTextComponent();

    void SetTextPosition(Float3 _pos);

    void SetFontSize(unsigned int _size);

    unsigned int GetFontSize() const;

    void LoadFont(std::string _path);

    void ChangeSingleText(std::string _text);

    void ReloadMutiText(std::string _path);

    void DrawUText();

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    std::string mSingleText;

    std::vector<std::string> mMutiText;

    Float3 mTextPosition;

    unsigned int mFontSize;

    Font mFont;

    bool mUsingMutiTextFlg;
};
