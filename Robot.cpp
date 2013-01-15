// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"

DriveBase* Robot::driveBase = NULL;
OI* Robot::oi = NULL;

void Robot::RobotInit()
{
    RobotMap::init();
    driveBase = new DriveBase();

    // This MUST be here. If the OI creates Commands (which it very likely
    // will), constructing it during the construction of CommandBase (from
    // which commands extend) will refer to subsystems are not guaranteed
    // to be instantiated yet. Thus, their requires() statements may grab
    // null pointers. Bad news. Don't move it.
    oi = new OI();
    lw = LiveWindow::GetInstance();

    // Instantiate top-level commands
    autonomousCommand = new AutoCommand();
    teleopCommand = new TeleCommand();
}

void Robot::Cancel()
{
    if (autonomousCommand && autonomousCommand->IsRunning()) {
	autonomousCommand->Cancel();
    }
    if (teleopCommand && teleopCommand->IsRunning()) {
	teleopCommand->Cancel();
    }
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
    if (autonomousCommand) {
	autonomousCommand->Start();
	RobotMap::driveBaseDrive3->SetSafetyEnabled(true);
    }
}
    
void Robot::AutonomousPeriodic()
{
    Scheduler::GetInstance()->Run();
}
    
void Robot::TeleopInit()
{
    Cancel();
    if (teleopCommand) {
	teleopCommand->Start();
	RobotMap::driveBaseDrive3->SetSafetyEnabled(true);
    }
}
    
void Robot::TeleopPeriodic()
{
    Scheduler::GetInstance()->Run();
}

void Robot::TestInit()
{
    Cancel();
    RobotMap::driveBaseDrive3->SetSafetyEnabled(false);
}

void Robot::TestPeriodic() {
    lw->Run();
}

START_ROBOT_CLASS(Robot);

