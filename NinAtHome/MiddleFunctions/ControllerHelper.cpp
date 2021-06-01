#include "ControllerHelper.h"
#include <iostream>

#define INPUT_DEADZONE (0.24f * float(0x7FFF))

DWORD const g_XGamePadIndex = 0;
XINPUT_STATE* gp_XGamePadStatus = nullptr;
XINPUT_STATE* gp_XGamePadOldStatus = nullptr;

XINPUT_VIBRATION* gp_VibraHandle = nullptr;
int g_VibrationLeftFrame = 0;
int g_VibrationRightFrame = 0;

void InitController()
{
    gp_XGamePadStatus = new XINPUT_STATE;

    DWORD result = XInputGetState(
        g_XGamePadIndex, gp_XGamePadStatus);
    if (result == ERROR_SUCCESS)
    {
        gp_XGamePadOldStatus = new XINPUT_STATE;
        *gp_XGamePadOldStatus = *gp_XGamePadStatus;

        gp_VibraHandle = new XINPUT_VIBRATION{ 0 };
    }
    else
    {
        delete gp_XGamePadStatus;
        gp_XGamePadStatus = nullptr;
        NN_LOG("could not find xbox gamepad\n");
    }
}

void UninitController()
{
    if (gp_XGamePadStatus)
    {
        delete gp_XGamePadStatus;
    }
    if (gp_XGamePadOldStatus)
    {
        delete gp_XGamePadOldStatus;
    }
    if (gp_VibraHandle)
    {
        delete gp_VibraHandle;
    }
}

Float2 GetOldControllerLeftStick();

Float2 GetOldControllerRightStick();

void UpdateController()
{
    if (gp_XGamePadStatus && gp_XGamePadOldStatus)
    {
        *gp_XGamePadOldStatus = *gp_XGamePadStatus;
    }
    else
    {
        /*std::cout <<
            "sth wrong with getting xinput status" << std::endl;*/
        return;
    }

    DWORD result = XInputGetState(
        g_XGamePadIndex, gp_XGamePadStatus);

    if (result != ERROR_SUCCESS)
    {
        NN_LOG("sth wrong with polling xinput status");
    }

    if (g_VibrationLeftFrame > 0)
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
    }
}

bool GetControllerPress(int button)
{
    // TODO need to add shoulder key trigger here
    if (!gp_XGamePadStatus)
    {
        return false;
    }

    if (button >= 0)
    {
        return (gp_XGamePadStatus->Gamepad.wButtons & button) ?
            true : false;
    }
    else
    {
        switch (button)
        {
        case SZL:
            return (gp_XGamePadStatus->Gamepad.bLeftTrigger > 5) ?
                true : false;
        case SZR:
            return (gp_XGamePadStatus->Gamepad.bRightTrigger > 5) ?
                true : false;
        case LL:
            return (GetControllerLeftStick().x < -0.f) ?
                true : false;
        case LU:
            return (GetControllerLeftStick().y > 0.f) ?
                true : false;
        case LR:
            return (GetControllerLeftStick().x > 0.f) ?
                true : false;
        case LD:
            return (GetControllerLeftStick().y < -0.f) ?
                true : false;
        case RL:
            return (GetControllerRightStick().x < -0.f) ?
                true : false;
        case RU:
            return (GetControllerRightStick().y > 0.f) ?
                true : false;
        case RR:
            return (GetControllerRightStick().x > 0.f) ?
                true : false;
        case RD:
            return (GetControllerRightStick().y < -0.f) ?
                true : false;
        default:
            return false;
        }
    }
}

