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

    m_oi = new OI();

    ////////////////////////////////////////////////////////////////////
    //
    // Digital Inputs:
    // 1 - pneumatics pressure switch
    //     (polarity handled by Compressor class)
    //
    // 2 - climber left bottom limit switch
    // 3 - climber left top limit switch
    // 4 - climber right bottom limit switch
    // 5 - climber right top limit switch
    //     limit switches are normally-open switches to ground
    //     so normally true, switch to false = at limit
    //
    // 6 - shooter mid-range position
    //
    // Analog Inputs:
    // 1 - turn rate gyro
    //     + output is clockwise rotation
    //
    // Relay (Spike) Outputs:
    // 1 - compressor
    //
    // Solenoid Outputs:
    // 1,2 - climber tilt
    //     1 = extend
    //     2 = retract
    //
    // 3,4 - shooter position
    //     3 = extend (deploy)
    //     4 = retract
    //
    // 5 - shooter injector
    //     false = extend (idle)
    //     true = retract (inject)
    //
    // PWM Outputs:
    // 1 - blinky light (not used)
    // 4 - drive left
    // 5 - drive right
    // 6 - drive rear
    //
    // CAN (CANJaguar) channels:
    // 6 - shooter motor
    //
    ////////////////////////////////////////////////////////////////////

    //compressor
    m_compressor = new Compressor(1, 1);

    // DriveBase( leftMotorChannel, rightMotorChannel, rearMotorChannel,
    //		  gyroAnalogChannel );
    m_driveBase = new DriveBase( 4, 5, 6, 1 ),
    // printf("m_driveBase = %p\n", m_driveBase);

    // Shooter( motorChannel, solenoidChannel, switchChannel, injectorChannel );
    m_shooter = new Shooter( 6, 3, 6, 5);
    // printf("m_shooter = %p\n", m_shooter);
    
    m_blinkyLight = new BlinkyLight( 1 );
    // printf("m_blinkyLight = %p\n", m_blinkyLight);

    m_autonomousCommand = new AutoCommand();
    // printf("m_autonomousCommand = %p\n", m_autonomousCommand);

    m_teleopCommand = new TeleCommand();
    // printf("m_teleopCommand = %p\n", m_teleopCommand);

    m_shootCommand = new ShootCommand();
    // printf("m_shootCommand = %p\n", m_shootCommand);
    SmartDashboard::PutData("Shoot", m_shootCommand);

    // Now that everything else is set up, start the compressor
    m_compressor->Start();
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

