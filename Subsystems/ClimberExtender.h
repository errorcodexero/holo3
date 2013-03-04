#ifndef CLIMBER_EXTENDER_H
#define CLIMBER_EXTENDER_H

#include <WPILib.h>

class ClimberExtender : public Subsystem
{
private:
	DoubleSolenoid *m_pExtender;
	
public:
	ClimberExtender( int extendChannel, int retractChannel );
	~ClimberExtender();

	typedef enum { kRetracted, kExtended } ExtenderPosition;
	void Set(ExtenderPosition);
};

#endif
