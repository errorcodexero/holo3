// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"

Robot::Robot()
{
    printf("Robot::Robot() has been called!\n");
}

Robot::~Robot()
{
    printf("BWA HA HA HA HA!  The Robot cannot be destroyed!\n");
    // this should throw a "can't happen" exception
}

void Robot::RobotInit()
{
    printf("Robot::RobotInit()\n");

    // connect sensors and actuators to LiveWindow
    LiveWindow* lw = LiveWindow::GetInstance();
    printf("LiveWindow has been instantiated\n");

    // instantiate sensors and actuators first,
    m_driveBaseFront = new Jaguar(1, 6);
    printf("m_driveBaseFront has been instantiated\n");
    lw->AddActuator("DriveBase", "Front", m_driveBaseFront);

    m_driveBaseLeft  = new Jaguar(1, 5);
    printf("m_driveBaseLeft has been instantiated\n");
    lw->AddActuator("DriveBase", "Left",  m_driveBaseLeft);

    m_driveBaseRight = new Jaguar(1, 4);
    printf("m_driveBaseRight has been instantiated\n");
    lw->AddActuator("DriveBase", "Right", m_driveBaseRight);

    m_blinkyPWM = new Victor(1, 1);
    printf("m_blinkyPWM has been instantiated\n");
    lw->AddActuator("BlinkyLight", "PWM", m_blinkyPWM);

    // m_unused = new Victor(1, 2);

    // then subsystems based on those sensors and actuators,
    m_driveBase = new DriveBase( m_driveBaseFront, m_driveBaseLeft,
    				 m_driveBaseRight );
    printf("m_driveBase has been instantiated\n");

    m_blinkyLight = new BlinkyLight( m_blinkyPWM );
    printf("m_blinkyLight has been instantiated\n");

    // then the OI,
    m_oi = new OI();
    printf("m_oi has been instantiated\n");

    // then commands
    m_autonomousCommand = new AutoCommand();
    printf("m_autonomousCommand has been instantiated\n");

    m_teleopCommand = new TeleCommand();
    printf("m_teleopCommand has been instantiated\n");

    // blinky lights don't need watchdogs
    m_blinkyPWM->SetSafetyEnabled(false);
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

