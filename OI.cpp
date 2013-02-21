// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "OI.h"
#include "Robot.h"

OI::OI() 
{
    // Instantiate operator controls
    m_stick = new Joystick(1);
    m_gamepadButtonA = new JoystickButton(m_stick, 1);
    m_gamepadButtonB = new JoystickButton(m_stick, 2);
    m_gamepadButtonX = new JoystickButton(m_stick, 3);
    m_gamepadButtonY = new JoystickButton(m_stick, 4);
    m_gamepadLeftBumper = new JoystickButton(m_stick, 5);
    m_gamepadRightBumper = new JoystickButton(m_stick, 6);
    m_gamepadBack = new JoystickButton(m_stick, 7);
    m_gamepadStart = new JoystickButton(m_stick, 8);
}

void OI::Initialize()
{
    // Link controls to commands
    m_gamepadButtonA->WhenPressed(new TargetCommand());
    m_gamepadButtonB->WhenPressed(new SelectTarget("right"));
    m_gamepadButtonX->WhenPressed(new SelectTarget("left"));
    m_gamepadButtonY->WhenPressed(new SelectTarget("mid"));
    m_gamepadLeftBumper->WhenPressed(new TimedDrive( 0.0, 0.0, -.35, 0.20 ));
    m_gamepadRightBumper->WhenPressed(new TimedDrive( 0.0, 0.0, .35, 0.20 ));
    m_gamepadBack->WhenPressed(new AimTrim(true));
    m_gamepadStart->WhenPressed(new AimTrim(false));
}
