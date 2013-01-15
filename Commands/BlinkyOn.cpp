#include "Robot.h"
#include "BlinkyOn.h"

BlinkyOn::BlinkyOn()
{
    // Use Requires() here to declare subsystem dependencies
    // eg. Requires(chassis);
    Requires(Robot::blinkyLight);
}

// Called just before this Command runs the first time
void BlinkyOn::Initialize()
{
    Robot::blinkyLight->Set(1.0);
}

// Called repeatedly when this Command is scheduled to run
void BlinkyOn::Execute()
{
    ;
}

// Make this return true when this Command no longer needs to run execute()
bool BlinkyOn::IsFinished()
{
    return true;
}

// Called once after isFinished returns true
void BlinkyOn::End()
{
    ;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BlinkyOn::Interrupted()
{
    ;
}
