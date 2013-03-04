// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include <WPILib.h>
#include "Robot.h"
#include "OI.h"
#include "ClimberExtender.h"
#include "ClimberClaw.h"
#include "ClimberHooks.h"
#include "ClimbCommand.h"

#define	EXTEND_TIME	1.2
#define	GRAB_TIME	1.2

ClimbCommand::ClimbCommand()
{
    Requires(Robot::extender());
    Requires(Robot::claw());
    Requires(Robot::climber());
}

void ClimbCommand::Initialize()
{
    Robot::claw()->Set(ClimberClaw::kOpen);
    Robot::extender()->Set(ClimberExtender::kRetracted);
    m_state = 0;
}

void ClimbCommand::Execute()
{
    // The OI "tip" switch must be on for the climber system to run.

    // In state 0/1 (before we've grabbed the rail or started climbing),
    // turning the tip switch off retracts the climber.  In all other
    // states, turning the tip switch off simply stops the climber in
    // its current state/position.  Turning the switch on again resumes
    // motion from where it was stopped.

    if (!Robot::oi()->GetTip()) {
	if (m_state == 0 || m_state == 1) {
	    Robot::claw()->Set(ClimberClaw::kOpen);
	    Robot::extender()->Set( ClimberExtender::kRetracted );
	    m_state = 0;
	}
	Robot::climber()->Set(ClimberHooks::kStop);
	return;
    }

    switch (m_state) {
    case 0:
	// open claw 
	Robot::claw()->Set(ClimberClaw::kOpen);
	// motor stopped, feed watchdog
	Robot::climber()->Set(ClimberHooks::kStop);

	// wait for claw to open
	if (Robot::claw()->Get() == ClimberClaw::kOpen) {
	    ++m_state;
	}
	break;

    case 1:
	// claw open, now extend climber
	Robot::extender()->Set(ClimberExtender::kExtended);
	// motor stopped, feed watchdog
	Robot::climber()->Set(ClimberHooks::kStop);

	// wait for extender to finish and driver to move switch
	//   to middle or up position
	if (Robot::extender()->Get() == ClimberExtender::kExtended &&
	    Robot::oi()->GetClimber() > 0)
	{
	    ++m_state;
	}
	break;

    case 2:
	// climber extended, now close claw
	Robot::claw()->Set(ClimberClaw::kClosed);
	// motor stopped, feed watchdog
	Robot::climber()->Set(ClimberHooks::kStop);

	// wait for claw to close and driver to set climber switch "up"
	if (Robot::claw()->Get() == ClimberClaw::kClosed &&
	    Robot::oi()->GetClimber() == 2)
	{
	    ++m_state;
	}
	// else if the driver sets the climber switch to "down",
	//   open the claw and go back for another try
	else if (Robot::oi()->GetClimber() == 0)
	{
	    m_state = 0;
	}
	break;

    case 3:
	// climber extended, claw closed
	// run long hook up to top
	// wait at top for driver to set climber switch to "middle" or "down"
	if (Robot::climber()->Set(ClimberHooks::kUp, ClimberHooks::kTop) &&
	    Robot::oi()->GetClimber() <= 1)
	{
	    ++m_state;
	}
	break;

    case 4:
	// run long hook down to mid-high so hook is in contact with rail,
	if (Robot::climber()->Set(ClimberHooks::kDown, ClimberHooks::kMidHigh))
	{
	    ++m_state;
	}
	break;

    case 5:
	// motor stopped, feed watchdog
	Robot::climber()->Set(ClimberHooks::kStop);
	// open the claw to step over the rail
	Robot::claw()->Set(ClimberClaw::kOpen);

	// wait for claw to open
	if (Robot::claw()->Get() == ClimberClaw::kOpen) {
	    ++m_state;
	}
	break;

    case 6:
	// drive long hook down to mid-low so claw is above rail
	if (Robot::climber()->Set(ClimberHooks::kDown, ClimberHooks::kMidLow))
	{
	    ++m_state;
	}
	break;

    case 7:
	// motor stopped, feed watchdog
	Robot::climber()->Set(ClimberHooks::kStop);
	// re-engage the claw
	Robot::claw()->Set(ClimberClaw::kClosed);
	
	// wait for claw to close and driver to verify by setting the
	//  climber switch to "down"
	if ((Robot::claw()->Get() == ClimberClaw::kClosed) &&
	    Robot::oi()->GetClimber() == 0)
	{
	    ++m_state;
	}
	// else if the driver sets the climber switch to "up",
	//   open the claw and go back for another try
	else if (Robot::oi()->GetClimber() == 2)
	{
	    m_state = 6;
	}
	break;

    case 8:
	// drive long hook down to bottom so short hook is above rail
	if (Robot::climber()->Set(ClimberHooks::kDown, ClimberHooks::kBottom))
	{
	    ++m_state;
	}
	break;

    case 9:
	// at bottom, motor stopped, feed watchdog
	Robot::climber()->Set(ClimberHooks::kStop);

	// wait for driver to set climb switch back to "mid" or "up"
	if (Robot::oi()->GetClimber() > 0) {
	    m_state = 3;
	}
	break;

    default:
	// "can't happen"
	// stop and wait here for driver to reset the robot
	Robot::climber()->Set(ClimberHooks::kStop);
	break;
    }
}

bool ClimbCommand::IsFinished()
{
    return false;
}

void ClimbCommand::Stop()
{
    ;
}

void ClimbCommand::Interrupted()
{
    ;
}


