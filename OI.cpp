// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "OI.h"
#include "Robot.h"

OI::OI() 
{
    // Process operator interface input here.
    m_stick = new Joystick(1);

    m_gamepadButtonA = new JoystickButton(m_stick, 1);
    m_gamepadButtonA->WhenPressed(new TargetCommand());

    m_gamepadButtonB = new JoystickButton(m_stick, 2);
    m_gamepadButtonB->WhenPressed(new SelectTarget("right"));

    m_gamepadButtonX = new JoystickButton(m_stick, 3);
    m_gamepadButtonX->WhenPressed(new SelectTarget("left"));

    m_gamepadButtonY = new JoystickButton(m_stick, 4);
    m_gamepadButtonY->WhenPressed(new SelectTarget("mid"));

    m_gamepadLeftBumper = new JoystickButton(m_stick, 5);
    m_gamepadLeftBumper->WhenPressed(new TimedDrive( 0.0, 0.0, -.35, 0.20 ));

    m_gamepadRightBumper = new JoystickButton(m_stick, 6);
    m_gamepadRightBumper->WhenPressed(new TimedDrive( 0.0, 0.0, .35, 0.20 ));

    m_gamepadBack = new JoystickButton(m_stick, 7);
    m_gamepadBack->WhenPressed(new AimTrim(true));

    m_gamepadStart = new JoystickButton(m_stick, 8);
    m_gamepadStart->WhenPressed(new AimTrim(false));
}
