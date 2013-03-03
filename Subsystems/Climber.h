#ifndef CLIMBER_H
#define CLIMBER_H
#include <WPILib.h>
#include "Robot.h"

class Climber : public Subsystem
{
private:
	Victor *m_pLeft;
	Victor *m_pRight;
	DigitalInput *m_pLTopLim;
	DigitalInput *m_pRTopLim;
	DigitalInput *m_pLMidLim;
	DigitalInput *m_pRMidLim;
	DigitalInput *m_pLBotLim;
	DigitalInput *m_pRBotLim;
	Solenoid *m_pExtender;
	Solenoid *m_pClaw;
	
public:
	Climber();
	~Climber();
	
};
#endif
