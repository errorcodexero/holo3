// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"
#include <math.h>

// Identify resources required by this command.
// Other commands that are using these resources will be Canceled
// when this command is Started.
TargetCommand::TargetCommand() : TimedDrive( 0.0, 0.0, 0.0, 0.0 )
{
    SmartDashboard::PutNumber("kP", 0.350);
    SmartDashboard::PutNumber("kT", 0.250);
    SmartDashboard::PutNumber("height", 0.0);
    SmartDashboard::PutNumber("width",  0.0);
    SmartDashboard::PutNumber("offset", 0.0);
    m_done = 0;
}

// Called just before this Command runs the first time
void TargetCommand::Initialize()
{
    printf("TargetCommand::Initialize\n");
    m_kP = SmartDashboard::GetNumber("kP");
    m_kT = SmartDashboard::GetNumber("kT");
    m_tgtHeight = 0;
    m_tgtWidth  = 0;
    m_tgtOffset = 0;
    m_done = 0;
}

// Called repeatedly when this Command is scheduled to run
void TargetCommand::Execute()
{
    // printf("TargetCommand::Execute\n");

    bool moveIt = false;
    int newHeight = (int)(SmartDashboard::GetNumber("height") + 0.5);
    if (newHeight != m_tgtHeight) {
	printf("+++ height was %5d now %5d +++\n", m_tgtHeight, newHeight);
	m_tgtHeight = newHeight;
	moveIt = true;
    }
    int newWidth = (int)(SmartDashboard::GetNumber("width") + 0.5);
    if (newWidth != m_tgtWidth) {
	printf("+++ width  was %5d now %5d +++\n", m_tgtWidth, newWidth);
	m_tgtWidth = newWidth;
	moveIt = true;
    }
    int newOffset = (int)(SmartDashboard::GetNumber("offset") + 0.5);
    if (newOffset != m_tgtOffset) {
	printf("+++ offset was %5d now %5d +++\n", m_tgtOffset, newOffset);
	m_tgtOffset = newOffset;
	moveIt = true;
    }

    if (moveIt) {
	if (abs(m_tgtOffset) < 10) {
	    printf("+++ done!\n");
	    Set(0.0, 0.0, 0.0, 0.0);
	    ++m_done;
	} else if (m_tgtWidth > 10) {
	    float error = (float)m_tgtOffset / (float)m_tgtWidth;
	    float twist = (error < 0) ? -m_kP : m_kP;
	    float secs  = fabs(error) * m_kT;
	    printf("+++ error %g twist %g time %g\n", error, twist, secs);
	    Set(0.0, 0.0, twist, secs);
	    m_done = 0;
	}
    }

    TimedDrive::Execute();
}

bool TargetCommand::IsFinished()
{
    if (TimedDrive::IsFinished()) {
	Set(0.0, 0.0, 0.0, 0.0);
	return (m_done >= 10);
    }
    return false;
}
