// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"

Shoot::Shoot()
{
    Requires(Robot::shooter());
}

void Shoot::Initialize()
{
    Robot::shooter()->Set(3000.0);
    Robot::shooter()->Start();
}

void Shoot::Execute()
{
    ;
}

bool Shoot::IsFinished()
{
    // return Robot::shooter()->IsUpToSpeed();
    return false;
}

void Shoot::End()
{
    ;
}

void Shoot::Interrupted()
{
    Robot::shooter()->Stop();
}
