#ifndef CLIMBER_HOOKS_H
#define CLIMBER_HOOKS_H

#include <WPILib.h>

class ClimberHooks : public Subsystem
{
	
public:
    ClimberHooks( int leftMotor, int rightMotor, int ltLim, int rtLim,
		  int lmLim, int rmLim, int lbLim, int rbLim );
    ~ClimberHooks();

    typedef enum { kUp, kDown, kStop } HookDirection;
    typedef enum { kTop, kMidHigh, kMidLow, kBottom, kUnknown } HookPosition;

    // Set returns true when both motors are stopped
    bool Set( HookDirection direction, HookPosition stopAt = kUnknown );
    HookPosition Get();

    // These functions just return the values from the sensor inputs
    bool IsAtTop();
    bool IsAtMidHigh();
    bool IsAtMidLow();
    bool IsAtBottom();

private:
    Victor *m_pLeftMotor;
    Victor *m_pRightMotor;
    DigitalInput *m_pLTopLim;
    DigitalInput *m_pRTopLim;
    DigitalInput *m_pLMidLim;
    DigitalInput *m_pRMidLim;
    DigitalInput *m_pLBotLim;
    DigitalInput *m_pRBotLim;

    HookDirection m_direction;
    HookPosition m_leftPosition;
    HookPosition m_rightPosition;

    static const double kHookSpeed;

    void UpdatePosition();
};

#endif
