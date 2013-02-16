// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "DriveBase.h"

DriveBase::DriveBase( SpeedController * rear,
		      SpeedController * right,
		      SpeedController * left,
		      RateGyro * gyro )
    : Subsystem("DriveBase"),
    m_rear(rear),
    m_right(right),
    m_left(left),
    m_drive3(NULL),
    m_gyro(gyro),
    m_defaultCommand(NULL),
    m_started(false)
{
    m_drive3 = new RobotDrive3(rear, right, left);
    Stop();
}

DriveBase::~DriveBase()
{
    // This is dangerous because the default command
    // may still be (probably still is) registered within the
    // Command/Scheduler subsystem
    delete m_defaultCommand;
    delete m_drive3;
    Stop();
}
    
void DriveBase::InitDefaultCommand()
{
    if (!m_defaultCommand) {
	m_defaultCommand = new DriveCommand();
	SetDefaultCommand(m_defaultCommand);
    }
}

void DriveBase::Stop()
{
    // stop and disable all motors
    m_drive3->StopMotor();
    // watchdogs not needed while stopped
    m_drive3->SetSafetyEnabled(false);
    dynamic_cast<MotorSafety*>(m_rear)->SetSafetyEnabled(false);
    dynamic_cast<MotorSafety*>(m_right)->SetSafetyEnabled(false);
    dynamic_cast<MotorSafety*>(m_left)->SetSafetyEnabled(false);
    // remember that we're stopped
    m_started = false;
}

void DriveBase::Start()
{
    if (!m_started) {
	// set all motors to 0.0 in order to feed their watchdogs
	m_drive3->SetLeftRightMotorOutputs(0.0, 0.0);
	// now enable the watchdogs
	m_drive3->SetSafetyEnabled(true);
	dynamic_cast<MotorSafety*>(m_rear)->SetSafetyEnabled(true);
	dynamic_cast<MotorSafety*>(m_right)->SetSafetyEnabled(true);
	dynamic_cast<MotorSafety*>(m_left)->SetSafetyEnabled(true);
	// remember that we're started
	m_started = true;
    }
}

void DriveBase::Drive3( float x, float y, float twist )
{
    if (!m_started) Start();

    // Reduce the sensitivity to the "twist" control.
    // Also reverse the direction, since our drive base is a mirror
    // image of what RobotDrive3 expects.
    twist = -twist / 2.;

    // add gyro compensation (adjust the "500" for best PID response)
    twist -= m_gyro->GetRate() / 500.;

    // limit the twist range to avoid normalization problems
    if (twist < -1.0) twist = -1.0;
    if (twist > 1.0) twist = 1.0;

    m_drive3->HolonomicDrive_Cartesian( x, y, twist );
}

