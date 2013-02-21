// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Shooter.h"
#include <math.h>

const double Shooter::kPollInterval = 0.100;
const double Shooter::kReportInterval = 0.500;

// Constructor
Shooter::Shooter( int motorChannel, int positionerChannel, int switchChannel,
			int injectorChannel )
    : Subsystem("Shooter")
{
    LiveWindow *lw = LiveWindow::GetInstance();

    m_motor = new CANJaguar( motorChannel );
    lw->AddActuator("Shooter", "Motor", m_motor);
    m_motor->SetSafetyEnabled(false);	// motor safety off while configuring

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

    m_speedStable = 2.0; // 4 ticks = 2.0 seconds
    SmartDashboard::PutNumber("Shooter Stable Time", m_speedStable);

    m_injectTime = 2.0; // 4 ticks = 2.0 seconds
    SmartDashboard::PutNumber("Shooter Injection Time", m_injectTime);

    // Initialize pneumatics
    m_positioner = new TripleSolenoid( positionerChannel,
				       positionerChannel+1,
				       switchChannel );
    lw->AddActuator("Shooter", "Positioner", m_positioner);
    lw->AddSensor("Shooter", "PositionCenter", m_positioner->m_switch);
    m_distance = kUnknown;
    SmartDashboard::PutBoolean("Shooter InPosition", false);

    m_injector = new Solenoid( injectorChannel );
    lw->AddActuator("Shooter", "Injector", m_injector);
    SmartDashboard::PutBoolean("Shooter Injector", false);

    m_notifier = new Notifier( Shooter::TimerEvent, this );

    m_report = 0;
    m_timeAtSpeed = 0;
    m_isUpToSpeed = false;
    SmartDashboard::PutBoolean("Shooter UpToSpeed", m_isUpToSpeed);

    m_injectCounter = 0;
}

Shooter::~Shooter()
{
printf("Shooter::~Shooter\n");
    Stop();
    delete m_notifier;
    delete m_positioner;
    delete m_motor;
}

/*
 * Move the shooter to the desired position
 */
void Shooter::SetAngle(TargetDistance target)
{
    m_distance = target;

    // map TargetDistance to TripleSolenoid::Position
    switch (m_distance) {
    case kShort:
	m_positioner->SetPosition(TripleSolenoid::kRetracted);
	SmartDashboard::PutString("Shooter Distance", "Short");
	break;
    case kMid:
	m_positioner->SetPosition(TripleSolenoid::kCenter);
	SmartDashboard::PutString("Shooter Distance", "Mid");
	break;
    case kLong:
	m_positioner->SetPosition(TripleSolenoid::kExtended);
	SmartDashboard::PutString("Shooter Distance", "Long");
	break;
    default:
	break;
    }
}

/*
 * Set the shooter wheel speed.
 * Start/stop the wheel.
 */
void Shooter::SetSpeed( double speed )
{
    m_speed = speed;
    SmartDashboard::PutNumber("Shooter Speed", m_speed);
}

void Shooter::Start()
{
printf("Shooter::Start\n");
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

    // Increase motor safety timer to match status reporting interval
    // Poke the motor speed to reset the watchdog, then enable the watchdog
    m_motor->SetExpiration(kPollInterval * kReportInterval);
    m_speed = SmartDashboard::GetNumber("Shooter Speed");
    m_motor->Set(m_speed);
#if 0
    m_motor->SetSafetyEnabled(true);
#endif

    // Start run timer
    m_report = 0;
    m_notifier->StartPeriodic(kPollInterval);
}

void Shooter::Stop()
{
printf("Shooter::Stop\n");
    // stop timer
    m_notifier->Stop();

    // stop motor
    m_motor->StopMotor();
    m_motor->SetSafetyEnabled(false);

    // stop positioner
    m_positioner->Stop();

    // reset injector
    m_injector->Set(false);

    // not running any more!
    m_timeAtSpeed = 0;
    m_isUpToSpeed = false;
    SmartDashboard::PutBoolean("Shooter UpToSpeed", m_isUpToSpeed);
}

void Shooter::TimerEvent( void *param )
{
    ((Shooter *)param)->Run();
}

void Shooter::Run()
{
    m_speed = SmartDashboard::GetNumber("Shooter Speed");
    m_motor->Set(m_speed, 0);
    if (++m_report * kPollInterval >= kReportInterval) {
	ReportStatus();
    }

    if (m_injector->Get()) {
	m_injectTime = (int)SmartDashboard::GetNumber("Shooter Injection Time");
	if (++m_injectCounter * kReportInterval >= m_injectTime) {
	    m_injector->Set(false);
	}
    } else if (m_injectCounter) {
	if (--m_injectCounter == 0) {
	    SmartDashboard::PutBoolean("Shooter Injector", false);
	}
    }
}

void Shooter::ReportStatus()
{
    char *pos = "";
    switch (m_positioner->GetPosition()) {
    case TripleSolenoid::kUnknown:
	pos = "unknown";
	break;
    case TripleSolenoid::kRetracted:
	pos = "retracted";
	break;
    case TripleSolenoid::kPartlyRetracted:
	pos = "partly retracted";
	break;
    case TripleSolenoid::kCenter:
	pos = "center";
	break;
    case TripleSolenoid::kPartlyExtended:
	pos = "partly extended";
	break;
    case TripleSolenoid::kExtended:
	pos = "extended";
	break;
    }
    SmartDashboard::PutString("Shooter Position", pos);

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
	// 1000 is arbitrary, just to limit number of digits
	//  displayed on the dashboard.
	if (m_timeAtSpeed < 1000) m_timeAtSpeed++;
	m_speedStable = (int) SmartDashboard::GetNumber("Shooter Stable Time");
	m_isUpToSpeed = (m_timeAtSpeed * kReportInterval >= m_speedStable);
    } else {
	m_timeAtSpeed = 0;
	m_isUpToSpeed = false;
    }
    SmartDashboard::PutBoolean("Shooter UpToSpeed", m_isUpToSpeed);
}

// check positioner at correct angle
bool Shooter::IsInPosition()
{
    TripleSolenoid::Position pos = m_positioner->GetPosition();
    bool inPosition;

    switch (m_distance) {
    case kUnknown:
	inPosition = true;
	break;
    case kShort:
	inPosition = (pos == TripleSolenoid::kRetracted);
	break;
    case kMid:
	inPosition = (pos == TripleSolenoid::kCenter);
	break;
    case kLong:
	inPosition = (pos == TripleSolenoid::kExtended);
	break;
    }
    SmartDashboard::PutBoolean("Shooter InPosition", inPosition);
    return inPosition;
}

bool Shooter::IsUpToSpeed()
{
    return m_isUpToSpeed;
}

bool Shooter::IsInjectorActive()
{
    bool active = (m_injectCounter != 0);
    SmartDashboard::PutBoolean("Shooter Active", active);
    return active;
}

bool Shooter::IsReadyToShoot()
{
    // we are ready when in position, wheel up to speed and injector idle
    bool ready = (IsInPosition() && IsUpToSpeed() && !IsInjectorActive());
    SmartDashboard::PutBoolean("Shooter Ready", ready);
    return ready;
}

/*
 * Launch a disk
 */
void Shooter::Inject()
{
    m_injector->Set(true);
    m_injectCounter++;
    SmartDashboard::PutBoolean("Shooter Injector", true);
}
