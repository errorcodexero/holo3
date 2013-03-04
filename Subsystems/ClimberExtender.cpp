#include "ClimberExtender.h"

const double ClimberExtender::kExtendTime = 1.2;

ClimberExtender::ClimberExtender( int extendChannel, int retractChannel )
    : Subsystem("ClimberExtender")
{
    m_pExtender = new DoubleSolenoid(extendChannel, retractChannel);
    LiveWindow::GetInstance()->AddActuator("Climber", "Extender", m_pExtender);
    m_position = kUnknown;
    m_startTime = 0.0;
    m_moving = false;
}

ClimberExtender::~ClimberExtender()
{
    delete m_pExtender;
}

void ClimberExtender::Set( ExtenderPosition position )
{
    switch (position) {
    case kExtended:
	m_pExtender->Set(DoubleSolenoid::kForward);
	break;
    case kRetracted:
	m_pExtender->Set(DoubleSolenoid::kReverse);
	break;
    default:
	m_pExtender->Set(DoubleSolenoid::kOff);
	break;
    }
    if (position != m_position) {
	m_startTime = Timer::GetFPGATimestamp();
	m_moving = true;
	m_position = position;
    }
}

ClimberExtender::ExtenderPosition ClimberExtender::Get()
{
    if (IsMoving())
	return kUnknown;
    else
	return m_position;
}

bool ClimberExtender::IsMoving()
{
    if (m_moving && ((Timer::GetFPGATimestamp() - m_startTime) >= kExtendTime))
    {
	m_moving = false;
    }
    return m_moving;
}