bool GetControllerTrigger(int button)
{
    // TODO need to add shoulder key trigger here
    if (!gp_XGamePadStatus)
    {
        return false;
    }

    if (button >= 0)
    {
        bool oldStatus = false, thisStatus = false;
        oldStatus = (gp_XGamePadOldStatus->Gamepad.wButtons & button) ?
            true : false;
        thisStatus = (gp_XGamePadStatus->Gamepad.wButtons & button) ?
            true : false;

        return ((!oldStatus) && thisStatus);
    }
    else
    {
        bool oldStatus = false, thisStatus = false;
        switch (button)
        {
        case SZL:
            oldStatus =
                (gp_XGamePadOldStatus->Gamepad.bLeftTrigger > 5) ?
                true : false;
            thisStatus =
                (gp_XGamePadStatus->Gamepad.bLeftTrigger > 5) ?
                true : false;
            break;
        case SZR:
            oldStatus =
                (gp_XGamePadOldStatus->Gamepad.bRightTrigger > 5) ?
                true : false;
            thisStatus =
                (gp_XGamePadStatus->Gamepad.bRightTrigger > 5) ?
                true : false;
            break;
        case LL:
            oldStatus =
                (GetOldControllerLeftStick().x < -0.f) ? true : false;
            thisStatus =
                (GetControllerLeftStick().x < -0.f) ? true : false;
            break;
        case LU:
            oldStatus =
                (GetOldControllerLeftStick().y > 0.f) ? true : false;
            thisStatus =
                (GetControllerLeftStick().y > 0.f) ? true : false;
            break;
        case LR:
            oldStatus =
                (GetOldControllerLeftStick().x > 0.f) ? true : false;
            thisStatus =
                (GetControllerLeftStick().x > 0.f) ? true : false;
            break;
        case LD:
            oldStatus =
                (GetOldControllerLeftStick().y < -0.f) ? true : false;
            thisStatus =
                (GetControllerLeftStick().y < -0.f) ? true : false;
            break;
        case RL:
            oldStatus =
                (GetOldControllerRightStick().x < -0.f) ? true : false;
            thisStatus =
                (GetControllerRightStick().x < -0.f) ? true : false;
            break;
        case RU:
            oldStatus =
                (GetOldControllerRightStick().y > 0.f) ? true : false;
            thisStatus =
                (GetControllerRightStick().y > 0.f) ? true : false;
            break;
        case RR:
            oldStatus =
                (GetOldControllerRightStick().x > 0.f) ? true : false;
            thisStatus =
                (GetControllerRightStick().x > 0.f) ? true : false;
            break;
        case RD:
            oldStatus =
                (GetOldControllerRightStick().y < -0.f) ? true : false;
            thisStatus =
                (GetControllerRightStick().y < -0.f) ? true : false;
            break;
        default:
            return false;
        }

        return ((!oldStatus) && thisStatus);
    }
}

Float2 GetControllerLeftStick()
{
    Float2 stick = { 0.f,0.f };
    if (!gp_XGamePadStatus)
    {
        return stick;
    }

    SHORT xOffset, yOffset;
    xOffset = gp_XGamePadStatus->Gamepad.sThumbLX;
    yOffset = gp_XGamePadStatus->Gamepad.sThumbLY;
    if ((xOffset < INPUT_DEADZONE) && (xOffset > -INPUT_DEADZONE))
    {
        xOffset = 0;
    }
    if ((yOffset < INPUT_DEADZONE) && (yOffset > -INPUT_DEADZONE))
    {
        yOffset = 0;
    }

    stick.x = (float)xOffset / (float)(0x7FFF);
    stick.y = (float)yOffset / (float)(0x7FFF);

    return stick;
}

Float2 GetControllerRightStick()
{
    Float2 stick = { 0.f,0.f };
    if (!gp_XGamePadStatus)
    {
        return stick;
    }

    SHORT xOffset, yOffset;
    xOffset = gp_XGamePadStatus->Gamepad.sThumbRX;
    yOffset = gp_XGamePadStatus->Gamepad.sThumbRY;
    if ((xOffset < INPUT_DEADZONE) && (xOffset > -INPUT_DEADZONE))
    {
        xOffset = 0;
    }
    if ((yOffset < INPUT_DEADZONE) && (yOffset > -INPUT_DEADZONE))
    {
        yOffset = 0;
    }

    stick.x = (float)xOffset / (float)(0x7FFF);
    stick.y = (float)yOffset / (float)(0x7FFF);

    return stick;
}

