// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef DRIVEBASE_H
#define DRIVEBASE_H

#include "Robot.h"
#include "RobotDrive3.h"

// robot drive base with three-wheeled holonomic drive

class DriveBase : public Subsystem {
private:
	SpeedController* m_front;
	SpeedController* m_left;
	SpeedController* m_right;
	// TBD: add a turn-rate gyro as part of the drive base,
	// with output incorporated into the Drive3 directive.
	RobotDrive3* m_drive3;
	bool m_started;

public:
	DriveBase( SpeedController* front,
		   SpeedController* left,
		   SpeedController* right );

	~DriveBase();

	void InitDefaultCommand();

	void Stop();
	void Start();
	void Drive3( float x, float y, float twist );
};

#endif
