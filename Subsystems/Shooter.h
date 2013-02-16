// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef SHOOTER_H
#define SHOOTER_H

#include <WPILib.h>


class Shooter : public Subsystem {
public:
	
	// Class member data section:
	static const UINT8 syncGroup = 0; // create synchronization group in case of more motors.
	static const double autonomousSpeed = 2700.;
	static const UINT8 shooterMotorDeviceNumber = 6;
	static const CANJaguar::ControlMode shooterMotorControlMode = CANJaguar::kSpeed;

	CANJaguar* p_shooterMotor;
	
	Shooter( CANJaguar* motor );
	
	void Initialize();
	void Run(double wheelSpeed);
	void Stop();
private:
	void ReportStatus(void);
};
#endif
