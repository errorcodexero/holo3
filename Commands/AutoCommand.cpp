// FIRST Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include <WPILib.h>
#include "Robot.h"
#include "OI.h"
#include "BlinkyLight.h"
#include "AutoCommand.h"
#include "BlinkyBreathe.h"
#include "TimedDrive.h"

void PrintDebug(char* stringToPrint){
	printf("\n##########\n%s\n##########\n", stringToPrint);
}

AutoCommand::AutoCommand() :
    CommandGroup("AutoCommand")
{

    m_blinky = new BlinkyBreathe(3.0);

    m_autoModeKnob = Robot::oi()->GetAuto();

    m_firstMove = new TimedDrive(0.0,0.0,0.0,0.0);
    m_secondMove = new TimedDrive(0.0,0.0,0.0,0.0);
    m_thirdMove = new TimedDrive(0.0,0.0,0.0,0.0);
    m_fourthMove = new TimedDrive(0.0,0.0,0.0,0.0);
    m_fifthMove = new TimedDrive(0.0,0.0,0.0,0.0);
    m_sixthMove = new TimedDrive(0.0,0.0,0.0,0.0);
    
    AddParallel(m_blinky);
	PrintDebug("m_blinky");



	////AddSequential(m_target);

	//AddSequential(m_shoot);
	PrintDebug("m_shoot");

	AddSequential(m_firstMove);
	AddSequential(m_secondMove);
	AddSequential(m_thirdMove);
	AddSequential(m_fourthMove);
	AddSequential(m_fifthMove);
	AddSequential(m_sixthMove);
}

AutoCommand::~AutoCommand()
{
    // this should remove command instances from scheduler,
    // then delete them.
}

void AutoCommand::Initialize()
{
    printf("AutoCommand::Initialize\n");
    
    // TBD: We can do this based on the "AutoSelect" rotary switch or on
    // the gunner's target height selector.  Figure out which the drive
    // team prefers!

    // For now, use the AutoSelect.  When set to "2", shoot for the 2-point
    // goal, else for the 3-point goal.
    
    m_autoModeKnob = Robot::oi()->GetAuto();
    switch(m_autoModeKnob) {
		case PRIGHT_FRIGHT:
			PrintDebug("PRIGHT_FRIGHT");
			m_firstMove->Set(0.8,0.0,0.1,1.3);
			m_secondMove->Set(0,0,0,0.5);
			m_thirdMove->Set(0.0,0.8,0.05,1.5);
			m_fourthMove->Set(0.0,0.0,0.0,0.0);
			m_fifthMove->Set(0.0,0.0,0.0,0.0);
			m_sixthMove->Set(0.0,0.0,0.0,0.0);
			break;
		case PRIGHT_FMID:
			PrintDebug("PRIGHT_FMID");
			m_firstMove->Set(0.0,0.8,0.05,0.75);
			m_secondMove->Set(0,0,0,0.5);
			m_thirdMove->Set(-0.8,0.0,-0.1,0.6);
			m_fourthMove->Set(0,0,0,0.5);
			m_fifthMove->Set(0.0,0.8,0.05,0.75);
			m_sixthMove->Set(0.0,0.0,0.0,0.0);
			break;
		case PRIGHT_FLEFT:
			PrintDebug("PRIGHT_FLEFT");
			m_firstMove->Set(0.0,0.8,0.05,0.75);
			m_secondMove->Set(0,0,0,0.5);
			m_thirdMove->Set(-0.8,0.0,-0.1,1.6);
			m_fourthMove->Set(0,0,0,0.5);
			m_fifthMove->Set(0.0,0.8,0.05,0.75);
			m_sixthMove->Set(0.0,0.0,0.0,0.0);
			break;
		case PLEFT_FRIGHT:
			PrintDebug("PLEFT_FRIGHT");
			m_firstMove->Set(0.0,0.8,0.05,0.75);
			m_secondMove->Set(0,0,0,0.5);
			m_thirdMove->Set(0.8,0.0,0.1,1.6);
			m_fourthMove->Set(0,0,0,0.5);
			m_fifthMove->Set(0.0,0.8,0.05,0.75);
			m_sixthMove->Set(0.0,0.0,0.0,0.0);
			break;
		case PLEFT_FMID:
			PrintDebug("PLEFT_FMID");
			m_firstMove->Set(0.0,0.8,0.05,0.75);
			m_secondMove->Set(0,0,0,0.5);
			m_thirdMove->Set(0.8,0.0,0.1,0.6);
			m_fourthMove->Set(0,0,0,0.5);
			m_fifthMove->Set(0.0,0.8,0.05,0.75);
			m_sixthMove->Set(0.0,0.0,0.0,0.0);
			break;
		case PLEFT_FLEFT:
			PrintDebug("PLEFT_FLEFT");
			m_firstMove->Set(-0.8,0.0,-0.1,1.3);
			m_secondMove->Set(0,0,0,0.5);
			m_thirdMove->Set(0.0,0.8,0.05,1.5);
			m_fourthMove->Set(0.0,0.0,0.0,0.0);
			m_fifthMove->Set(0.0,0.0,0.0,0.0);
			m_sixthMove->Set(0.0,0.0,0.0,0.0);
			break;
		case PMID_FRIGHT:
			PrintDebug("PMID_FRIGHT");
			m_firstMove->Set(0.0,0.8,0.05,0.75);
			m_secondMove->Set(0,0,0,0.5);
			m_thirdMove->Set(0.8,0.0,0.1,0.6);
			m_fourthMove->Set(0.8,0.0,0.1,1.3);
			m_fifthMove->Set(0,0,0,0.5);
			m_sixthMove->Set(0.0,0.8,0.05,0.75);
			break;
		case PMID_FMID:
			PrintDebug("PMID_FMID");
			m_firstMove->Set(0.0,0.8,0.05,1.5);
			m_secondMove->Set(0,0,0,0.5);
			m_thirdMove->Set(0.0,0.0,0.0,0.0);
			m_fourthMove->Set(0.0,0.0,0.0,0.0);
			m_fifthMove->Set(0.0,0.0,0.0,0.0);
			m_sixthMove->Set(0.0,0.0,0.0,0.0);
			break;
		case PMID_FLEFT:
			PrintDebug("PMID_FLEFT");
			m_firstMove->Set(0.0,0.8,0.05,0.75);
			m_secondMove->Set(0,0,0,0.5);
			m_thirdMove->Set(-0.8,0.0,-0.1,0.6);
			m_fourthMove->Set(-0.8,0.0,-0.1,1.3);
			m_fifthMove->Set(0,0,0,0.5);
			m_sixthMove->Set(0.0,0.8,0.05,0.75);
			break;
		default:
			PrintDebug("default");
			break;
	   }
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

