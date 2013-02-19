// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Shooter.h"
#include <math.h>

const double Shooter::kPollInterval = 0.100;
const int Shooter::kReportInterval = 5;

// Constructor
Shooter::Shooter( int motorChannel, int positionerChannel, int switchChannel,
			int injectorChannel )
    : Subsystem("Shooter")
{
    m_motor = new CANJaguar( motorChannel );
    m_motor->SetSafetyEnabled(false);
    m_notifier = NULL;

    m_rampRate = 0.5; // 0.0 disables rate limiting
    SmartDashboard::PutNumber("Shooter RampRate", m_rampRate);

    m_P = 1.000;
    SmartDashboard::PutNumber("Shooter P", m_P);

    m_I = 0.003;
    SmartDashboard::PutNumber("Shooter I", m_I);

    m_D = 0.000;
    SmartDashboard::PutNumber("Shooter D", m_D);

    m_speed = 3200.0;
    SmartDashboard::PutNumber("Shooter Speed", m_speed);

    m_speedTolerance = 10.0;  // +/- 10% speed tolerance
    SmartDashboard::PutNumber("Shooter Tolerance (%)", m_speedTolerance);

    m_speedStable = 4; // 4 ticks = 2.0 seconds
    SmartDashboard::PutNumber("Shooter Stable Time (ticks)", m_speedStable);

    m_injectTime = 4; // 4 ticks = 2.0 seconds
    SmartDashboard::PutNumber("Shooter Injection Time (ticks)", m_injectTime);

    // Initialize pneumatics
    m_positioner = new ThreePositionSolenoid(
	    positionerChannel, positionerChannel+1, switchChannel
	);
    m_positionChooser = new SendableChooser();
    m_positionChooser->AddDefault("Unknown", (void *)kUnknown);
    m_positionChooser->AddObject("Home", (void *)kHome);
    m_positionChooser->AddObject("Short", (void *)kShort);
    m_positionChooser->AddObject("Long", (void *)kLong);
    SmartDashboard::PutData("Shooter Target", m_positionChooser);

    m_injector = new Solenoid( injectorChannel );
    SmartDashboard::PutBoolean("Shooter Injector", false);

    m_report = 0;
    m_timeAtSpeed = 0;
    m_injected = 0;
}

Shooter::~Shooter()
{
    Stop();
    delete m_notifier;
    // no "SmartDashboard::removeData" method
    // delete m_positionChooser;
    delete m_positioner;
    delete m_motor;
}

void Shooter::Set( double speed )
{
    m_speed = speed;
    SmartDashboard::PutNumber("Shooter Speed", m_speed);
}

void Shooter::Start()
{
    // If we were already running, shut down the periodic timer and motor,
    // then (re)configure the motor controller and start.
    Stop();

    // Set control mode
    m_motor->ChangeControlMode( CANJaguar::kSpeed );

    // Set encoder as reference device for speed controller mode:
    m_motor->SetSpeedReference( CANJaguar::kSpeedRef_Encoder );

    // Set codes per revolution parameter:
    m_motor->ConfigEncoderCodesPerRev( 1 );

    // Set voltage ramp rate:
    m_rampRate = SmartDashboard::GetNumber("Shooter RampRate");
    m_motor->SetVoltageRampRate( m_rampRate );

    // Set Jaguar PID parameters:
    m_P = SmartDashboard::GetNumber("Shooter P");
    m_I = SmartDashboard::GetNumber("Shooter I");
    m_D = SmartDashboard::GetNumber("Shooter D");
    m_motor->SetPID( m_P, m_I, m_D );

    // Enable Jaguar control:
    m_motor->EnableControl();

    // Poke the motor speed to reset the watchdog, then enable the watchdog
    m_speed = SmartDashboard::GetNumber("Shooter Speed");
    m_motor->Set(m_speed);

    m_motor->SetSafetyEnabled(true);

    // Start run timer
    if (!m_notifier) {
	m_notifier = new Notifier( Shooter::TimerEvent, this );
    }
    m_report = 0;
    m_notifier->StartPeriodic(kPollInterval);
}

