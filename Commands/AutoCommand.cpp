// FIRST Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include <WPILib.h>
#include "Robot.h"
#include "OI.h"
#include "BlinkyLight.h"
#include "Shooter.h"
#include "AutoCommand.h"
#include "BlinkyBreathe.h"
#include "TiltCommand.h"
#include "TargetCommand.h"
#include "ShootCommand.h"

AutoCommand::AutoCommand() :
    CommandGroup("AutoCommand")
{
    m_blinky = new BlinkyBreathe(3.0);
    m_tilt = new TiltCommand(Shooter::kLong);
    m_target = new TargetCommand();
    // default setting: shoot 3 disks for 3/6 points each from mid-field
    m_shoot = new ShootCommand(Shooter::kMid, 3, 3);

    AddParallel(m_blinky);
    AddSequential(m_tilt);
    //AddSequential(m_target);
    AddSequential(m_shoot);
}

AutoCommand::~AutoCommand()
{
    // this should remove command instances from scheduler,
    // then delete them.
}

void AutoCommand::Initialize()
{
    printf("AutoCommand::Initialize\n");

    m_shoot->SetDistance(Shooter::kMid);

    // TBD: We can do this based on the "AutoSelect" rotary switch or on
    // the gunner's target height selector.  Figure out which the drive
    // team prefers!

    // For now, use the AutoSelect.  When set to "2", shoot for the 2-point
    // goal, else for the 3-point goal.

    m_shoot->SetTarget( (Robot::oi()->GetAuto() == 2) ? 2 : 3 );
    m_shoot->SetNumDisks(3);
}

void AutoCommand::Execute()
{
}

bool AutoCommand::IsFinished()
{
    // this should return true when all commands are done
    return false;
}

void AutoCommand::End()
{
    printf("AutoCommand::End\n");
}

void AutoCommand::Interrupted()
{
    printf("AutoCommand::Interrupted\n");
    Robot::blinkyLight()->Set(0.0);
}

