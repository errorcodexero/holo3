// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef PNEUMATICS_H
#define PNEUMATICS_H

#include "WPILib.h"
#include "Compressor.h"
#include "DoubleSolenoid.h"

// Full Pneumatics System

class Pneumatic : public Subsystem {
private:
	Compressor* m_compressor;
	DoubleSolenoid* m_doubleSolenoid;
	
public:
	Pneumatic(Compressor* pneuControl, DoubleSolenoid* m_solenoid);

	~Pneumatic();

	void InitDefaultCommand();

	void Stop();
	void Start();
	void SolenoidActivate(DoubleSolenoid* m_solenoid_01);
};

#endif

