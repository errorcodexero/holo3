// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include <WPILib.h>
#include "Robot.h"
#include "ClimberExtender.h"
#include "ClimberClaw.h"
#include "ClimberHooks.h"
#include "ClimbCommand.h"

ClimbCommand::ClimbCommand()
{
    Requires(Robot::extender());
    Requires(Robot::claw());
    Requires(Robot::climber());
}

