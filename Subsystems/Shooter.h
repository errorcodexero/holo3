// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef SHOOTER_H
#define SHOOTER_H

#include <WPILib.h>
#include "ThreePositionSolenoid.h"

class Shooter : public Subsystem {
private:
    CANJaguar* m_motor;
    double m_rampRate, m_P, m_I, m_D;
    double m_speed;
    double m_speedTolerance;
    int m_speedStable;
    int m_report;
    int m_timeAtSpeed;
    int m_injectTime;
    int m_injected;
    
    ThreePositionSolenoid *m_positioner;
    SendableChooser *m_positionChooser;
    Solenoid *m_injector;

    Notifier* m_notifier;

    static const double kPollInterval;	// not changeable at runtime
    static const int kReportInterval;

public:
    Shooter( int motorChannel, int positionerChannel, int switchChannel,
    		int injectorChannel );
    ~Shooter();
    void Set(double speed);
    void Start(void);
    void Stop(void);
    bool IsUpToSpeed(void);

    enum ShooterPosition {
	kUnknown,
	kHome,
	kShort,
	kLong,
    };

    void SetPosition(ShooterPosition);
    ShooterPosition GetPosition(ShooterPosition);

    void Inject();
	
private:
    static void TimerEvent( void *param );
    void Run(void);
    void ReportStatus(void);
};

#endif
