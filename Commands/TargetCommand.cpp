// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"

// Identify resources required by this command.
// Other commands that are using these resources will be Canceled
// when this command is Started.
TargetCommand::TargetCommand()
{
    Requires(Robot::driveBase());

    SmartDashboard::PutNumber("height", 0.0);
    SmartDashboard::PutNumber("width",  0.0);
    SmartDashboard::PutNumber("offset", 0.0);
}

// Called just before this Command runs the first time
void TargetCommand::Initialize()
{
    printf("+++ TargetCommand::Initialize\n");
    m_tgtHeight = 0;
    m_tgtWidth  = 0;
    m_tgtOffset = 0;
    m_done = false;
}

// Called repeatedly when this Command is scheduled to run
void TargetCommand::Execute()
{
    bool moveIt = false;

    printf("+++ TargetCommand::Execute\n");
    int newHeight = (int)(SmartDashboard::GetNumber("height") + 0.5);
    if (newHeight != m_tgtHeight) {
	printf("+++ height has changed to %5d +++\n", newHeight);
	m_tgtHeight = newHeight;
	moveIt = true;
    }
    int newWidth = (int)(SmartDashboard::GetNumber("width") + 0.5);
    if (newWidth != m_tgtWidth) {
	printf("+++ width  has changed to %5d +++\n", newWidth);
	m_tgtWidth = newWidth;
	moveIt = true;
    }
    int newOffset = (int)(SmartDashboard::GetNumber("offset") + 0.5);
    if (newOffset != m_tgtOffset) {
	printf("+++ offset has changed to %5d +++\n", newOffset);
	m_tgtOffset = newOffset;
	moveIt = true;
    }

    if (moveIt) {
	if (abs(m_tgtOffset) < 10) {
	    printf("+++ TargetCommand::Done!\n");
	    m_done = true;
	    Robot::driveBase()->Drive3(0.0, 0.0, 0.0);
	} else {
	    const float kP = 4.0;
	    float t = kP * (float)m_tgtOffset / (float)m_tgtWidth;
	    printf("+++ twist %g\n", t);
	    Robot::driveBase()->Drive3(0.0, 0.0, t);
	}
    } else {
	Robot::driveBase()->Drive3(0.0, 0.0, 0.0);
    }
}

// Make this return true when this Command no longer needs to run execute()
bool TargetCommand::IsFinished()
{
    return m_done;
}

// Called once after isFinished returns true
void TargetCommand::End()
{
    printf("+++ TargetCommand::End\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TargetCommand::Interrupted()
{
    printf("+++ TargetCommand::Interrupted\n");
}
