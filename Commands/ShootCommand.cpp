// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"

ShootCommand::ShootCommand()
{
    Requires(Robot::shooter());
}

void ShootCommand::Initialize()
{
    Robot::shooter()->Set(3000.0);
    Robot::shooter()->Start();
}

void ShootCommand::Execute()
{
    ;
}

bool ShootCommand::IsFinished()
{
    // return Robot::shooter()->IsUpToSpeed();
    return false;
}

void ShootCommand::End()
{
    ;
}

void ShootCommand::Interrupted()
{
    Robot::shooter()->Stop();
}
