// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef SHOOTER_H
#define SHOOTER_H

#include <WPILib.h>

class Shooter : public Subsystem {
private:
    CANJaguar* m_motor;
    Notifier* m_notifier;
    double m_rampRate, m_P, m_I, m_D;
    double m_speed;
    double m_speedTolerance;
    int m_speedStable;
    int m_report;
    int m_upToSpeed;
    bool m_deployed;
    
    static const double kPollInterval;	// not changeable at runtime
    static const int kReportInterval;

    Solenoid *m_positioner;

public:
    Shooter( int motorChannel, int solenoidChannel );
    ~Shooter();
    void Set(double speed);
    void Start(void);
    void Stop(void);
    bool IsUpToSpeed(void);
    void SetPosition(bool);
	
private:
    static void Shooter::TimerEvent( void *param );
    void Run(void);
    void ReportStatus(void);
};
#endif
