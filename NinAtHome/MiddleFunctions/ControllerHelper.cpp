#include "ControllerHelper.h"
#include <iostream>

//int g_VibrationLeftFrame = 0;
//int g_VibrationRightFrame = 0;

void InitController()
{
    if (!InputInterface::StartUp())
    {
        MY_NN_LOG(LOG_ERROR,
            "failed to init input device system\n");
    }
}

void UninitController()
{
    InputInterface::CleanAndStop();
}

//Float2 GetOldControllerLeftStick();
//
//Float2 GetOldControllerRightStick();

void UpdateController()
{
    InputInterface::PollDevices();

    /*if (g_VibrationLeftFrame > 0)
    {
        g_VibrationLeftFrame--;

        if (g_VibrationLeftFrame == 0)
        {
            gp_VibraHandle->wLeftMotorSpeed = 0;
            XInputSetState(g_XGamePadIndex, gp_VibraHandle);
        }
    }
    if (g_VibrationRightFrame > 0)
    {
        g_VibrationRightFrame--;

        if (g_VibrationRightFrame == 0)
        {
            gp_VibraHandle->wRightMotorSpeed = 0;
            XInputSetState(g_XGamePadIndex, gp_VibraHandle);
        }
    }*/
}

bool GetControllerPress(UINT button)
{
    return InputInterface::IsKeyDownInSingle(button);
}

bool GetControllerTrigger(UINT button)
{
    return InputInterface::IsKeyPushedInSingle(button);
}

STICK_OFFSET GetControllerLeftStick()
{
    return InputInterface::LeftStickOffset();
}

STICK_OFFSET GetControllerRightStick()
{
    return InputInterface::RightStickOffset();
}

void SetControllerLeftVibration(int frame)
{
    /*gp_VibraHandle->wLeftMotorSpeed = 65535 / 2;
    XInputSetState(g_XGamePadIndex, gp_VibraHandle);
    g_VibrationLeftFrame = frame;*/
}

void SetControllerRightVibration(int frame)
{
    /*gp_VibraHandle->wRightMotorSpeed = 65535 / 2;
    XInputSetState(g_XGamePadIndex, gp_VibraHandle);
    g_VibrationRightFrame = frame;*/
}

//Float3 GetControllerLeftAcceleration()
//{
//    int x, y, z;
//    x = GetDeltaCursorX(LEFT_ANGLE);
//    y = GetDeltaCursorY(LEFT_ANGLE);
//    z = GetDeltaScroll(LEFT_ANGLE);
//    x = x / 50;
//    y = -y / 50;
//
//    return Float3{ (float)x,(float)y,(float)z };
//}
//
//Float3 GetControllerRightAcceleration()
//{
//    int x, y, z;
//    x = GetDeltaCursorX(RIGHT_ANGLE);
//    y = GetDeltaCursorY(RIGHT_ANGLE);
//    z = GetDeltaScroll(RIGHT_ANGLE);
//    x = x / 50;
//    y = -y / 50;
//
//    return Float3{ (float)x,(float)y,(float)z };
//}
//
//Float3 GetControllerLeftAngle()
//{
//    return Float3
//    {
//        GetAngleX(LEFT_ANGLE),
//        GetAngleY(LEFT_ANGLE),
//        GetAngleZ(LEFT_ANGLE)
//    };
//}
//
//Float3 GetControllerRightAngle()
//{
//    return Float3
//    {
//        GetAngleX(RIGHT_ANGLE),
//        GetAngleY(RIGHT_ANGLE),
//        GetAngleZ(RIGHT_ANGLE)
//    };
//}
//
//bool GetControllerTouchScreen()
//{
//    return IsClickingMouseLeft();
//}
//
//Float2 GetControllerTouchScreenPosition()
//{
//    Float2 pos = { 0.f,0.f };
//    if (IsClickingMouseLeft())
//    {
//        pos.x = (float)GetCursorPosX();
//        pos.y = (float)GetCursorPosY();
//    }
//
//    return pos;
//}
//
//Float2 GetOldControllerLeftStick()
//{
//    Float2 stick = { 0.f,0.f };
//    if (!gp_XGamePadOldStatus)
//    {
//        return stick;
//    }
//
//    SHORT xOffset, yOffset;
//    xOffset = gp_XGamePadOldStatus->Gamepad.sThumbLX;
//    yOffset = gp_XGamePadOldStatus->Gamepad.sThumbLY;
//    if ((xOffset < INPUT_DEADZONE) && (xOffset > -INPUT_DEADZONE))
//    {
//        xOffset = 0;
//    }
//    if ((yOffset < INPUT_DEADZONE) && (yOffset > -INPUT_DEADZONE))
//    {
//        yOffset = 0;
//    }
//
//    stick.x = (float)xOffset / (float)(0x7FFF);
//    stick.y = (float)yOffset / (float)(0x7FFF);
//
//    return stick;
//}
//
//Float2 GetOldControllerRightStick()
//{
//    Float2 stick = { 0.f,0.f };
//    if (!gp_XGamePadOldStatus)
//    {
//        return stick;
//    }
//
//    SHORT xOffset, yOffset;
//    xOffset = gp_XGamePadOldStatus->Gamepad.sThumbRX;
//    yOffset = gp_XGamePadOldStatus->Gamepad.sThumbRY;
//    if ((xOffset < INPUT_DEADZONE) && (xOffset > -INPUT_DEADZONE))
//    {
//        xOffset = 0;
//    }
//    if ((yOffset < INPUT_DEADZONE) && (yOffset > -INPUT_DEADZONE))
//    {
//        yOffset = 0;
//    }
//
//    stick.x = (float)xOffset / (float)(0x7FFF);
//    stick.y = (float)yOffset / (float)(0x7FFF);
//
//    return stick;
//}
