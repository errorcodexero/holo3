// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include <WPILib.h>
#include <Utility.h>
#include "Robot.h"
#include "Rotate.h"
#include <math.h>

Rotate::Rotate()
{
    Requires(Robot::driveBase());
    m_x = 0.0;
    m_y = 0.0;
    m_t = 0.0;
    m_time = 0.0;
    m_startTime = 0.0;
    SmartDashboard::PutNumber("Rotate X", 0.0);
    SmartDashboard::PutNumber("Rotate Y", 0.0);
    SmartDashboard::PutNumber("Rotate T", 0.0);
    SmartDashboard::PutNumber("Rotate time", 0.0);
}

// Called just before this Command runs the first time
void Rotate::Initialize()
{
    m_startTime = Timer::GetFPGATimestamp();
}

// Call this while running to update the speed, direction or time to run.
void Rotate::Set( double x, double y, double t, double seconds )
{
    m_x = SmartDashboard::GetNumber("Rotate X");
    m_y = SmartDashboard::GetNumber("Rotate Y");
    m_t = SmartDashboard::GetNumber("Rotate T");
    m_time = SmartDashboard::GetNumber("Rotate time");

    m_startTime = Timer::GetFPGATimestamp();
}

// Called repeatedly when this Command is scheduled to run
void Rotate::Execute()
{
    Robot::driveBase()->Drive3(m_x, m_y, m_t);
}

// Make this return true when this Command no longer needs to run execute()
bool Rotate::IsFinished()
{
    return ((Timer::GetFPGATimestamp() - m_startTime) >= m_time);
}

// Called once after isFinished returns true
void Rotate::End()
{
    Robot::driveBase()->Drive3(0.0, 0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Rotate::Interrupted()
{
    ;
}

