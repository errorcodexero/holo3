// FIRST Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include <WPILib.h>
#include "Robot.h"
#include "BlinkyLight.h"
#include "Shooter.h"
#include "AutoCommand.h"
#include "BlinkyBreathe.h"
#include "TiltCommand.h"
#include "TargetCommand.h"
#include "ShootCommand.h"

AutoCommand::AutoCommand()
{
    m_blinky = new BlinkyBreathe(3.0);
    m_tilt = new TiltCommand(Shooter::kMid);
    m_target = new TargetCommand();
    m_shoot = new ShootCommand(Shooter::kMid, 3);

    AddParallel(m_blinky);
    AddSequential(m_tilt);
    //AddSequential(m_target);
    AddSequential(m_shoot);
}

void AutoCommand::Interrupted()
{
    Robot::blinkyLight()->Set(0.0);
}

