// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "OI.h"
#include "AutoCommand.h"
#include "DriveCommand.h"
#include "TeleCommand.h"

OI::OI()
{
    // Process operator interface input here.
    stick = new Joystick(1);

    // SmartDashboard Buttons
}

Joystick* OI::getStick()
{
    return stick;
}

