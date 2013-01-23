// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"


Robot::Robot() :
    m_driveBaseFront(1, 6),
    m_driveBaseLeft(1, 5),
    m_driveBaseRight(1, 4),
    m_gyro(1, 1),
    m_blinkyPWM(1, 1),
    // m_unused(1, 2),
    m_driveBase( m_driveBaseFront, m_driveBaseLeft,
		 m_driveBaseRight, m_gyro ),
    m_blinkyLight( &m_blinkyPWM ),
    m_oi(new OI()),
    m_autonomousCommand(),
    m_teleopCommand()
{
    printf("Robot::Robot() has been called!\n");

    // blinky lights don't need watchdogs
    m_blinkyPWM.SetSafetyEnabled(false);
}

Robot::~Robot()
{
    printf("BWA HA HA HA HA!  The Robot cannot be destroyed!\n");
}

void Robot::RobotInit()
{
    printf("Robot::RobotInit()\n");

    // connect sensors and actuators to LiveWindow
    LiveWindow* lw = LiveWindow::GetInstance();

    lw->AddActuator("DriveBase", "Front", &m_driveBaseFront);
    lw->AddActuator("DriveBase", "Left",  &m_driveBaseLeft);
    lw->AddActuator("DriveBase", "Right", &m_driveBaseRight);
    lw->AddSensor("DriveBase", "Gyro", &m_gyro);
    lw->AddActuator("BlinkyLight", "PWM", &m_blinkyPWM);
}

void Robot::Cancel()
{
    if (m_autonomousCommand.IsRunning()) {
	m_autonomousCommand.Cancel();
    }
    if (m_teleopCommand.IsRunning()) {
	m_teleopCommand.Cancel();
    }
    m_driveBase.Stop();
    m_blinkyLight.Set(0.0);
}
	
void Robot::DisabledInit()
{
    Cancel();
}

void Robot::DisabledPeriodic()
{
    Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit()
{
    Cancel();
    m_autonomousCommand.Start();
}
    
void Robot::AutonomousPeriodic()
{
    Scheduler::GetInstance()->Run();
}
    
void Robot::TeleopInit()
{
    Cancel();
    m_teleopCommand.Start();
}
    
void Robot::TeleopPeriodic()
{
    Scheduler::GetInstance()->Run();
}

void Robot::TestInit()
{
    Cancel();
}

void Robot::TestPeriodic()
{
    LiveWindow::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot);

