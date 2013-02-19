// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include <WPILib.h>
#include "ThreePositionSolenoid.h"

ThreePositionSolenoid::ThreePositionSolenoid(
	int forwardChannel, int reverseChannel, int switchChannel
    )
{
    m_solenoid = new DoubleSolenoid( forwardChannel, reverseChannel );
    m_switch = new DigitalInput( switchChannel );
    m_goal = kUnknown;
    m_position = kUnknown;
    m_direction = DoubleSolenoid::kOff;
    m_notifier = NULL;
}

ThreePositionSolenoid::~ThreePositionSolenoid()
{
    Stop();
    delete m_notifier;
    delete m_switch;
    delete m_solenoid;
}

ThreePositionSolenoid::Position ThreePositionSolenoid::Get()
{
    return m_position;
}

void ThreePositionSolenoid::Set( Position position )
{
    m_goal = position;
    Start();
}

void ThreePositionSolenoid::Start()
{
    if (m_notifier) {
	m_notifier->Stop();
    } else {
	m_notifier = new Notifier( ThreePositionSolenoid::TimerEvent, this );
    }
    Run();
    m_notifier->StartPeriodic( 0.027 );
}

void ThreePositionSolenoid::Stop()
{
    if (m_notifier) {
	m_notifier->Stop();
    }
    m_solenoid->Set(DoubleSolenoid::kOff);
}

void ThreePositionSolenoid::TimerEvent( void *param )
{
    ((ThreePositionSolenoid*)param)->Run();
}

void ThreePositionSolenoid::Run()
{
    // update current position
    if (!m_switch->Get()) {
	m_position = kCenter;
    } else if (m_direction == DoubleSolenoid::kForward) {
	if (m_position == kRetracted)
	    m_position = kPartlyRetracted;
	else if (m_position == kCenter)
	    m_position = kPartlyExtended;
	// else: no limit switch to detect PartlyExtended => Extended
    } else if (m_direction == DoubleSolenoid::kReverse) {
	if (m_position == kExtended)
	    m_position = kPartlyExtended;
	else if (m_position == kCenter)
	    m_position = kPartlyRetracted;
	// else: no limit switch to detect PartlyRetracted => Retracted
    }

    // figure out how to move toward goal
    if (m_position == m_goal) {
	m_direction = DoubleSolenoid::kOff;
    } else {
	switch (m_goal) {
	case kUnknown:
	    m_direction = DoubleSolenoid::kOff;
	    break;
	case kRetracted:
	case kPartlyRetracted:
	    m_direction = DoubleSolenoid::kReverse;
	    break;
	case kCenter:
	    if (m_position == kRetracted || m_position == kPartlyRetracted)
		m_direction = DoubleSolenoid::kForward;
	    else if (m_position == kExtended || m_position == kPartlyExtended)
		m_direction = DoubleSolenoid::kReverse;
	    else // m_position == kUnknown, don't know what to do!
		m_direction = DoubleSolenoid::kOff;
	    break;
	case kPartlyExtended:
	case kExtended:
	    m_direction = DoubleSolenoid::kForward;
	    break;
	}
    }
    m_solenoid->Set(m_direction);
}
