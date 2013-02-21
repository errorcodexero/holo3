// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include <WPILib.h>
#include "TripleSolenoid.h"

TripleSolenoid::TripleSolenoid( int forwardChannel,
					      int reverseChannel,
					      int switchChannel )
    : DoubleSolenoid( forwardChannel, reverseChannel )
{
    m_switch = new DigitalInput( switchChannel );
    LiveWindow::GetInstance()->AddSensor("3PS", "SW", m_switch);
    m_goal = kUnknown;
    m_position = kUnknown;
    m_direction = DoubleSolenoid::kOff;
    m_notifier = NULL;
}

TripleSolenoid::~TripleSolenoid()
{
    Stop();
    delete m_notifier;
    delete m_switch;
}

TripleSolenoid::Position TripleSolenoid::GetPosition()
{
    return m_position;
}

void TripleSolenoid::SetPosition( Position position )
{
    m_goal = position;
    Start();
}

void TripleSolenoid::Start()
{
    if (m_notifier) {
	m_notifier->Stop();
    } else {
	m_notifier = new Notifier( TripleSolenoid::TimerEvent, this );
    }
    Run();
    m_notifier->StartPeriodic( 0.027 );
}

void TripleSolenoid::Stop()
{
    if (m_notifier) {
	m_notifier->Stop();
    }
    Set(DoubleSolenoid::kOff);
}

void TripleSolenoid::TimerEvent( void *param )
{
    ((TripleSolenoid*)param)->Run();
}

void TripleSolenoid::Run()
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
    SmartDashboard::PutNumber("3PS Direction", (double)m_direction);
    Set(m_direction);
}

