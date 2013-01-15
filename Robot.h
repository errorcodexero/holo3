// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef _ROBOT_H
#define _ROBOT_H

#include "WPILib.h"
#include "LiveWindow/LiveWindow.h"

#include "RobotMap.h"
#include "DriveBase.h"
#include "BlinkyLight.h"
#include "AutoCommand.h"
#include "TeleCommand.h"
#include "DriveCommand.h"
#include "BlinkyBreathe.h"
#include "BlinkyOff.h"
#include "BlinkyOn.h"

#include "OI.h"

class Robot : public IterativeRobot {
public:
	static OI *oi;
	static DriveBase* driveBase;
	static BlinkyLight* blinkyLight;
	LiveWindow *lw;
	Command *autonomousCommand;
	Command *teleopCommand;

	void Cancel();
	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestInit();
	virtual void TestPeriodic();
};

#endif
