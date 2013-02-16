// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Shooter.h"
#include <math.h>

// Constructor
Shooter::Shooter(CANJaguar* motor):Subsystem("Shooter")
{			
    p_shooterMotor = motor;
    p_notifier = NULL;

    m_rampRate = 0.0; // 0.0 disables rate limiting
    SmartDashboard::PutNumber("Shooter RampRate", m_rampRate);

    m_P = 0.250;
    SmartDashboard::PutNumber("Shooter P", m_P);

    m_I = 0.010;
    SmartDashboard::PutNumber("Shooter I", m_P);

    m_D = 0.000;
    SmartDashboard::PutNumber("Shooter D", m_P);

    m_speed = 2800.0;
    SmartDashboard::PutNumber("Shooter Speed", m_speed);

    m_report = 0;
}

Shooter::~Shooter()
{
    Stop();
    delete p_notifier;
}

void Shooter::Set( double speed )
{
    m_speed = speed;
    SmartDashboard::PutNumber("Shooter Speed", m_speed);
}


void Shooter::Start()
{
    // If we were already running, shut down the periodic timer and motor, then reset.
    Stop();

    // Set control mode
    p_shooterMotor->ChangeControlMode( CANJaguar::kSpeed );

    // Set encoder as reference device for speed controller mode:
    p_shooterMotor->SetSpeedReference( CANJaguar::kSpeedRef_Encoder );

    // Set codes per revolution parameter:
    p_shooterMotor->ConfigEncoderCodesPerRev( 1 );

    // Set voltage ramp rate:
    m_rampRate = SmartDashboard::GetNumber("Shooter RampRate");
    p_shooterMotor->SetVoltageRampRate( m_rampRate );

    // Set Jaguar PID parameters:
    m_P = SmartDashboard::GetNumber("Shooter P");
    m_I = SmartDashboard::GetNumber("Shooter I");
    m_D = SmartDashboard::GetNumber("Shooter D");
    p_shooterMotor->SetPID( m_P, m_I, m_D );

    // Enable Jaguar control:
    p_shooterMotor->EnableControl();

    // Start run timer
    if (!p_notifier) {
	p_notifier = new Notifier( Shooter::TimerEvent, this );
    }
    m_report = 0;
    p_notifier->StartPeriodic(0.10);
}

void Shooter::Stop()
{
    // stop timer
    if (p_notifier) {
	p_notifier->Stop();
    }

    // stop motor
    p_shooterMotor->Set(0.0);

    // not running any more!
    m_upToSpeed = 0;
    SmartDashboard::PutNumber("Shooter UpToSpeed", (double) m_upToSpeed);
}

void Shooter::TimerEvent( void *param )
{
    ((Shooter *)param)->Run();
}

void Shooter::Run()
{
    m_speed = SmartDashboard::GetNumber("Shooter Speed");
    p_shooterMotor->Set(m_speed, 0);
    if (++m_report >= 5) {
	ReportStatus();
    }
}

void Shooter::ReportStatus()
{
    // UINT8 jagHWVersion = p_shooterMotor->GetHardwareVersion();
    // UINT32 jagFWVersion = p_shooterMotor->GetFirmwareVersion();
    // double jagTemp  = p_shooterMotor->GetTemperature();
    double jagOutV = p_shooterMotor->GetOutputVoltage();
    double jagSpeed = p_shooterMotor->GetSpeed(); 

    // Send values to SmartDashboard
    // SmartDashboard::PutNumber("Jaguar Hardware Version", double(jagHWVersion));
    // SmartDashboard::PutNumber("Jaguar Firmware Version", double(jagFWVersion));
    // SmartDashboard::PutNumber("Shooter Temp", jagTemp);
    SmartDashboard::PutNumber("Shooter Voltage", jagOutV);
    SmartDashboard::PutNumber("Shooter RPM", jagSpeed);

    double error = jagSpeed - m_speed;
    if (fabs(error) < m_speed * 0.10) {
	// 1000 is arbitrary, just to limit number of digits displayed on dashboard
	if (m_upToSpeed < 1000) m_upToSpeed++;
    } else {
	m_upToSpeed = 0;
    }
    SmartDashboard::PutNumber("Shooter UpToSpeed", (double) m_upToSpeed);
}

bool Shooter::IsUpToSpeed()
{
    return (m_upToSpeed > 3);
}

