// FIRST Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

class Robot;

#ifndef _ROBOT_H
#define _ROBOT_H

#include <WPILib.h>

// Sensors & Actuators
class RateGyro;

// Subsystems
class BlinkyLight;
class DriveBase;

// Commands
class AutoCommand;

// Operator Interface
class OI;

////////////////////////////////////////////////////////////////////
// Analog Inputs:
// 1 - turn rate gyro
//     + output is clockwise rotation

#define ANALOG_GYRO			1

// 2-7 - not used

// 8 - battery (from analog bumper)

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

// 7,8 - not used

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

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
    BlinkyLight* m_blinkyLight;
    
public:
    // commands
    AutoCommand* m_autonomousCommand;

public:
    // singleton accessor
    static Robot& theRobot() { return (Robot&) RobotBase::getInstance(); };

    // convenience accessors
    static DriveBase* driveBase() { return theRobot().m_driveBase; printf("%s (%s:%d) %p\n", __FUNCTION__, __FILE__, __LINE__, theRobot().m_driveBase); };
    static BlinkyLight* blinkyLight() { return theRobot().m_blinkyLight; };
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
