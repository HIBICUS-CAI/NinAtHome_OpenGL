//---------------------------------------------------------------
// File: UInputComponent.cpp
// Proj: NinAtHome
// Info: UI•™•÷•∏•ß•Ø•»§À»Î¡¶§ÀÈv§∑§∆§Œ•≥•Û•›©`•Õ•Û•»
// Date: 2021.06.10
// Mail: cai_genkan@outlook.com
// Comt: NULL
//---------------------------------------------------------------

#include "UInputComponent.h"
#include "UiObject.h"

UInputComponent::UInputComponent(std::string _name,
    UiObject* _owner, int _order) :
    UComponent(_name, _owner, _order),
    mEventBtns({}), mEventSensors({})
{
    mEventBtns.clear();
    mEventSensors.clear();
}

UInputComponent::~UInputComponent()
{

}

void UInputComponent::CompInit()
{

}

void UInputComponent::CompUpdate(float _deltatime)
{

}

void UInputComponent::CompDestory()
{

}

void UInputComponent::AddEventBtn(int _btnCode)
{

}

void UInputComponent::DeleteEventBtn(int _btnCode)
{

}

bool UInputComponent::HasBtnExisted(int _btnCode)
{
    // TEMP--------------------
    return false;
    // TEMP--------------------
}

void UInputComponent::AddEventSensor(int _senCode)
{

}

void UInputComponent::DeleteEventSensor(int _senCode)
{

}

bool UInputComponent::HasSensorExisted(int _senCode)
{
    // TEMP--------------------
    return false;
    // TEMP--------------------
}
