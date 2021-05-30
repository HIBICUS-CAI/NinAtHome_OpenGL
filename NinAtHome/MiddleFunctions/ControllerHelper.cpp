#include "ControllerHelper.h"
#include <iostream>

#define INPUT_DEADZONE (0.24f * float(0x7FFF))

XINPUT_STATE* gp_XGamePadStatus = nullptr;
XINPUT_STATE* gp_XGamePadOldStatus = nullptr;
DWORD const g_XGamePadIndex = 0;

void InitController()
{
    gp_XGamePadStatus = new XINPUT_STATE;

    DWORD result = XInputGetState(
        g_XGamePadIndex, gp_XGamePadStatus);
    if (result == ERROR_SUCCESS)
    {
        gp_XGamePadOldStatus = new XINPUT_STATE;
        *gp_XGamePadOldStatus = *gp_XGamePadStatus;
    }
    else
    {
        delete gp_XGamePadStatus;
        gp_XGamePadStatus = nullptr;
        std::cout << "could not find xbox gamepad" << std::endl;
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
}

void UpdateController()
{
    if (gp_XGamePadStatus && gp_XGamePadOldStatus)
    {
        *gp_XGamePadOldStatus = *gp_XGamePadStatus;
    }
    else
    {
        std::cout <<
            "sth wrong with getting xinput status" << std::endl;
        return;
    }

    DWORD result = XInputGetState(
        g_XGamePadIndex, gp_XGamePadStatus);

    if (result != ERROR_SUCCESS)
    {
        std::cout <<
            "sth wrong with polling xinput status" << std::endl;
    }
}

bool GetControllerPress(int button)
{
    // TODO need to add shoulder key trigger here
    if (!gp_XGamePadStatus)
    {
        return false;
    }

    return (gp_XGamePadStatus->Gamepad.wButtons & button) ?
        true : false;
}

bool GetControllerTrigger(int button)
{
    // TODO need to add shoulder key trigger here
    if (!gp_XGamePadStatus)
    {
        return false;
    }

    bool oldStatus = false, thisStatus = false;
    oldStatus = (gp_XGamePadOldStatus->Gamepad.wButtons & button) ?
        true : false;
    thisStatus = (gp_XGamePadStatus->Gamepad.wButtons & button) ?
        true : false;

    return ((!oldStatus) && thisStatus);
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

}

void SetControllerRightVibration(int frame)
{

}
