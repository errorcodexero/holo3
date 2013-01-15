// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"

DriveBase::DriveBase() : Subsystem("DriveBase")
{
	right = RobotMap::driveBaseRight;
	front = RobotMap::driveBaseFront;
	left = RobotMap::driveBaseLeft;
	drive3 = RobotMap::driveBaseDrive3;
	// TBD: add a turn-rate gyro
}
    
void DriveBase::InitDefaultCommand()
{
	SetDefaultCommand(new DriveCommand());
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void DriveBase::Drive3( float x, float y, float twist )
{
	// TBD: add turn-rate gyro output as the fourth argument
	// to HolonomicDrive_Cartesian
	drive3->HolonomicDrive_Cartesian( x, y, twist );
}

