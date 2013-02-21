// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include <WPILib.h>
#include "DoubleSolenoid.h"
#include "TripleSolenoid.h"

// 47mS update period chosen to avoid collisions
// with other scheduled tasks
const double TripleSolenoid::kPollInterval = 0.047;

// end-to-end travel time
const double TripleSolenoid::kTravelTime = 4.00;

TripleSolenoid::TripleSolenoid( int forwardChannel,
			        int reverseChannel,
			        int switchChannel )
    : BugfixDoubleSolenoid( forwardChannel, reverseChannel )
{
//  printf("TripleSolenoid::TripleSolenoid\n");
    m_switch = new DigitalInput( switchChannel );
    m_notifier = new Notifier( TripleSolenoid::TimerEvent, this );
    m_goal = kUnknown;
    m_position = kUnknown;
    m_direction = BugfixDoubleSolenoid::kOff;
}

TripleSolenoid::~TripleSolenoid()
{
//  printf("TripleSolenoid::~TripleSolenoid\n");
    Stop();
    delete m_notifier;
    delete m_switch;
}

TripleSolenoid::Position TripleSolenoid::GetPosition()
{
//  printf("TripleSolenoid::GetPosition = %d\n", (int)m_position);
    return m_position;
}

void TripleSolenoid::SetPosition( Position position )
{
    printf("TripleSolenoid::SetPosition %d\n", (int)position);
    m_notifier->Stop();
    m_goal = position;
    Start();
}

void TripleSolenoid::Start()
{
    printf("TripleSolenoid::Start\n");
    m_howLong = 0;
    if (Move()) {
        printf("TripleSolenoid::Start is moving\n");
	m_notifier->StartPeriodic( kPollInterval );
    }
}

void TripleSolenoid::Stop()
{
    printf("TripleSolenoid::Stop\n");
    m_notifier->Stop();
    Set(BugfixDoubleSolenoid::kOff);
}

void TripleSolenoid::TimerEvent( void *param )
{
//  printf("TripleSolenoid::TimerEvent\n");
    ((TripleSolenoid*)param)->Run();
}

void TripleSolenoid::Run()
{
//  printf("TripleSolenoid::Run\n");
    m_howLong++;
    SmartDashboard::PutNumber("position time", (double)m_howLong);
    Update();
    if (!Move()) {
        printf("TripleSolenoid::Run done!\n");
	Stop();
    }
}

// update current position
void TripleSolenoid::Update()
{
    bool sw = ! m_switch->Get();
    SmartDashboard::PutBoolean("position center", sw);
    if (sw) {
	m_position = kCenter;
    } else if (m_direction == BugfixDoubleSolenoid::kForward) {
	if (m_position == kRetracted)
	    m_position = kPartlyRetracted;
	else if (m_position == kCenter)
	    m_position = kPartlyExtended;
	// use timer instead of limit switch to detect
	// PartlyExtended => Extended
	else if (m_howLong * kPollInterval >= kTravelTime)
	    m_position = kExtended;
    } else if (m_direction == BugfixDoubleSolenoid::kReverse) {
	if (m_position == kExtended)
	    m_position = kPartlyExtended;
	else if (m_position == kCenter)
	    m_position = kPartlyRetracted;
	// use timer instead of limit switch to detect
	// PartlyRetracted => Retracted
	else if (m_howLong * kPollInterval >= kTravelTime)
	    m_position = kRetracted;
    }
//  printf("TripleSolenoid::Update sw=%d pos=%d\n", (int)sw, (int)m_position);
}

// determine how to move toward goal
bool TripleSolenoid::Move()
{
    if (m_position == m_goal || m_goal == kUnknown) {
//      printf("TripleSolenoid::Move stopping\n");
	return false;
    }

    switch (m_goal) {
    case kRetracted:
	m_direction = BugfixDoubleSolenoid::kReverse;
	break;
    case kPartlyRetracted:
	if (m_position == kRetracted)
	    m_direction = BugfixDoubleSolenoid::kForward;
	else
	    m_direction = BugfixDoubleSolenoid::kReverse;
	break;
    case kCenter:
	if (m_position == kRetracted || m_position == kPartlyRetracted)
	    m_direction = BugfixDoubleSolenoid::kForward;
	else
	    m_direction = BugfixDoubleSolenoid::kReverse;
	break;
    case kPartlyExtended:
	if (m_position == kExtended)
	    m_direction = BugfixDoubleSolenoid::kReverse;
	else
	    m_direction = BugfixDoubleSolenoid::kForward;
	break;
    case kExtended:
	m_direction = BugfixDoubleSolenoid::kForward;
	break;
    default: // can't happen
	m_direction = BugfixDoubleSolenoid::kOff;
	break;
    }
    SmartDashboard::PutNumber("position direction", (double)m_direction);
//  printf("TripleSolenoid::Move dir %d\n", (int)m_direction);
    Set(m_direction);
    return true;
}


