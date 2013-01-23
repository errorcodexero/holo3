// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "DriveBase.h"

DriveBase::DriveBase( SpeedController& front,
		      SpeedController& left,
		      SpeedController& right,
		      RateGyro& gyro )
    : Subsystem("DriveBase"),
    m_front(front),
    m_left(left),
    m_right(right),
    m_drive3(front, left, right),
    m_gyro(gyro),
    m_defaultCommand(),
    m_started(false)
{
    Stop();
}

DriveBase::~DriveBase()
{
    Stop();
}
    
void DriveBase::InitDefaultCommand()
{
    SetDefaultCommand(&m_defaultCommand);
}


void DriveBase::Stop()
{
    // stop and disable all motors
    m_drive3.StopMotor();
    // watchdogs not needed while stopped
    m_drive3.SetSafetyEnabled(false);
    dynamic_cast<MotorSafety*>(&m_front)->SetSafetyEnabled(false);
    dynamic_cast<MotorSafety*>(&m_left)->SetSafetyEnabled(false);
    dynamic_cast<MotorSafety*>(&m_right)->SetSafetyEnabled(false);
    // remember that we're stopped
    m_started = false;
}

void DriveBase::Start()
{
    if (!m_started) {
	// set all motors to 0.0 in order to feed their watchdogs
	m_drive3.SetLeftRightMotorOutputs(0.0, 0.0);
	// now enable the watchdogs
	m_drive3.SetSafetyEnabled(true);
	dynamic_cast<MotorSafety*>(&m_front)->SetSafetyEnabled(true);
	dynamic_cast<MotorSafety*>(&m_left)->SetSafetyEnabled(true);
	dynamic_cast<MotorSafety*>(&m_right)->SetSafetyEnabled(true);
	// remember that we're started
	m_started = true;
    }
}

void DriveBase::Drive3( float x, float y, float twist )
{
    if (!m_started) Start();
    // "front" and "right" for our platform are opposite the way
    //    the RobotDrive and RobotDrive3 class are set up
    x = -x;
    y = -y;

    // reduce the sensitivity to the "twist" control
    twist /= 2.;

    // add gyro compensation (adjust the "500" for best PID response)
    twist -= m_gyro.GetRate() / 500.;

    // limit the twist range to avoid normalization problems
    if (twist < -1.0) twist = -1.0;
    if (twist > 1.0) twist = 1.0;

    m_drive3.HolonomicDrive_Cartesian( x, y, twist );
}

