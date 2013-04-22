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


struct TimedDriveVariables {
	double x,y,twist,time;
	TimedDriveVariables(){
		x = 0;
		y = 0;
		twist = 0;
		time = 0;
	}
	TimedDriveVariables(double xtdv, double ytdv, double twisttdv, double timetdv){
		x = xtdv;
		y = ytdv;
		twist = twisttdv;
		time = timetdv;
	}
};
void SetTimedDrive(TimedDrive* td, TimedDriveVariables tdv){
	td->Set(tdv.x, tdv.y, tdv.twist, tdv.time);
}
struct AutoProgram {
	TimedDriveVariables move[6];
};


void PrintDebug(char* stringToPrint){
	printf("\n##########\n%s\n##########\n", stringToPrint);
}

int GetKnob(){
	return Robot::oi()->GetAuto() - 1;
}
AutoCommand::AutoCommand() :
    CommandGroup("AutoCommand")
{
	m_blinky = new BlinkyBreathe(3.0);
    m_tilt = new TiltCommand(Shooter::kLong);
    m_target = new TargetCommand();
    // default setting: shoot 3 disks for 3/6 points each from mid-field
    m_shoot = new ShootCommand(Shooter::kMid, 3, 3);

    m_firstMove = new TimedDrive(0.0,0.0,0.0,0.0);
    m_secondMove = new TimedDrive(0.0,0.0,0.0,0.0);
    m_thirdMove = new TimedDrive(0.0,0.0,0.0,0.0);
    m_fourthMove = new TimedDrive(0.0,0.0,0.0,0.0);
    m_fifthMove = new TimedDrive(0.0,0.0,0.0,0.0);
    m_sixthMove = new TimedDrive(0.0,0.0,0.0,0.0);
    
    AddParallel(m_blinky);
	PrintDebug("m_blinky");

	AddSequential(m_tilt);
	PrintDebug("m_tilt");

	////AddSequential(m_target);

	//AddSequential(m_shoot);
	PrintDebug("m_shoot");

	AddSequential(m_firstMove);
	AddSequential(m_secondMove);
	AddSequential(m_thirdMove);
	AddSequential(m_fourthMove);
	AddSequential(m_fifthMove);
	AddSequential(m_sixthMove);
	
	//SmartDashboard::PutNumber(characters, tempValue);
	
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
    
    AutoProgram moveValues;
    
    m_autoModeKnob = GetKnob();
    double tempValues[6][4];
    for (int i = 0;i<6;i++){
		for (int j = 0;j<4;j++){
			tempValues[i][j] = Robot::oi()->GetCurrentValueAt(m_autoModeKnob, i, j);
			printf("%f\t", tempValues[i][j]);
		}
		printf("\n");
	}
    switch(m_autoModeKnob) {
		case PRIGHT_FRIGHT:
			PrintDebug("PRIGHT_FRIGHT");
			for (int i = 0;i<6;i++){
				for (int j = 0;j<4;j++){
					printf("%f\t", tempValues[i][j]);
				}
				moveValues.move[i] = TimedDriveVariables(
						tempValues[i][0],
						tempValues[i][1],
						tempValues[i][2],
						tempValues[i][3]
				);
				printf("\n");
			}   
			/*
			SmartDashboard::GetNumber(m_SDLabels[0][0][0]),
			SmartDashboard::GetNumber(m_SDLabels[0][0][1]),
			SmartDashboard::GetNumber(m_SDLabels[0][0][2]),
			SmartDashboard::GetNumber(m_SDLabels[0][0][3])); 0.8,0.0,0.1,1.3);
			moveValues.move[1] = TimedDriveVariables(0.0,0.0,0.0,0.5);
			moveValues.move[2] = TimedDriveVariables(0.0,0.8,0.05,1.5);
			moveValues.move[3] = TimedDriveVariables(0.0,0.0,0.0,0.0);
			moveValues.move[4] = TimedDriveVariables(0.0,0.0,0.0,0.0);
			moveValues.move[5] = TimedDriveVariables(0.0,0.0,0.0,0.0);
			*/
			/*
			m_firstMove->Set(0.8,0.0,0.1,1.3);
			m_secondMove->Set(0,0,0,0.5);
			m_thirdMove->Set(0.0,0.8,0.05,1.5);
			m_fourthMove->Set(0.0,0.0,0.0,0.0);
			m_fifthMove->Set(0.0,0.0,0.0,0.0);
			m_sixthMove->Set(0.0,0.0,0.0,0.0);
			*/
			SetTimedDrive(m_firstMove, moveValues.move[0]);
			SetTimedDrive(m_secondMove, moveValues.move[1]);
			SetTimedDrive(m_thirdMove, moveValues.move[2]);
			SetTimedDrive(m_fourthMove, moveValues.move[3]);
			SetTimedDrive(m_fifthMove, moveValues.move[4]);
			SetTimedDrive(m_sixthMove, moveValues.move[5]);
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
