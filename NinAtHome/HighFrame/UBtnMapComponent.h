//---------------------------------------------------------------
// File: UBtnMapComponent.h
// Proj: NinAtHome
// Info: UIオブジェクトにボタン地図に関してのコンポーネント
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

    void SetLeftName(std::string _name);
    
    void SetRightName(std::string _name);

    void SetUpName(std::string _name);
    
    void SetDownName(std::string _name);

private:
    void SetCanSelectFlg(bool _value);

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    std::array<class UiObject*, 4> mSurroundBtns;

    std::array<std::string, 4> mSurroundName;

    bool mIsSelected;

    bool mCanSelectOther;
};

