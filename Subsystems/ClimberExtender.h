#ifndef CLIMBER_EXTENDER_H
#define CLIMBER_EXTENDER_H

#include <WPILib.h>

class ClimberExtender : public Subsystem
{
public:
	ClimberExtender( int extendChannel, int retractChannel );
	~ClimberExtender();

	typedef enum { kRetracted, kExtended, kUnknown } ExtenderPosition;
	void Set(ExtenderPosition);
	ExtenderPosition Get();
	bool IsMoving();

private:
	DoubleSolenoid *m_pExtender;
	ExtenderPosition m_position;
	bool m_moving;
	double m_startTime;
	static const double kExtendTime;
};

#endif
