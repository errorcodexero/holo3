// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"

BlinkyOff::BlinkyOff()
{
    // Use Requires() here to declare subsystem dependencies
    // eg. Requires(chassis);
    Requires(Robot::blinkyLight());
}

// Called just before this Command runs the first time
void BlinkyOff::Initialize()
{
    printf("Robot: Turn blinky light off NOW!\n");
    Robot::blinkyLight()->Set(0.0);
}

// Called repeatedly when this Command is scheduled to run
void BlinkyOff::Execute()
{
    ;
}

// Make this return true when this Command no longer needs to run execute()
bool BlinkyOff::IsFinished()
{
    return true;
}

// Called once after isFinished returns true
void BlinkyOff::End()
{
    ;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BlinkyOff::Interrupted()
{
    ;
}
