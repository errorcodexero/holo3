// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"
#include "RobotDrive3.h"

// The RobotMap is a mapping from the ports sensors and actuators are
// wired into to a variable name.  This provides flexibility for changing
// wiring, makes checking the wiring easier and significantly reduces
// the number of magic numbers floating around.

class RobotMap {
public:
	static Jaguar* driveBaseFront;
	static Jaguar* driveBaseLeft;
	static Jaguar* driveBaseRight;
	static RobotDrive3* driveBaseDrive3;

	static void init();
};
#endif
