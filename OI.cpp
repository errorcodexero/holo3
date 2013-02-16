// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "OI.h"
#include "AutoCommand.h"
#include "DriveCommand.h"
#include "TeleCommand.h"
#include "Commands/SelectTarget.h"

OI::OI() 


{
    // Process operator interface input here.
    stick = new Joystick(1);
    button1 = new JoystickButton(stick, 1);
    button2 = new JoystickButton(stick, 2);
    button3 = new JoystickButton(stick, 3);
    button4 = new JoystickButton(stick, 4);
    button5 = new JoystickButton(stick, 5);
    button6 = new JoystickButton(stick, 6);
    button7 = new JoystickButton(stick, 7);
    button8 = new JoystickButton(stick, 8);
    
    button1->WhenPressed(new TargetCommand());
    button2->WhenPressed(new SelectTarget("right"));
    button3->WhenPressed(new SelectTarget("left"));
    button4->WhenPressed(new SelectTarget("mid"));
    // SmartDashboard Buttons
    
    
}

Joystick* OI::getStick()
{
    return stick;
}

