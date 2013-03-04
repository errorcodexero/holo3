// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

class OI;

#ifndef OI_H
#define OI_H

#include <WPILib.h>
#include "Robot.h"

class DSAnalogInput {
private:
    DriverStationEnhancedIO *m_pEIO;
    UINT32 m_channel;

public:
    DSAnalogInput( DriverStationEnhancedIO *pEIO, UINT32 channel ) :
	m_pEIO(pEIO),
	m_channel(channel)
    {
	;
    }

    ~DSAnalogInput() {}

    double GetAnalog() {
	return m_pEIO->GetAnalogInRatio(m_channel); 
    }

    int GetDigital( int numPositions ) {
	return (int)(GetAnalog() * numPositions);
    }
};

class DSDigitalInput : public Button {
private:
    DriverStationEnhancedIO *m_pEIO;
    UINT32 m_channel;
    bool m_active;

public:
    DSDigitalInput( DriverStationEnhancedIO *pEIO, UINT32 channel,
    		    DriverStationEnhancedIO::tDigitalConfig config,
		    bool active ) :
	m_pEIO(pEIO),
	m_channel(channel),
	m_active(active)
    {
	m_pEIO->SetDigitalConfig(channel, config);
    }

    ~DSDigitalInput() {}

    // return true when the button is in the active state, whether high or low
    bool Get() {
	return (m_pEIO->GetDigital(m_channel) == m_active);
    }
};

class DSDigitalOutput {
private:
    DriverStationEnhancedIO *m_pEIO;
    UINT32 m_channel;

public:
    DSDigitalOutput( DriverStationEnhancedIO *pEIO, UINT32 channel ) :
	m_pEIO(pEIO),
	m_channel(channel)
    {
	m_pEIO->SetDigitalConfig(channel,
	    DriverStationEnhancedIO::kOutput);
    }

    ~DSDigitalOutput() {}

    void Set( bool value ) {
	return m_pEIO->SetDigitalOutput(m_channel, value);
    }
};

class OI {
private:
    DriverStation *m_pDS;
    DriverStationEnhancedIO *m_pEIO;
    DriverStationLCD *m_pLCD;

    Joystick* m_pStick;
    JoystickButton* m_pGamepadButtonA;
    JoystickButton* m_pGamepadButtonB;
    JoystickButton* m_pGamepadButtonX;
    JoystickButton* m_pGamepadButtonY;
    JoystickButton* m_pGamepadLeftBumper;
    JoystickButton* m_pGamepadRightBumper;
    JoystickButton* m_pGamepadBack;
    JoystickButton* m_pGamepadStart;

    DSAnalogInput* m_pClimber;
    DSAnalogInput* m_pTip;
    DSAnalogInput* m_pSpeedAdjust;
    DSAnalogInput* m_pShooterTarget;

    DSDigitalInput* m_pDump;
    DSDigitalInput* m_pCameraLight;
    DSDigitalInput* m_pCameraPosition;
    DSDigitalInput* m_pQueryButton;
    DSDigitalInput* m_pManualOverride;
    DSDigitalInput* m_pLaunch;
    DSDigitalInput* m_pKey;

    DSDigitalOutput* m_pReadyLED;

    // aiming
    class TimedDrive* m_pNudgeLeft;
    class TimedDrive* m_pNudgeRight;

    class Rotate* m_pRotateFwd;
    class Rotate* m_pRotateRev;

    class AimTrim* m_pTrimLeft;
    class AimTrim* m_pTrimRight;

    // shooting
    class TargetCommand* m_pTargetCommand;

    class SelectTarget* m_pSelectTargetLeft;
    class SelectTarget* m_pSelectTargetRight;
    class SelectTarget* m_pSelectTargetMid;

    class ShootCommand* m_pShootShort;
    class ShootCommand* m_pShootMid;
    class ShootCommand* m_pShootLong;

    class ShootManual*  m_pShootManual;

    class TiltCommand* m_pTiltShort;
    class TiltCommand* m_pTiltMid;
    class TiltCommand* m_pTiltLong;

    // reset (for pit use!)
    class ResetRobot* m_pResetRobot;

public:
    OI();
    ~OI();
    void Initialize();
    DriverStation *getDS() { return m_pDS; }
    Joystick* getStick() { return m_pStick; }
    DriverStationEnhancedIO* getEIO() { return m_pEIO; }
    DriverStationLCD* getLCD() { return m_pLCD; }
    int getTarget() { return m_pShooterTarget->GetDigital(3); }
    double getSpeedAdjust() { return m_pSpeedAdjust->GetAnalog(); }
    void setReadyLED( bool value ) { m_pReadyLED->Set(value); }
    bool getLaunch() { return m_pLaunch->Get(); }
};

#endif