void Shooter::Stop()
{
    // stop timer
    if (m_notifier) {
	m_notifier->Stop();
    }

    // stop motor
    m_motor->StopMotor();
    m_motor->SetSafetyEnabled(false);

    // stop positioner
    m_positioner->Stop();

    // reset injector
    m_injector->Set(false);

    // not running any more!
    m_timeAtSpeed = 0;
}

void Shooter::TimerEvent( void *param )
{
    ((Shooter *)param)->Run();
}

void Shooter::Run()
{
    ShooterPosition pos = (ShooterPosition)(int)m_positionChooser->GetSelected();
    SetPosition(pos);

    // bool inject = SmartDashboard::GetBoolean("Shooter Injector");
    // m_injector->Set(inject);

    if (m_injector->Get()) {
	m_injectTime = (int)SmartDashboard::GetNumber("Shooter Injection Time (ticks)");
	if (++m_injected >= m_injectTime) {
	    m_injector->Set(false);
	    SmartDashboard::PutBoolean("Shooter Injector", false);
	}
    } else if (m_injected) {
	m_injected--;
    }

    m_speed = SmartDashboard::GetNumber("Shooter Speed");
    m_motor->Set(m_speed, 0);
    if (++m_report >= kReportInterval) {
	ReportStatus();
    }
}

void Shooter::ReportStatus()
{
    ThreePositionSolenoid::Position pos = m_positioner->Get();
    SmartDashboard::PutNumber("Shooter Position", (double)pos);

    // UINT8 jagHWVersion = m_motor->GetHardwareVersion();
    // UINT32 jagFWVersion = m_motor->GetFirmwareVersion();
    // double jagTemp  = m_motor->GetTemperature();
    double jagOutV = m_motor->GetOutputVoltage();
    double jagSpeed = m_motor->GetSpeed(); 

    // Send values to SmartDashboard
    // SmartDashboard::PutNumber("Jaguar Hardware Version", double(jagHWVersion));
    // SmartDashboard::PutNumber("Jaguar Firmware Version", double(jagFWVersion));
    // SmartDashboard::PutNumber("Shooter Temp", jagTemp);
    SmartDashboard::PutNumber("Shooter Voltage", jagOutV);
    SmartDashboard::PutNumber("Shooter RPM", jagSpeed);

    double error = jagSpeed - m_speed;
    m_speedTolerance = SmartDashboard::GetNumber("Shooter Tolerance (%)");
    if (fabs(error) < m_speed * m_speedTolerance / 100.0) {
	// 1000 is arbitrary, just to limit number of digits displayed on dashboard
	if (m_timeAtSpeed < 1000) m_timeAtSpeed++;
    } else {
	m_timeAtSpeed = 0;
    }
}

bool Shooter::IsUpToSpeed()
{
    m_speedStable = (int) SmartDashboard::GetNumber("Shooter Stable Time (ticks)");
    bool isUpToSpeed = (m_timeAtSpeed >= m_speedStable);
    SmartDashboard::PutBoolean("Shooter UpToSpeed", isUpToSpeed);
    return isUpToSpeed;
}

/*
 * Move the shooter to the desired position
 */
void Shooter::SetPosition(ShooterPosition position)
{
    // map ShooterPosition to ThreePositionSolenoid::Position
    switch (position) {
    case kHome:
	m_positioner->Set(ThreePositionSolenoid::kRetracted);
	break;
    case kShort:
	m_positioner->Set(ThreePositionSolenoid::kCenter);
	break;
    case kLong:
	m_positioner->Set(ThreePositionSolenoid::kExtended);
	break;
    default:
	m_positioner->Stop();
	break;
    }
}

/*
 * Launch a disk
 */
void Shooter::Inject()
{
    m_injector->Set(true);
    SmartDashboard::PutBoolean("Shooter Injector", true);
}
