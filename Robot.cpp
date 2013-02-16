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
}

void Robot::RobotInit()
{
    printf("Robot::RobotInit()\n");

    // connect sensors and actuators to LiveWindow
    LiveWindow* lw = LiveWindow::GetInstance();

    m_driveBaseLeft = new Talon(1, 4);
    lw->AddActuator("DriveBase", "Left", m_driveBaseLeft);

    m_driveBaseRight  = new Talon(1, 5);
    lw->AddActuator("DriveBase", "Right",  m_driveBaseRight);

    m_driveBaseRear = new Talon(1, 6);
    lw->AddActuator("DriveBase", "Rear", m_driveBaseRear);

    m_gyro = new RateGyro(1, 1);
    lw->AddSensor("DriveBase", "Gyro", m_gyro);

    m_shooterMotor = new CANJaguar(6);
    
    m_blinkyPWM = new Victor(1, 1);
    // blinky lights don't need watchdogs
    m_blinkyPWM->SetSafetyEnabled(false);
    lw->AddActuator("BlinkyLight", "PWM", m_blinkyPWM);

    // m_unused = new Victor(1, 2);

    // Our drive base is rotated 180 degrees from the way the
    // DriveBase and RobotDrive3 (and RobotDrive) class expect,
    // so the motor channels have different names than the class
    // prototype.
    m_driveBase = new DriveBase( m_driveBaseRear, m_driveBaseRight,
				 m_driveBaseLeft, m_gyro ),

    m_shooter = new Shooter( m_shooterMotor );
    
    m_blinkyLight = new BlinkyLight( m_blinkyPWM );

    m_oi = new OI();

    m_autonomousCommand = new AutoCommand();

    m_teleopCommand = new TeleCommand();

    m_targetCommand = new TargetCommand();
    SmartDashboard::PutData("makeItSo", m_targetCommand);
    
    m_nudgeLeft = new TimedDrive( 0.0, 0.0, -.35, 0.15 );
    SmartDashboard::PutData("Lean to da Left!", m_nudgeLeft);
    
    m_nudgeRight = new TimedDrive( 0.0, 0.0, .35, 0.15);

    SmartDashboard::PutData("Lean to da Right Ya!", m_nudgeRight);

    m_shootCommand = new ShootCommand();
    SmartDashboard::PutData("Shoot", m_shootCommand);
    
    //compressor
    m_compressor = new Compressor(1, 2);  //TODO: Need actual channel values
    
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

