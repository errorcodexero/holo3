// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"

DriveBase::DriveBase( SpeedController* front,
		      SpeedController* left,
		      SpeedController* right )
    : Subsystem("DriveBase"),
    m_front(front),
    m_left(left),
    m_right(right),
    m_drive3(new RobotDrive3(front, left, right)),
    // TBD: add a turn-rate gyro
    m_started(false)
{
    Stop();
}

DriveBase::~DriveBase()
{
    Stop();
    delete m_drive3;
}
    
void DriveBase::InitDefaultCommand()
{
    SetDefaultCommand(new DriveCommand());
}


void DriveBase::Stop()
{
    // stop and disable all motors
    m_drive3->StopMotor();
    // watchdogs not needed while stopped
    m_drive3->SetSafetyEnabled(false);
    dynamic_cast<MotorSafety*>(m_front)->SetSafetyEnabled(false);
    dynamic_cast<MotorSafety*>(m_left)->SetSafetyEnabled(false);
    dynamic_cast<MotorSafety*>(m_right)->SetSafetyEnabled(false);
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
	dynamic_cast<MotorSafety*>(m_front)->SetSafetyEnabled(true);
	dynamic_cast<MotorSafety*>(m_left)->SetSafetyEnabled(true);
	dynamic_cast<MotorSafety*>(m_right)->SetSafetyEnabled(true);
	// remember that we're started
	m_started = true;
    }
}

void DriveBase::Drive3( float x, float y, float twist )
{
    // TBD: add turn-rate gyro output as the fourth argument
    // to HolonomicDrive_Cartesian
    if (!m_started) Start();
    // "front" and "right" for our platform are opposite the way
    // the drive framework is set up.
    x = -x;
    y = -y;
    // reduce the sensitivity to the "twist" control
    twist /= 4.;
    m_drive3->HolonomicDrive_Cartesian( x, y, twist );
}

