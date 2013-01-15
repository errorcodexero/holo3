// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"

Robot::Robot() :
    // instantiate sensors and actuators first,
    m_driveBaseFront( new Jaguar(1, 1) ),
    m_driveBaseLeft(  new Jaguar(1, 2) ),
    m_driveBaseRight( new Jaguar(1, 3) ),
    m_blinkyPWM( new Victor(1, 4) ),
    // then subsystems based on those sensors and actuators,
    m_driveBase( new DriveBase( m_driveBaseFront, m_driveBaseLeft,
    				m_driveBaseRight ) ),
    m_blinkyLight( new BlinkyLight( m_blinkyPWM ) ),
    // then the OI,
    m_oi( new OI() ),
    // then commands
    m_autonomousCommand( new AutoCommand() ),
    m_teleopCommand( new TeleCommand() )
{
    // connect sensors and actuators to LiveWindow
    LiveWindow* lw = LiveWindow::GetInstance();
    lw->AddActuator("DriveBase", "Front", m_driveBaseFront);
    lw->AddActuator("DriveBase", "Left",  m_driveBaseLeft);
    lw->AddActuator("DriveBase", "Right", m_driveBaseRight);
    lw->AddActuator("BlinkyLight", "PWM", m_blinkyPWM);

    // blinky lights don't need watchdogs
    m_blinkyPWM->SetSafetyEnabled(false);
}

Robot::~Robot()
{
    printf("BWA HA HA HA HA!  The Robot cannot be destroyed!\n");
    // this should throw a "can't happen" exception
}

void Robot::RobotInit()
{
    // initialization done in constructor
}

void Robot::Cancel()
{
    if (m_autonomousCommand->IsRunning()) {
	m_autonomousCommand->Cancel();
    }
    if (m_teleopCommand->IsRunning()) {
	m_teleopCommand->Cancel();
    }
    m_driveBase->Stop();
    m_blinkyLight->Set(0.0);
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
    m_autonomousCommand->Start();
}
    
void Robot::AutonomousPeriodic()
{
    Scheduler::GetInstance()->Run();
}
    
void Robot::TeleopInit()
{
    Cancel();
    m_teleopCommand->Start();
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

