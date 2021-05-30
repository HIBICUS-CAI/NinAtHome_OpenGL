#pragma once

#include "main.h"
#include <Xinput.h>

namespace NpadButton
{
    namespace Up
    {
        const int Index = XINPUT_GAMEPAD_DPAD_UP;
    };
    namespace Down
    {
        const int Index = XINPUT_GAMEPAD_DPAD_DOWN;
    };
    namespace Left
    {
        const int Index = XINPUT_GAMEPAD_DPAD_LEFT;
    };
    namespace Right
    {
        const int Index = XINPUT_GAMEPAD_DPAD_RIGHT;
    };
    namespace A
    {
        const int Index = XINPUT_GAMEPAD_B;
    };
    namespace B
    {
        const int Index = XINPUT_GAMEPAD_A;
    };
    namespace X
    {
        const int Index = XINPUT_GAMEPAD_Y;
    };
    namespace Y
    {
        const int Index = XINPUT_GAMEPAD_X;
    };
};

void InitController();

void UninitController();

void UpdateController();

bool GetControllerPress(int button);

bool GetControllerTrigger(int button);

Float2 GetControllerLeftStick();

Float2 GetControllerRightStick();

void SetControllerLeftVibration(int frame);

void SetControllerRightVibration(int frame);

//Float3 GetControllerLeftAcceleration();
//
//Float3 GetControllerRightAcceleration();

Float3 GetControllerLeftAngle();

Float3 GetControllerRightAngle();

bool GetControllerTouchScreen();

Float2 GetControllerTouchScreenPosition();
