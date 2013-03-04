#include "ClimberClaw.h"

const double ClimberClaw::kGrabTime = 1.2;

ClimberClaw::ClimberClaw( int clawOpen, int clawClose )
    : Subsystem("ClimberClaw")
{
    m_pClaw = new DoubleSolenoid(clawOpen, clawClose);
    LiveWindow::GetInstance()->AddActuator("Climber", "Claw", m_pClaw);
    m_position = kUnknown;
    m_startTime = 0.0;
    m_moving = false;
}

ClimberClaw::~ClimberClaw()
{
    delete m_pClaw;
}

void ClimberClaw::Set( ClawPosition position )
{
    switch (position) {
    case kOpen:
	m_pClaw->Set(DoubleSolenoid::kForward);
	break;
    case kClosed:
	m_pClaw->Set(DoubleSolenoid::kReverse);
	break;
    default:
	m_pClaw->Set(DoubleSolenoid::kOff);
	break;
    }
    if (position != m_position) {
	m_startTime = Timer::GetFPGATimestamp();
	m_moving = true;
	m_position = position;
    }
}

ClimberClaw::ClawPosition ClimberClaw::Get()
{
    if (IsMoving())
	return kUnknown;
    else
	return m_position;
}

bool ClimberClaw::IsMoving()
{
    if (m_moving && ((Timer::GetFPGATimestamp() - m_startTime) >= kGrabTime))
    {
	m_moving = false;
    }
    return m_moving;
}
