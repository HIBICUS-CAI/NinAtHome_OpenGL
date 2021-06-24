//---------------------------------------------------------------
// File: UBtnMapComponent.h
// Proj: NinAtHome
// Info: UI���֥������Ȥ˥ܥ���؇���v���ƤΥ���ݩ`�ͥ��
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "UComponent.h"
#include <array>

#define LEFT_BTN    (0)
#define UP_BTN      (1)
#define RIGHT_BTN   (2)
#define DOWN_BTN    (3)

class UBtnMapComponent :
    public UComponent
{
public:
    UBtnMapComponent(std::string _name, class UiObject* _owner,
        int _order);
    virtual ~UBtnMapComponent();

    void SetIsSelected(bool _value);

    bool IsBeingSelected() const;

    void SelectUpBtn();

    void SelectDownBtn();

    void SelectLeftBtn();

    void SelectRightBtn();

    class UiObject* GetUpBtn() const;

    class UiObject* GetDownBtn() const;

    class UiObject* GetLeftBtn() const;

    class UiObject* GetRightBtn() const;

private:
    void UpdateButtonMapWith(class UiObject* _toAddUi);

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    std::array<class UiObject*, 4> mSurroundBtns;

    bool mIsSelected;
};

