// FIRST Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "OI.h"
#include "TimedDrive.h"
#include "Rotate.h"


OI::OI() 
{
    // Instantiate operator controls
    m_pDS = DriverStation::GetInstance();
    m_pEIO = &m_pDS->GetEnhancedIO();
    m_pLCD = DriverStationLCD::GetInstance();

    m_pStick = new Joystick(1);
    m_pGamepadButtonA     = new JoystickButton(m_pStick, 1);
    m_pGamepadButtonB     = new JoystickButton(m_pStick, 2);
    m_pGamepadButtonX     = new JoystickButton(m_pStick, 3);
    m_pGamepadButtonY     = new JoystickButton(m_pStick, 4);
    m_pGamepadLeftBumper  = new JoystickButton(m_pStick, 5);
    m_pGamepadRightBumper = new JoystickButton(m_pStick, 6);
    m_pGamepadBack        = new JoystickButton(m_pStick, 7);
    m_pGamepadStart       = new JoystickButton(m_pStick, 8);
#ifdef PRACTICE_OI
    m_pAutoSelect         = new DSAnalogInput(m_pEIO, 1);
#else // COMPETITION_OI
    m_pAutoSelect         = new DSAnalogInput(m_pEIO, 5);
#endif
    m_pShooterTarget      = new DSAnalogInput(m_pEIO, 6);
    // digital inputs

    // digital input 2 not connected/not used
#ifdef PRACTICE_OI
    m_pLightsOn           = new DSDigitalInput(m_pEIO, 2,
				    DriverStationEnhancedIO::kInputPullUp,
				    false);	// active-low toggle
#else // COMPETITION_OI
    m_pLightsOn           = new DSDigitalInput(m_pEIO, 2,
				    DriverStationEnhancedIO::kInputPullUp,
				    true);	// active-high toggle
#endif

#ifdef PRACTICE_OI
    m_pDriverSelect       = new DSDigitalInput(m_pEIO, 3,
				    DriverStationEnhancedIO::kInputPullUp,
				    false);	// active-low toggle
#else // COMPETITION_OI
    m_pDriverSelect       = new DSDigitalInput(m_pEIO, 3,
				    DriverStationEnhancedIO::kInputPullUp,
				    true);	// active-high toggle
#endif




#ifdef PRACTICE_OI
    m_pLearn              = new DSDigitalInput(m_pEIO, 12,
				    DriverStationEnhancedIO::kInputPullUp,
				    false);	// active-low pushbutton
#else // COMPETITION_OI
    m_pLearn              = new DSDigitalInput(m_pEIO, 7,
				    DriverStationEnhancedIO::kInputPullUp,
				    false);	// active-low pushbutton
#endif
}

OI::~OI()
{
    // initialized in constructor
    delete m_pStick;
    delete m_pGamepadButtonA;
    delete m_pGamepadButtonB;
    delete m_pGamepadButtonX;
    delete m_pGamepadButtonY;
    delete m_pGamepadLeftBumper;
    delete m_pGamepadRightBumper;
    delete m_pGamepadBack;
    delete m_pGamepadStart;
    delete m_pAutoSelect;
    delete m_pLightsOn;
    delete m_pDriverSelect;
    delete m_pLearn;


    // initialized in Initialize()
    if (m_pNudgeLeft) delete m_pNudgeLeft;
    if (m_pNudgeRight) delete m_pNudgeRight;
    if (m_pRotateFwd) delete m_pRotateFwd;
    if (m_pRotateRev) delete m_pRotateRev;
}


void OI::Initialize()
{
    // Link controls to commands
    m_pNudgeLeft = new TimedDrive( 0.0, 0.0, -.20, 0.20 );
    m_pGamepadLeftBumper->WhenPressed(m_pNudgeLeft);

    m_pNudgeRight = new TimedDrive( 0.0, 0.0, .20, 0.20 );
    m_pGamepadRightBumper->WhenPressed(m_pNudgeRight);

    m_pRotateFwd = new Rotate(1);
    SmartDashboard::PutData("Rotate Fwd", m_pRotateFwd);

    m_pRotateRev = new Rotate(-1);
    SmartDashboard::PutData("Rotate Rev", m_pRotateRev);
}

