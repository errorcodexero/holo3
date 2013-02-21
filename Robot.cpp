// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"
#include "OI.h"


////////////////////////////////////////////////////////////////////
// Digital Inputs:
// 1 - pneumatics pressure switch
//     (polarity handled by Compressor class)

#define	DIGITAL_PRESSURE_SWITCH		1

// 2 - climber left bottom limit switch
// 3 - climber left top limit switch
// 4 - climber right bottom limit switch
// 5 - climber right top limit switch
//     limit switches are normally-open switches to ground
//     so normally true, switch to false = at limit

#define DIGITAL_LIMIT_LEFT_BOTTOM	2
#define DIGITAL_LIMIT_LEFT_TOP		3
#define DIGITAL_LIMIT_RIGHT_BOTTOM	4
#define DIGITAL_LIMIT_RIGHT_TOP		5

// 6 - shooter mid-range position

#define DIGITAL_SHOOTER_CENTER		6

////////////////////////////////////////////////////////////////////
// Analog Inputs:
// 1 - turn rate gyro
//     + output is clockwise rotation

#define ANALOG_GYRO			1

////////////////////////////////////////////////////////////////////
// Relay (Spike) Outputs:
// 1 - compressor

#define	RELAY_COMPRESSOR		1

////////////////////////////////////////////////////////////////////
// Solenoid Outputs:
// 1,2 - climber tilt
//     1 = extend
//     2 = retract
//

#define	SOLENOID_CLIMBER_EXTEND		1
#define	SOLENOID_CLIMBER_RETRACT	2

// 3,4 - shooter position
//     3 = extend (deploy for long range)
//     4 = retract (for shooting at tower goal)

#define SOLENOID_SHOOTER_EXTEND		3
#define SOLENOID_SHOOTER_RETRACT	4

// 5 - shooter injector
//     false = retract (idle)
//     true  = extend (to let a disk drop into firing position)

#define SOLENOID_SHOOTER_INJECT		5

////////////////////////////////////////////////////////////////////
// PWM Outputs:
// 1 - blinky light (not used)

#define PWM_BLINKY			1

// (PWM 2-3 not used)

// 4 - drive left
// 5 - drive right
// 6 - drive rear

#define PWM_DRIVE_LEFT			4
#define PWM_DRIVE_RIGHT			5
#define PWM_DRIVE_REAR			6

// CAN (CANJaguar) channels:
// 6 - shooter motor

#define CAN_SHOOTER			6

////////////////////////////////////////////////////////////////////


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

    m_teleopCommand = new TeleCommand();

    m_shootShort = new ShootCommand( Shooter::kShort );
    SmartDashboard::PutData("Shoot Short", m_shootShort);

    m_shootMid = new ShootCommand( Shooter::kMid );
    SmartDashboard::PutData("Shoot Mid", m_shootMid);

    m_shootLong = new ShootCommand( Shooter::kLong );
    SmartDashboard::PutData("Shoot Long", m_shootLong);

    // link operator controls to commands
    m_oi->Initialize();

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
    LiveWindow::GetInstance()->SetEnabled(true);
}

void Robot::TestPeriodic()
{
    LiveWindow::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot);

