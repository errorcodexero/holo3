#include "ClimberExtender.h"

ClimberExtender::ClimberExtender( int extendChannel, int retractChannel )
    : Subsystem("ClimberExtender")
{
    m_pExtender = new DoubleSolenoid(extendChannel, retractChannel);
    LiveWindow::GetInstance()->AddActuator("Climber", "Extender", m_pExtender);
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
    }
}
