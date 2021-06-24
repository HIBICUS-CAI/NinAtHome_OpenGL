//---------------------------------------------------------------
// File: UBtnMapComponent.h
// Proj: NinAtHome
// Info: UI¥ª¥Ö¥¸¥§¥¯¥È¤Ë¥Ü¥¿¥óµØ‡í¤Ëév¤·¤Æ¤Î¥³¥ó¥Ý©`¥Í¥ó¥È
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "UComponent.h"
#include <array>

class UBtnMapComponent :
    public UComponent
{
public:
    UBtnMapComponent(std::string _name, class UiObject* _owner,
        int _order);
    virtual ~UBtnMapComponent();

    bool IsBeingSelected();

    void SelectUpBtn();

    void SelectDownBtn();

    void SelectLeftBtn();

    void SelectRightBtn();

    class UiObject* GetUpBtn() const;

    class UiObject* GetDownBtn() const;

    class UiObject* GetLeftBtn() const;

    class UiObject* GetRightBtn() const;

private:
    void UpdateButtonMap();

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    std::array<class UiObject*, 4> mSurroundBtns;

    bool mIsSelected;
};

