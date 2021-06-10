//---------------------------------------------------------------
// File: UInputComponent.h
// Proj: NinAtHome
// Info: UI•™•÷•∏•ß•Ø•»§À»Î¡¶§ÀÈv§∑§∆§Œ•≥•Û•›©`•Õ•Û•»
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#pragma once

#include "UComponent.h"
#include <vector>

class UInputComponent :
    public UComponent
{
public:
    UInputComponent(std::string _name, class UiObject* _owner,
        int _order);
    virtual ~UInputComponent();

    void AddEventBtn(int _btnCode);

    void DeleteEventBtn(int _btnCode);

    bool HasBtnExisted(int _btnCode);

    void AddEventSensor(int _senCode);

    void DeleteEventSensor(int _senCode);

    bool HasSensorExisted(int _senCode);

public:
    virtual void CompInit();

    virtual void CompUpdate(float _deltatime);

    virtual void CompDestory();

private:
    std::vector<int> mEventBtns;

    std::vector<int> mEventSensors;
};
