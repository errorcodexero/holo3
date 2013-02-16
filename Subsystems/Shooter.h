// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef SHOOTER_H
#define SHOOTER_H

#include <WPILib.h>

class Shooter : public Subsystem {
private:
    CANJaguar* p_shooterMotor;
    Notifier* p_notifier;
    double m_rampRate, m_P, m_I, m_D;
    double m_speed;
    // additional tuning parameters:
    // drive polling interval (must be faster than MotorSafety timeout)
    // status polling interval
    // motor "up to speed" threshold
    // motor "up to speed" time
    int m_report;
    int m_upToSpeed;

public:
    Shooter( CANJaguar* motor );
    ~Shooter();
    void Set(double speed);
    void Start(void);
    void Stop(void);
    bool IsUpToSpeed(void);
	
private:
    static void Shooter::TimerEvent( void *param );
    void Run(void);
    void ReportStatus(void);
};
#endif
