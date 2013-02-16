// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Shooter.h"

// Constructor:
Shooter::Shooter(CANJaguar* motor):Subsystem("Shooter")
{			
	p_shooterMotor = motor;
}	

void Shooter::Initialize()
{
	// Set control mode
	p_shooterMotor->ChangeControlMode(CANJaguar::kSpeed);

	// Set voltage ramp rate:
	double rampRate = 0.0; // 0.0 disables rate limiting
	p_shooterMotor->SetVoltageRampRate(rampRate);

	// Set encoder as reference device for speed controller mode:
	CANJaguar::SpeedReference reference = CANJaguar::kSpeedRef_Encoder;
	p_shooterMotor->SetSpeedReference(reference);

	// Set codes per revolution parameter:
	UINT16 codesPerRev = 1;
	p_shooterMotor->ConfigEncoderCodesPerRev(codesPerRev);

	// Set Jaguar PID parameters:
	double Kp = 0.250;
	double Ki = 0.010;
	double Kd = 0.000;
	p_shooterMotor->SetPID(Kp, Ki, Kd);

	// Enable Jaguar control:
	double encoderInitialPosition = 0.0;
	p_shooterMotor->EnableControl(encoderInitialPosition);     
}

void Shooter::ReportStatus()
{
	double jagSpeed = p_shooterMotor->GetSpeed(); 
	double jagTemp  = p_shooterMotor->GetTemperature();
	UINT8 jagHWVersion = p_shooterMotor->GetHardwareVersion();
	UINT32 jagFWVersion = p_shooterMotor->GetFirmwareVersion();
	double jagOutV = p_shooterMotor->GetOutputVoltage();

	// Send values to SmartDashboard
	SmartDashboard::PutNumber("Jaguar Current Speed [RPM]", jagSpeed);
	SmartDashboard::PutNumber("Jaguar Temperature [Degrees C]", jagTemp);
	SmartDashboard::PutNumber("Jaguar Hardware Version", double(jagHWVersion));
	SmartDashboard::PutNumber("Jaguar Firmware Version", double(jagFWVersion));
	SmartDashboard::PutNumber("P Value", p_shooterMotor->GetP());
	SmartDashboard::PutNumber("I Value", p_shooterMotor->GetI());
	SmartDashboard::PutNumber("D Value", p_shooterMotor->GetD());
	SmartDashboard::PutNumber("Output Voltage [V]", jagOutV);
}


void Shooter::Run(double wheelSpeed)
{
	
	SmartDashboard::PutNumber("set speed", wheelSpeed);
	p_shooterMotor->Set(wheelSpeed, syncGroup); // set wheel rpm
	CANJaguar::UpdateSyncGroup(syncGroup);

	ReportStatus();

}

void Shooter::Stop()
{
	Run(0.0);
}
