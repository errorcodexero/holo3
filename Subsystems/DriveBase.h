// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef DRIVEBASE_H
#define DRIVEBASE_H

#include "Robot.h"
#include "RobotDrive3.h"

// robot drive base with three-wheeled holonomic drive

class DriveBase: public Subsystem {
private:
	SpeedController* right;
	SpeedController* front;
	SpeedController* left;
	// TBD: add a turn-rate gyro as part of the drive base,
	// with output incorporated into the Drive3 directive.
	RobotDrive3* drive3;

public:
	DriveBase();
	void InitDefaultCommand();
	void Drive3( float x, float y, float twist );
};

#endif
