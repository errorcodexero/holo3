#include "Robot.h"
#include "BlinkyLight.h"

BlinkyLight::BlinkyLight( SpeedController* pwm )
    : Subsystem("BlinkyLight"),
    m_pwm(pwm)
{
    m_pwm->Set(0.0);
}
    
void BlinkyLight::InitDefaultCommand()
{
    // SetDefaultCommand(new BlinkyOff());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void BlinkyLight::Set( float value )
{
    m_pwm->Set(value);
}

