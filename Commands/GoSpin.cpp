// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"
GoSpin::GoSpin()
{
    Requires(Robot::shooter());
}

void GoSpin::Initialize()
{
    Robot::shooter()->Initialize();
    
}

void GoSpin::Execute()
{
	Robot::shooter()->Run(2700.0);
}

bool GoSpin::IsFinished()
{
    return false;
}

void GoSpin::End()
{
    Robot::shooter()->Stop();
}

void GoSpin::Interrupted()
{
    Robot::shooter()->Stop();
}
