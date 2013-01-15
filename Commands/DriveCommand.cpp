// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "DriveCommand.h"

// Identify resources required by this command.
// Other commands that are using these resources will be Canceled
// when this command is Started.
DriveCommand::DriveCommand()
{
	Requires(Robot::driveBase());
}

// Called just before this Command runs the first time
void DriveCommand::Initialize()
{
	;
}

// Called repeatedly when this Command is scheduled to run
void DriveCommand::Execute()
{
	Joystick *joy = Robot::oi()->getStick();
	Robot::driveBase()->Drive3(joy->GetX(), joy->GetY(), joy->GetTwist());
}

// Make this return true when this Command no longer needs to run execute()
bool DriveCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void DriveCommand::End()
{
	;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveCommand::Interrupted()
{
	;
}