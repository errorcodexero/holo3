// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

Jaguar* RobotMap::driveBaseRight = NULL;
Jaguar* RobotMap::driveBaseFront = NULL;
Jaguar* RobotMap::driveBaseLeft = NULL;
RobotDrive3* RobotMap::driveBaseDrive3 = NULL;

Victor* RobotMap::blinkyPWM = NULL;

void RobotMap::init()
{
	LiveWindow* lw = LiveWindow::GetInstance();

	driveBaseFront = new Jaguar(1, 1);
	// driveBaseFront->SetSafetyEnabled(false);
	lw->AddActuator("RobotDrive3", "Front", driveBaseFront);
	
	driveBaseLeft = new Jaguar(1, 2);
	// driveBaseLeft->SetSafetyEnabled(false);
	lw->AddActuator("RobotDrive3", "Left", driveBaseLeft);
	
	driveBaseRight = new Jaguar(1, 3);
	// driveBaseRight->SetSafetyEnabled(false);
	lw->AddActuator("RobotDrive3", "Right", driveBaseRight);
	
	driveBaseDrive3 = new RobotDrive3(driveBaseFront, driveBaseLeft,
              driveBaseRight);
	
	driveBaseDrive3->SetSafetyEnabled(true);
        driveBaseDrive3->SetExpiration(0.1);
        driveBaseDrive3->SetSensitivity(0.5);
        driveBaseDrive3->SetMaxOutput(1.0);

	blinkyPWM = new Victor(1, 4);
	// blinky lights don't need watchdogs
	blinkyPWM->SetSafetyEnabled(false);
	lw->AddActuator("BlinkyLight", "PWM", blinkyPWM);
}
