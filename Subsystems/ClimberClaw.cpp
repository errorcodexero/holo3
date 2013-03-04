#include "ClimberClaw.h"

ClimberClaw::ClimberClaw( int clawOpen, int clawClose )
    : Subsystem("ClimberClaw")
{
    m_pClaw = new DoubleSolenoid(clawOpen, clawClose);
    LiveWindow::GetInstance()->AddActuator("Climber", "Claw", m_pClaw);
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
    }
}
