#pragma once

#include "main.h"
#include <Xinput.h>

#define SZL (-1)
#define SZR (-2)
#define LL (-3)
#define LU (-4)
#define LR (-5)
#define LD (-6)
#define RL (-7)
#define RU (-8)
#define RR (-9)
#define RD (-10)

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
    namespace StickL
    {
        const int Index = XINPUT_GAMEPAD_LEFT_THUMB;
    };
    namespace StickR
    {
        const int Index = XINPUT_GAMEPAD_RIGHT_THUMB;
    };
    namespace L
    {
        const int Index = XINPUT_GAMEPAD_LEFT_SHOULDER;
    };
    namespace R
    {
        const int Index = XINPUT_GAMEPAD_RIGHT_SHOULDER;
    };
    namespace ZL
    {
        const int Index = SZL;
    };
    namespace ZR
    {
        const int Index = SZR;
    };
    namespace Plus
    {
        const int Index = XINPUT_GAMEPAD_START;
    };
    namespace Minus
    {
        const int Index = XINPUT_GAMEPAD_BACK;
    };
    namespace StickLLeft
    {
        const int Index = LL;
    };
    namespace StickLUp
    {
        const int Index = LU;
    };
    namespace StickLRight
    {
        const int Index = LR;
    };
    namespace StickLDown
    {
        const int Index = LD;
    };
    namespace StickRLeft
    {
        const int Index = RL;
    };
    namespace StickRUp
    {
        const int Index = RU;
    };
    namespace StickRRight
    {
        const int Index = RR;
    };
    namespace StickRDown
    {
        const int Index = RD;
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

Float3 GetControllerLeftAcceleration();

Float3 GetControllerRightAcceleration();

Float3 GetControllerLeftAngle();

Float3 GetControllerRightAngle();

bool GetControllerTouchScreen();

Float2 GetControllerTouchScreenPosition();
