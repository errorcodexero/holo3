// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"
#include "OI.h"



Robot::Robot()
{
    printf("Robot::Robot() has been called!\n");
}

Robot::~Robot()
{
    printf("BWA HA HA HA HA!  The Robot cannot be destroyed!\n");
}

void Robot::RobotInit()
{
    printf("Robot::RobotInit()\n");

    m_oi = new OI();

    // subsystems

    m_compressor = new Compressor( DIGITAL_PRESSURE_SWITCH, RELAY_COMPRESSOR );

    m_driveBase = new DriveBase( PWM_DRIVE_LEFT, PWM_DRIVE_RIGHT,
    				 PWM_DRIVE_REAR, ANALOG_GYRO );

    m_shooter = new Shooter( CAN_SHOOTER, SOLENOID_SHOOTER_EXTEND,
			     DIGITAL_SHOOTER_CENTER, SOLENOID_SHOOTER_INJECT );
    
    m_blinkyLight = new BlinkyLight( PWM_BLINKY );

    // commands

    m_autonomousCommand = new AutoCommand();

    // link operator controls to commands
    m_oi->Initialize();

    // Now that everything else is set up, start the compressor
    m_compressor->Start();
}

void Robot::Cancel()
{
    printf("Robot::Cancel\n");
    if (m_autonomousCommand->IsRunning()) {
	m_autonomousCommand->Cancel();
    }
    m_driveBase->Stop();
    m_blinkyLight->Set(0.0);
}
	
void Robot::DisabledInit()
{
    printf("Robot::DisabledInit\n");
    Cancel();
}

void Robot::DisabledPeriodic()
{
    Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit()
{
    printf("Robot::AutonomousInit\n");
    Cancel();
    m_autonomousCommand->Start();
}
    
void Robot::AutonomousPeriodic()
{
    Scheduler::GetInstance()->Run();
}
    
void Robot::TeleopInit()
{
    printf("Robot::TeleopInit\n");
    Cancel();
}
    
void Robot::TeleopPeriodic()
{
    Scheduler::GetInstance()->Run();
}

void Robot::TestInit()
{
    printf("Robot::TestInit\n");
    Cancel();
}

void Robot::TestPeriodic()
{
    LiveWindow::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot);

