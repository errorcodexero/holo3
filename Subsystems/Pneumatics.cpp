// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Pneumatics.h"

Pneumatic::Pneumatic( Compressor* pneuControl, DoubleSolenoid* m_solenoid)
	: Subsystem("PneumaticControl"),
	  m_compressor(pneuControl),
	  m_doubleSolenoid(m_solenoid)
	
{
	
}
Pneumatic::~Pneumatic()
{
	
}
void Pneumatic::InitDefaultCommand()
{
	
}
void Pneumatic::Stop()
{
	
}
void Pneumatic::Start()
{
	
}
void Pneumatic::SolenoidActivate(DoubleSolenoid* m_solenoid)
{
	
}
