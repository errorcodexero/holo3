#ifndef CLIMBER_HOOKS_H
#define CLIMBER_HOOKS_H

#include <WPILib.h>

class ClimberHooks : public Subsystem
{
private:
	Victor *m_pLeftMotor;
	Victor *m_pRightMotor;
	DigitalInput *m_pLTopLim;
	DigitalInput *m_pRTopLim;
	DigitalInput *m_pLMidLim;
	DigitalInput *m_pRMidLim;
	DigitalInput *m_pLBotLim;
	DigitalInput *m_pRBotLim;
	static const double kHookSpeed;
	
public:
	ClimberHooks( int leftMotor, int rightMotor, int ltLim, int rtLim,
	              int lmLim, int rmLim, int lbLim, int rbLim );
	~ClimberHooks();

	typedef enum { kUp, kUpHalf, kDownHalf, kDown, kStop } HookDirection;
	bool Set( HookDirection direction );
	bool IsAtTop();
	bool IsAtMiddle();
	bool IsAtBottom();
};

#endif
