#ifndef BLINKY_LIGHT_H
#define BLINKY_LIGHT_H

#include <WPILib.h>

class BlinkyLight: public Subsystem
{
private:
    SpeedController* m_pwm;

public:
    BlinkyLight( SpeedController* pwm );
    void InitDefaultCommand();
    void Set( float value );
};

#endif