void SetControllerLeftVibration(int frame)
{
    gp_VibraHandle->wLeftMotorSpeed = 65535 / 2;
    XInputSetState(g_XGamePadIndex, gp_VibraHandle);
    g_VibrationLeftFrame = frame;
}

void SetControllerRightVibration(int frame)
{
    gp_VibraHandle->wRightMotorSpeed = 65535 / 2;
    XInputSetState(g_XGamePadIndex, gp_VibraHandle);
    g_VibrationRightFrame = frame;
}

Float3 GetControllerLeftAcceleration()
{
    int x, y, z;
    x = GetDeltaCursorX(LEFT_ANGLE);
    y = GetDeltaCursorY(LEFT_ANGLE);
    z = GetDeltaScroll(LEFT_ANGLE);
    x = x / 50;
    y = -y / 50;

    return Float3{ (float)x,(float)y,(float)z };
}

Float3 GetControllerRightAcceleration()
{
    int x, y, z;
    x = GetDeltaCursorX(RIGHT_ANGLE);
    y = GetDeltaCursorY(RIGHT_ANGLE);
    z = GetDeltaScroll(RIGHT_ANGLE);
    x = x / 50;
    y = -y / 50;

    return Float3{ (float)x,(float)y,(float)z };
}

Float3 GetControllerLeftAngle()
{
    return Float3
    {
        GetAngleX(LEFT_ANGLE),
        GetAngleY(LEFT_ANGLE),
        GetAngleZ(LEFT_ANGLE)
    };
}

Float3 GetControllerRightAngle()
{
    return Float3
    {
        GetAngleX(RIGHT_ANGLE),
        GetAngleY(RIGHT_ANGLE),
        GetAngleZ(RIGHT_ANGLE)
    };
}

bool GetControllerTouchScreen()
{
    return IsClickingMouseLeft();
}

Float2 GetControllerTouchScreenPosition()
{
    Float2 pos = { 0.f,0.f };
    if (IsClickingMouseLeft())
    {
        pos.x = (float)GetCursorPosX();
        pos.y = (float)GetCursorPosY();
    }

    return pos;
}

Float2 GetOldControllerLeftStick()
{
    Float2 stick = { 0.f,0.f };
    if (!gp_XGamePadOldStatus)
    {
        return stick;
    }

    SHORT xOffset, yOffset;
    xOffset = gp_XGamePadOldStatus->Gamepad.sThumbLX;
    yOffset = gp_XGamePadOldStatus->Gamepad.sThumbLY;
    if ((xOffset < INPUT_DEADZONE) && (xOffset > -INPUT_DEADZONE))
    {
        xOffset = 0;
    }
    if ((yOffset < INPUT_DEADZONE) && (yOffset > -INPUT_DEADZONE))
    {
        yOffset = 0;
    }

    stick.x = (float)xOffset / (float)(0x7FFF);
    stick.y = (float)yOffset / (float)(0x7FFF);

    return stick;
}

Float2 GetOldControllerRightStick()
{
    Float2 stick = { 0.f,0.f };
    if (!gp_XGamePadOldStatus)
    {
        return stick;
    }

    SHORT xOffset, yOffset;
    xOffset = gp_XGamePadOldStatus->Gamepad.sThumbRX;
    yOffset = gp_XGamePadOldStatus->Gamepad.sThumbRY;
    if ((xOffset < INPUT_DEADZONE) && (xOffset > -INPUT_DEADZONE))
    {
        xOffset = 0;
    }
    if ((yOffset < INPUT_DEADZONE) && (yOffset > -INPUT_DEADZONE))
    {
        yOffset = 0;
    }

    stick.x = (float)xOffset / (float)(0x7FFF);
    stick.y = (float)yOffset / (float)(0x7FFF);

    return stick;
}
