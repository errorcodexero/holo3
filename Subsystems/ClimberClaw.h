#ifndef CLIMBER_CLAW_H
#define CLIMBER_CLAW_H

#include <WPILib.h>

class ClimberClaw : public Subsystem
{
private:
	DoubleSolenoid *m_pClaw;
	
public:
	ClimberClaw( int clawOpen, int clawClose );
	~ClimberClaw();

	typedef enum { kOpen, kClosed } ClawPosition;
	void Set(ClawPosition);
};

#endif
