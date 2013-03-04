#include "ClimberHooks.h"

const double ClimberHooks::kHookSpeed = 0.995;

ClimberHooks::ClimberHooks( int leftMotor, int rightMotor,
			    int ltLim, int rtLim,
			    int lmLim, int rmLim,
			    int lbLim, int rbLim )
    : Subsystem("Climber")
{
    LiveWindow *lw = LiveWindow::GetInstance();

    m_pLeftMotor = new Victor( leftMotor );
    lw->AddActuator("Climber", "Left", m_pLeftMotor);

    m_pRightMotor = new Victor( rightMotor );
    lw->AddActuator("Climber", "Right", m_pRightMotor);

    m_pLTopLim = new DigitalInput( ltLim );
    lw->AddSensor("Climber", "LeftTopLimit", m_pLTopLim);

    m_pRTopLim = new DigitalInput( rtLim );
    lw->AddSensor("Climber", "RightTopLimit", m_pRTopLim);

    m_pLMidLim = new DigitalInput( lmLim );
    lw->AddSensor("Climber", "LeftMidLimit", m_pLMidLim);

    m_pRMidLim = new DigitalInput( rmLim );
    lw->AddSensor("Climber", "RightMidLimit", m_pRMidLim);

    m_pLBotLim = new DigitalInput( lbLim );
    lw->AddSensor("Climber", "LeftBotLimit", m_pLBotLim);

    m_pRBotLim = new DigitalInput( rbLim );
    lw->AddSensor("Climber", "RightBotLimit", m_pRBotLim);

    m_leftPosition = kUnknown;
    m_rightPosition = kUnknown;
    m_direction = kStop;
}

ClimberHooks::~ClimberHooks()
{
    delete m_pLeftMotor;
    delete m_pRightMotor;
    delete m_pLTopLim;
    delete m_pRTopLim;
    delete m_pLMidLim;
    delete m_pRMidLim;
    delete m_pLBotLim;
    delete m_pRBotLim;
}

void ClimberHooks::UpdatePosition()
{
    if (!m_pLBotLim->Get()) {
	m_leftPosition = kBottom;
    } else if (!m_pLTopLim->Get()) {
	m_leftPosition = kTop;
    } else if (!m_pLMidLim->Get()) {
	if (m_direction == kUp) {
	    m_leftPosition = kMidLow;
	} else if (m_direction == kDown) {
	    m_leftPosition = kMidHigh;
	}
    } else if (m_direction == kUp && m_leftPosition == kMidLow) {
	m_leftPosition = kMidHigh;
    } else if (m_direction == kDown && m_leftPosition == kMidHigh) {
	m_leftPosition = kMidLow;
    }

    if (!m_pRBotLim->Get()) {
	m_rightPosition = kBottom;
    } else if (!m_pRTopLim->Get()) {
	m_rightPosition = kTop;
    } else if (!m_pRMidLim->Get()) {
	if (m_direction == kUp) {
	    m_rightPosition = kMidLow;
	} else if (m_direction == kDown) {
	    m_rightPosition = kMidHigh;
	}
    } else if (m_direction == kUp && m_rightPosition == kMidLow) {
	m_rightPosition = kMidHigh;
    } else if (m_direction == kDown && m_rightPosition == kMidHigh) {
	m_rightPosition = kMidLow;
    }
}

bool ClimberHooks::Set( HookDirection direction, HookPosition stopAt )
{
    int left, right;

    // figure out where we are now based on last driving directions

    UpdatePosition();

    // set motor driving direction, deal with top/bottom limit switches

    m_direction = direction;
    switch (m_direction) {
    case kUp:
	// Set motor directions for upward motion.
	left = 1;
	right = 1;
	// If we're already at the top limit, stop.
	if (!m_pLTopLim->Get())
	    left = 0;
	if (!m_pRTopLim->Get())
	    right = 0;
	// If we're already at or above the desired position, stop.
	if ((m_leftPosition != kUnknown) && (m_leftPosition >= stopAt))
	    left = 0;
	if ((m_rightPosition != kUnknown) && (m_rightPosition >= stopAt))
	    right = 0;
	break;
    case kDown:
	// Set motor directions for downward motion.
	left = -1;
	right = -1;
	// If we're already at the bottom limit, stop.
	if (!m_pLBotLim->Get())
	    left = 0;
	if (!m_pRBotLim->Get())
	    right = 0;
	// If we're already at or below the desired position, stop.
	if ((m_leftPosition != kUnknown) && (m_leftPosition <= stopAt))
	    left = 0;
	if ((m_rightPosition != kUnknown) && (m_rightPosition <= stopAt))
	    right = 0;
	break;
    case kStop:
	left = 0;
	right = 0;
    }

    m_pLeftMotor->Set(left * kHookSpeed);
    m_pRightMotor->Set(right * kHookSpeed);

    // return true when both hooks are in position (not moving)
    return (left == 0) || (right == 0);
}

bool ClimberHooks::IsAtTop()
{
    return (m_leftPosition == kTop) && (m_rightPosition == kTop);
}

bool ClimberHooks::IsAtMidHigh()
{
    return (m_leftPosition == kMidHigh) && (m_rightPosition == kMidHigh);
}

bool ClimberHooks::IsAtMidLow()
{
    return (m_leftPosition == kMidLow) && (m_rightPosition == kMidLow);
}

bool ClimberHooks::IsAtBottom()
{
    return (m_leftPosition == kBottom) && (m_rightPosition == kBottom);
}

