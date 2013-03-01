// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef OI_H
#define OI_H

#include <WPILib.h>
#include "Robot.h"


class OI {
private:
    Joystick* m_stick;
    JoystickButton* m_gamepadButtonA;
    JoystickButton* m_gamepadButtonB;
    JoystickButton* m_gamepadButtonX;
    JoystickButton* m_gamepadButtonY;
    JoystickButton* m_gamepadLeftBumper;
    JoystickButton* m_gamepadRightBumper;
    JoystickButton* m_gamepadBack;
    JoystickButton* m_gamepadStart;

    // aiming
    Rotate* m_rotate;

    // shooting
    ShootCommand* m_shootShort;
    ShootCommand* m_shootMid;
    ShootCommand* m_shootLong;
    
    //Tilting
    TiltCommand* m_tiltShort;
    TiltCommand* m_tiltLong;
    TiltCommand* m_tiltMid;

public:
    OI();
    void Initialize();
    Joystick* getStick() { return m_stick; }
};

#endif
