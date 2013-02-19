// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"

#define	SPEED_SHORT	1600	// shooting at tower from base of tower
#define	SPEED_MID	2800	// shooting at high goal from back of tower
#define	SPEED_LONG	3200	// shooting at high goal from feeder station

ShootCommand::ShootCommand( Shooter::TargetDistance targetDistance )
{
    Requires(Robot::shooter());
    m_targetDistance = targetDistance;
    m_launched = 0;
}

void ShootCommand::Initialize()
{
    Robot::shooter()->SetAngle(m_targetDistance);
    switch (m_targetDistance) {
    case Shooter::kShort:
	Robot::shooter()->SetSpeed(SPEED_SHORT);
	break;
    case Shooter::kMid:
	Robot::shooter()->SetSpeed(SPEED_MID);
	break;
    case Shooter::kLong:
	Robot::shooter()->SetSpeed(SPEED_LONG);
	break;
    default:
	break;
    }
    Robot::shooter()->Start();
    m_launched = 0;
}

void ShootCommand::Execute()
{
    if (Robot::shooter()->IsReadyToShoot()) {
	Robot::shooter()->Inject();
	m_launched++;
    }
}

int ShootCommand::GetLaunched()
{
    return m_launched;
}

bool ShootCommand::IsFinished()
{
    // keep running until canceled by caller
    return false;
}

void ShootCommand::End()
{
    Robot::shooter()->Stop();
}

void ShootCommand::Interrupted()
{
    Robot::shooter()->Stop();
}
