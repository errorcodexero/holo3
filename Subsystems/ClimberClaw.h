#ifndef CLIMBER_CLAW_H
#define CLIMBER_CLAW_H

#include <WPILib.h>

class ClimberClaw : public Subsystem
{
public:
	ClimberClaw( int clawOpen, int clawClose );
	~ClimberClaw();

	typedef enum { kOpen, kClosed, kUnknown } ClawPosition;
	void Set(ClawPosition);
	ClawPosition Get();
	bool IsMoving();

private:
	DoubleSolenoid *m_pClaw;
	ClawPosition m_position;
	bool m_moving;
	double m_startTime;
	static const double kGrabTime;
};

#endif
