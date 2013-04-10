// FIRST Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include <WPILib.h>
#include "Robot.h"
#include "OI.h"
#include "BlinkyLight.h"
#include "Shooter.h"
#include "AutoCommand.h"
#include "BlinkyBreathe.h"
#include "TiltCommand.h"
#include "TargetCommand.h"
#include "ShootCommand.h"
#include "TimedDrive.h"

AutoCommand::AutoCommand() :
    CommandGroup("AutoCommand")
{
    m_blinky = new BlinkyBreathe(3.0);
    m_tilt = new TiltCommand(Shooter::kLong);
    m_target = new TargetCommand();
    // default setting: shoot 3 disks for 3/6 points each from mid-field
    m_shoot = new ShootCommand(Shooter::kMid, 3, 3);
    
    int autoModeKnob = Robot::oi()->GetAuto(); 
    m_left = new TimedDrive(-0.8,0.0,-0.1,1.3);
    m_right = new TimedDrive(0.8,0.0,0.1,1.3);
    m_brake = new TimedDrive(0,0,0,.5);
    m_back = new TimedDrive(0.0,0.8,0.05,1.5);
    m_halfBack = new TimedDrive(0.0,0.8,0.05,0.75);
    m_longLeft = new TimedDrive(-0.8,0.0,-0.1,1.6);
    m_longRight = new TimedDrive(0.8,0.0,0.1,1.6);
    m_shortLeft = new TimedDrive(-0.8,0.0,-0.1,0.6);
    m_shortRight = new TimedDrive(-0.8,0.0,-0.1,0.6);
    
    AddParallel(m_blinky);
    AddSequential(m_tilt);
    //AddSequential(m_target);
    AddSequential(m_shoot);
    /*
     PRIGHT_FRIGHT 1
 	 PRIGHT_FMID   2
	 PRIGHT_FLEFT  3
	 PMID_FRIGHT   4
 	 PMID_FMID     5
 	 PMID_FLEFT    6
	 PLEFT_FRIGHT  7
	 PLEFT_FMID    8
	 PLEFT_FLEFT   9
     */
    switch(autoModeKnob) {
    	case PRIGHT_FRIGHT:
    	    AddSequential(m_right);
    	    AddSequential(m_brake);
    	    AddSequential(m_back);
    		break;
    	case PRIGHT_FMID:
    		AddSequential(m_halfBack);
    		AddSequential(m_brake);
    		AddSequential(m_shortLeft);
    		AddSequential(m_brake);
    		AddSequential(m_halfBack);
    	    break;
    	case PRIGHT_FLEFT:
    	    AddSequential(m_halfBack);
    	    AddSequential(m_brake);
    	    AddSequential(m_longLeft);
    	    AddSequential(m_brake);
    	    AddSequential(m_halfBack);
    	    break;
    	case PLEFT_FRIGHT:
			AddSequential(m_halfBack);
			AddSequential(m_brake);
			AddSequential(m_longRight);
			AddSequential(m_brake);
			AddSequential(m_halfBack);
			break;
    	case PLEFT_FMID:
			AddSequential(m_halfBack);
			AddSequential(m_brake);
			AddSequential(m_shortRight);
			AddSequential(m_brake);
			AddSequential(m_halfBack);
			break;
    	case PLEFT_FLEFT:
			AddSequential(m_left);
			AddSequential(m_brake);
			AddSequential(m_back);
			break;
    	case PMID_FRIGHT:
			AddSequential(m_halfBack);
			AddSequential(m_brake);
			AddSequential(m_shortRight);
			AddSequential(m_right);
			AddSequential(m_brake);
			AddSequential(m_halfBack);
			break;
    	case PMID_FMID:
    		AddSequential(m_back);
    	    AddSequential(m_brake);
    	    break;
    	case PMID_FLEFT:
			AddSequential(m_halfBack);
			AddSequential(m_brake);
			AddSequential(m_shortLeft);
			AddSequential(m_left);
			AddSequential(m_brake);
			AddSequential(m_halfBack);
			break;
    }
        
}

AutoCommand::~AutoCommand()
{
    // this should remove command instances from scheduler,
    // then delete them.
}

void AutoCommand::Initialize()
{
    printf("AutoCommand::Initialize\n");

    m_shoot->SetDistance(Shooter::kMid);

    // TBD: We can do this based on the "AutoSelect" rotary switch or on
    // the gunner's target height selector.  Figure out which the drive
    // team prefers!

    // For now, use the AutoSelect.  When set to "2", shoot for the 2-point
    // goal, else for the 3-point goal.
    m_shoot->SetTarget( 3 );
    m_shoot->SetNumDisks(3);
    
    
}

void AutoCommand::Execute()
{
}

bool AutoCommand::IsFinished()
{
    // this should return true when all commands are done
    return false;
}

void AutoCommand::End()
{
    printf("AutoCommand::End\n");
}

void AutoCommand::Interrupted()
{
    printf("AutoCommand::Interrupted\n");
    Robot::blinkyLight()->Set(0.0);
}

