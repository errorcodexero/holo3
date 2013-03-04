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

bool ClimberHooks::Set( HookDirection direction )
{
    int left, right;
    switch (direction) {
    case kUp:
	left = m_pLTopLim->Get() ? 1 : 0;
	right = m_pRTopLim->Get() ? 1 : 0;
	break;
    case kUpHalf:
	left = (m_pLTopLim->Get() && m_pLMidLim->Get()) ? 1 : 0;
	right = (m_pRTopLim->Get() && m_pRMidLim->Get()) ? 1 : 0;
	break;
    case kDownHalf:
	left = (m_pLBotLim->Get() && m_pLMidLim->Get()) ? -1 : 0;
	right = (m_pRBotLim->Get() && m_pRMidLim->Get()) ? -1 : 0;
	break;
    case kDown:
	left = m_pLBotLim->Get() ? -1 : 0;
	right = m_pRBotLim->Get() ? -1 : 0;
	break;
    case kStop:
	left = right = 0;
	break;
    }
    m_pLeftMotor->Set(left * kHookSpeed);
    m_pRightMotor->Set(right * kHookSpeed);
    // return true when both hooks are in position (not moving)
    return (left == 0) || (right == 0);
}

bool ClimberHooks::IsAtTop()
{
    return !m_pLTopLim->Get() && !m_pRTopLim->Get();
}

bool ClimberHooks::IsAtMiddle()
{
    return !m_pLMidLim->Get() && !m_pRMidLim->Get();
}

bool ClimberHooks::IsAtBottom()
{
    return !m_pLBotLim->Get() && !m_pRBotLim->Get();
}

