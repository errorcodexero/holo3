// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef _ROBOT_H
#define _ROBOT_H

#include <WPILib.h>
#include "BlinkyLight.h"
#include "DriveBase.h"
#include "RateGyro.h"
#include "Shooter.h"
#include "TripleSolenoid.h"
#include "AimTrim.h"
#include "AutoCommand.h"
#include "BlinkyBreathe.h"
#include "BlinkyOff.h"
#include "BlinkyOn.h"
#include "DriveCommand.h"
#include "ResetRobot.h"
#include "Rotate.h"
#include "SelectTarget.h"
#include "ShootCommand.h"
#include "TargetCommand.h"
#include "TimedDrive.h"
#include "OI.h"
#include "TiltCommand.h"

class OI;

class Robot : public IterativeRobot {
private:
    // Robot is a singleton object, so the constructor is private.
    Robot();

    // Allow construction of the singleton by the WPILib framework.
    friend RobotBase* FRC_userClassFactory();

    // Robot shouldn't be destroyed since references to its member
    // commands and subsystems may still exist in the command scheduler.
    // We can't really remove the (virtual) destructor, but we can hide
    // it by making it private.
    ~Robot();

    // C++ requires that class members must be declared in
    // construction order.  Because of dependencies among these
    // objects, they must be declared and constructed:
    //   sensors and actuators first,
    //   then subsystems based on those sensors and actuators,
    //   then the OI,
    //   then any other commands

    // global sensors
    Compressor* m_compressor;

    // OI
    OI* m_oi;

    // subsystems
    DriveBase* m_driveBase;
    Shooter* m_shooter;
    BlinkyLight* m_blinkyLight;
    
public:
    // commands
    AutoCommand* m_autonomousCommand;

public:
    // singleton accessor
    static Robot& theRobot() { return (Robot&) RobotBase::getInstance(); };

    // convenience accessors
    static DriveBase* driveBase() { return theRobot().m_driveBase; };
    static BlinkyLight* blinkyLight() { return theRobot().m_blinkyLight; };
    static Shooter* shooter() { return theRobot().m_shooter; };
    static OI* oi() { return theRobot().m_oi; };

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
