// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "OI.h"

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

    m_pClimber            = new DSAnalogInput(m_pEIO, 1);
    m_pTip                = new DSAnalogInput(m_pEIO, 2);
    m_pSpeedAdjust        = new DSAnalogInput(m_pEIO, 3);
    m_pShooterPosition    = new DSAnalogInput(m_pEIO, 4);

    m_pDump               = new DSDigitalInput(m_pEIO, 1);
    m_pCameraLight        = new DSDigitalInput(m_pEIO, 2);
    m_pCameraPosition     = new DSDigitalInput(m_pEIO, 3);
    m_pQueryButton        = new DSDigitalInput(m_pEIO, 4);
    m_pSpeedOverride      = new DSDigitalInput(m_pEIO, 5);
    m_pLaunch             = new DSDigitalInput(m_pEIO, 6);
    m_pKey                = new DSDigitalInput(m_pEIO, 7);

    m_pReadyLED           = new DSDigitalOutput(m_pEIO, 8);
}

void OI::Initialize()
{
    // Link controls to commands
    m_pGamepadButtonA->WhenPressed(new TargetCommand());
    m_pGamepadButtonB->WhenPressed(new SelectTarget("right"));
    m_pGamepadButtonX->WhenPressed(new SelectTarget("left"));
    m_pGamepadButtonY->WhenPressed(new SelectTarget("mid"));
    m_pGamepadLeftBumper->WhenPressed(new TimedDrive( 0.0, 0.0, -.35, 0.20 ));
    m_pGamepadRightBumper->WhenPressed(new TimedDrive( 0.0, 0.0, .35, 0.20 ));
    m_pGamepadBack->WhenPressed(new AimTrim(true));
    m_pGamepadStart->WhenPressed(new AimTrim(false));

    m_pRotateFwd = new Rotate(1);
    SmartDashboard::PutData("Rotate Fwd", m_pRotateFwd);

    m_pRotateRev = new Rotate(-1);
    SmartDashboard::PutData("Rotate Rev", m_pRotateRev);

    m_pShootShort = new ShootCommand( Shooter::kShort );
    SmartDashboard::PutData("Shoot Short", m_pShootShort);

    m_pShootMid = new ShootCommand( Shooter::kMid );
    SmartDashboard::PutData("Shoot Mid", m_pShootMid);

    m_pShootLong = new ShootCommand( Shooter::kLong );
    SmartDashboard::PutData("Shoot Long", m_pShootLong);

    // m_pBlinkyOn = new BlinkyOn();
    // SmartDashboard::PutData("Blinky On", m_pBlinkyOn);
    // m_pCameraLight->WhileHeld(m_pBlinkyOn);
}

