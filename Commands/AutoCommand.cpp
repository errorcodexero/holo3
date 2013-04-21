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
	Preferences *pref = Preferences::GetInstance();
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
    InitDefaultValues();
	
	char* names[] = {"x","y","twist","time", NULL};
	for (int i = 0;i<NUM_MODES;i++){
		for (int j = 0;j<NUM_MOVES;j++){
			for (int k = 0;k<NUM_VALUES;k++){
				char characters[20];
				sprintf(characters, "Md.%d_Mv.%d_%s",  i, j, names[k]);
				m_SDLabels[i][j][k] = characters;
				m_currentValues[i][j][k] = pref->GetFloat(m_SDLabels[i][j][k], m_defaultValues[i][j][k]); 
			}
		}
	}
	//SmartDashboard::PutNumber(characters, tempValue);
	
	m_autoModeKnob = GetKnob();
	for (int i = 0;i<NUM_MOVES;i++){
		for (int j = 0;j<NUM_VALUES;j++){
			SmartDashboard::PutNumber(m_SDLabels[m_autoModeKnob][i][j], m_currentValues[m_autoModeKnob][i][j]);
		}
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
    
    AutoProgram moveValues;
    
    m_autoModeKnob = GetKnob();
    
    switch(m_autoModeKnob) {
		case PRIGHT_FRIGHT:
			PrintDebug("PRIGHT_FRIGHT");
			double temp[4];
			for (int i = 0;i<6;i++){
				for (int j = 0;j<4;j++){
					temp[j] = SmartDashboard::GetNumber(m_SDLabels[PRIGHT_FRIGHT - 1][i][j]);
				}
				moveValues.move[i] = TimedDriveVariables(temp[0],temp[1],temp[2],temp[3]);
				printf("Values have been read!\n");
			}
			
		    
		    moveValues.move[0] = TimedDriveVariables(
		    	SmartDashboard::GetNumber(m_SDLabels[0][0][0]),
		    	SmartDashboard::GetNumber(m_SDLabels[0][0][1]),
				SmartDashboard::GetNumber(m_SDLabels[0][0][2]),
				SmartDashboard::GetNumber(m_SDLabels[0][0][3])); // 0.8,0.0,0.1,1.3);
			moveValues.move[1] = TimedDriveVariables(0.0,0.0,0.0,0.5);
			moveValues.move[2] = TimedDriveVariables(0.0,0.8,0.05,1.5);
			moveValues.move[3] = TimedDriveVariables(0.0,0.0,0.0,0.0);
			moveValues.move[4] = TimedDriveVariables(0.0,0.0,0.0,0.0);
			moveValues.move[5] = TimedDriveVariables(0.0,0.0,0.0,0.0);
			
			/*
			m_firstMove->Set(0.8,0.0,0.1,1.3);
			m_secondMove->Set(0,0,0,0.5);
			m_thirdMove->Set(0.0,0.8,0.05,1.5);
			m_fourthMove->Set(0.0,0.0,0.0,0.0);
			m_fifthMove->Set(0.0,0.0,0.0,0.0);
			m_sixthMove->Set(0.0,0.0,0.0,0.0);
			*/
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

void AutoCommand::InitDefaultValues()
{
    m_defaultValues[0][0][0] = 0.8;
    m_defaultValues[0][0][1] = 0.0;
    m_defaultValues[0][0][2] = 0.1;
    m_defaultValues[0][0][3] = 1.3;
    //
    m_defaultValues[0][1][0] = 0.0;
    m_defaultValues[0][1][1] = 0.0;
    m_defaultValues[0][1][2] = 0.0;
    m_defaultValues[0][1][3] = 0.5;
    //
    m_defaultValues[0][2][0] = 0.0;
    m_defaultValues[0][2][1] = 0.8;
    m_defaultValues[0][2][2] = 0.05;
    m_defaultValues[0][2][3] = 1.5;
    //
    m_defaultValues[0][3][0] = 0.0;
    m_defaultValues[0][3][1] = 0.0;
    m_defaultValues[0][3][2] = 0.0;
    m_defaultValues[0][3][3] = 0.0;
    //
    m_defaultValues[0][4][0] = 0.0;
    m_defaultValues[0][4][1] = 0.0;
    m_defaultValues[0][4][2] = 0.0;
    m_defaultValues[0][4][3] = 0.0;
    //
    m_defaultValues[0][5][0] = 0.0;
    m_defaultValues[0][5][1] = 0.0;
    m_defaultValues[0][5][2] = 0.0;
    m_defaultValues[0][5][3] = 0.0;
    //PRIGHT_FMID/////////////////
    m_defaultValues[1][0][0] = 0.0;
    m_defaultValues[1][0][1] = 0.8;
    m_defaultValues[1][0][2] = 0.05;
    m_defaultValues[1][0][3] = 0.75;
    //
    m_defaultValues[1][1][0] = 0.0;
    m_defaultValues[1][1][1] = 0.0;
    m_defaultValues[1][1][2] = 0.0;
    m_defaultValues[1][1][3] = 0.5;
    //
    m_defaultValues[1][2][0] = -0.8;
    m_defaultValues[1][2][1] = 0.0;
    m_defaultValues[1][2][2] = -0.1;
    m_defaultValues[1][2][3] = 0.6;
    //
    m_defaultValues[1][3][0] = 0.0;
    m_defaultValues[1][3][1] = 0.0;
    m_defaultValues[1][3][2] = 0.0;
    m_defaultValues[1][3][3] = 0.5;
    //
    m_defaultValues[1][4][0] = 0.0;
    m_defaultValues[1][4][1] = 0.8;
    m_defaultValues[1][4][2] = 0.05;
    m_defaultValues[1][4][3] = 0.75;
    //
    m_defaultValues[1][5][0] = 0.0;
    m_defaultValues[1][5][1] = 0.0;
    m_defaultValues[1][5][2] = 0.0;
    m_defaultValues[1][5][3] = 0.0;
    //PRIGHT_FLEFT/////////////////
    m_defaultValues[2][0][0] = 0.0;
    m_defaultValues[2][0][1] = 0.8;
    m_defaultValues[2][0][2] = 0.05;
    m_defaultValues[2][0][3] = 0.75;
    //
    m_defaultValues[2][1][0] = 0.0;
    m_defaultValues[2][1][1] = 0.0;
    m_defaultValues[2][1][2] = 0.0;
    m_defaultValues[2][1][3] = 0.5;
    //
    m_defaultValues[2][2][0] = -0.8;
    m_defaultValues[2][2][1] = 0.0;
    m_defaultValues[2][2][2] = -0.1;
    m_defaultValues[2][2][3] = 1.6;
    //
    m_defaultValues[2][3][0] = 0.0;
    m_defaultValues[2][3][1] = 0.0;
    m_defaultValues[2][3][2] = 0.0;
    m_defaultValues[2][3][3] = 0.5;
    //
    m_defaultValues[2][4][0] = 0.0;
    m_defaultValues[2][4][1] = 0.0;
    m_defaultValues[2][4][2] = 0.0;
    m_defaultValues[2][4][3] = 0.5;
    //
    m_defaultValues[2][5][0] = 0.0;
    m_defaultValues[2][5][1] = 0.0;
    m_defaultValues[2][5][2] = 0.0;
    m_defaultValues[2][5][3] = 0.0;
    //PMID_FRIGHT///////////////
    m_defaultValues[3][0][0] = 0.0;
    m_defaultValues[3][0][1] = 0.8;
    m_defaultValues[3][0][2] = 0.05;
    m_defaultValues[3][0][3] = 0.75;
    //
    m_defaultValues[3][1][0] = 0.0;
    m_defaultValues[3][1][1] = 0.0;
    m_defaultValues[3][1][2] = 0.0;
    m_defaultValues[3][1][3] = 0.5;
    //
    m_defaultValues[3][2][0] = 0.8;
    m_defaultValues[3][2][1] = 0.0;
    m_defaultValues[3][2][2] = 0.1;
    m_defaultValues[3][2][3] = 0.6;
    //
    m_defaultValues[3][3][0] = 0.8;
    m_defaultValues[3][3][1] = 0.0;
    m_defaultValues[3][3][2] = 0.1;
    m_defaultValues[3][3][3] = 1.3;
    //
    m_defaultValues[3][4][0] = 0.0;
    m_defaultValues[3][4][1] = 0.0;
    m_defaultValues[3][4][2] = 0.0;
    m_defaultValues[3][4][3] = 0.5;
    //
    m_defaultValues[3][5][0] = 0.0;
    m_defaultValues[3][5][1] = 0.8;
    m_defaultValues[3][5][2] = 0.05;
    m_defaultValues[3][5][3] = 0.75;
    //PMID_FMID////////////////
    m_defaultValues[4][0][0] = 0.0;
    m_defaultValues[4][0][1] = 0.8;
    m_defaultValues[4][0][2] = 0.05;
    m_defaultValues[4][0][3] = 1.5;
    //
    m_defaultValues[4][1][0] = 0.0;
    m_defaultValues[4][1][1] = 0.0;
    m_defaultValues[4][1][2] = 0.0;
    m_defaultValues[4][1][3] = 0.5;
    //
    m_defaultValues[4][2][0] = 0.0;
    m_defaultValues[4][2][1] = 0.0;
    m_defaultValues[4][2][2] = 0.0;
    m_defaultValues[4][2][3] = 0.0;
    //
    m_defaultValues[4][3][0] = 0.0;
    m_defaultValues[4][3][1] = 0.0;
    m_defaultValues[4][3][2] = 0.0;
    m_defaultValues[4][3][3] = 0.0;
    //
    m_defaultValues[4][4][0] = 0.0;
    m_defaultValues[4][4][1] = 0.0;
    m_defaultValues[4][4][2] = 0.0;
    m_defaultValues[4][4][3] = 0.0;
    //
    m_defaultValues[4][5][0] = 0.0;
    m_defaultValues[4][5][1] = 0.0;
    m_defaultValues[4][5][2] = 0.0;
    m_defaultValues[4][5][3] = 0.0;
    //PMID_FLEFT///////////////////////////
    m_defaultValues[5][0][0] = 0.0;
    m_defaultValues[5][0][1] = 0.8;
    m_defaultValues[5][0][2] = 0.05;
    m_defaultValues[5][0][3] = 0.75;
    //
    m_defaultValues[5][1][0] = 0.0;
    m_defaultValues[5][1][1] = 0.0;
    m_defaultValues[5][1][2] = 0.0;
    m_defaultValues[5][1][3] = 0.5;
    //
    m_defaultValues[5][2][0] = -0.8;
    m_defaultValues[5][2][1] = 0.0;
    m_defaultValues[5][2][2] = -0.1;
    m_defaultValues[5][2][3] = 0.6;
    //
    m_defaultValues[5][3][0] = -0.8;
    m_defaultValues[5][3][1] = 0.0;
    m_defaultValues[5][3][2] = -0.1;
    m_defaultValues[5][3][3] = 1.3;
    //
    m_defaultValues[5][4][0] = 0.0;
    m_defaultValues[5][4][1] = 0.0;
    m_defaultValues[5][4][2] = 0.0;
    m_defaultValues[5][4][3] = 0.5;
    //
    m_defaultValues[5][5][0] = 0.0;
    m_defaultValues[5][5][1] = 0.8;
    m_defaultValues[5][5][2] = 0.05;
    m_defaultValues[5][5][3] = 0.75;
    //PRIGHT_FRIGHT/////////////////////////
    m_defaultValues[6][0][0] = 0.0;
    m_defaultValues[6][0][1] = 0.8;
    m_defaultValues[6][0][2] = 0.05;
    m_defaultValues[6][0][3] = 0.75;
    //
    m_defaultValues[6][1][0] = 0.0;
    m_defaultValues[6][1][1] = 0.0;
    m_defaultValues[6][1][2] = 0.0;
    m_defaultValues[6][1][3] = 0.5;
    //
    m_defaultValues[6][2][0] = 0.8;
    m_defaultValues[6][2][1] = 0.0;
    m_defaultValues[6][2][2] = 0.1;
    m_defaultValues[6][2][3] = 1.6;
    //
    m_defaultValues[6][3][0] = 0.0;
    m_defaultValues[6][3][1] = 0.0;
    m_defaultValues[6][3][2] = 0.0;
    m_defaultValues[6][3][3] = 0.5;
    //
    m_defaultValues[6][4][0] = 0.0;
    m_defaultValues[6][4][1] = 0.8;
    m_defaultValues[6][4][2] = 0.05;
    m_defaultValues[6][4][3] = 0.75;
    //
    m_defaultValues[6][5][0] = 0.0;
    m_defaultValues[6][5][1] = 0.0;
    m_defaultValues[6][5][2] = 0.0;
    m_defaultValues[6][5][3] = 0.0;
    //PRIGHT_FMID//////////////////////////
    m_defaultValues[7][0][0] = 0.0;
    m_defaultValues[7][0][1] = 0.8;
    m_defaultValues[7][0][2] = 0.05;
    m_defaultValues[7][0][3] = 0.75;
    //
    m_defaultValues[7][1][0] = 0.0;
    m_defaultValues[7][1][1] = 0.0;
    m_defaultValues[7][1][2] = 0.0;
    m_defaultValues[7][1][3] = 0.5;
    //
    m_defaultValues[7][2][0] = 0.8;
    m_defaultValues[7][2][1] = 0.0;
    m_defaultValues[7][2][2] = 0.1;
    m_defaultValues[7][2][3] = 0.6;
    //
    m_defaultValues[7][3][0] = 0.0;
    m_defaultValues[7][3][1] = 0.0;
    m_defaultValues[7][3][2] = 0.0;
    m_defaultValues[7][3][3] = 0.5;
    //
    m_defaultValues[7][4][0] = 0.0;
    m_defaultValues[7][4][1] = 0.8;
    m_defaultValues[7][4][2] = 0.05;
    m_defaultValues[7][4][3] = 0.75;
    //
    m_defaultValues[7][5][0] = 0.0;
    m_defaultValues[7][5][1] = 0.0;
    m_defaultValues[7][5][2] = 0.0;
    m_defaultValues[7][5][3] = 0.0;
    //PRIGHT_FLEFT//////////////////
    m_defaultValues[8][0][0] = -0.8;
    m_defaultValues[8][0][1] = 0.0;
    m_defaultValues[8][0][2] = -0.1;
    m_defaultValues[8][0][3] = 1.3;
    //
    m_defaultValues[8][1][0] = 0.0;
    m_defaultValues[8][1][1] = 0.0;
    m_defaultValues[8][1][2] = 0.0;
    m_defaultValues[8][1][3] = 0.5;
    //
    m_defaultValues[8][2][0] = 0.0;
    m_defaultValues[8][2][1] = 0.8;
    m_defaultValues[8][2][2] = 0.05;
    m_defaultValues[8][2][3] = 1.5;
    //
    m_defaultValues[8][3][0] = 0.0;
    m_defaultValues[8][3][1] = 0.0;
    m_defaultValues[8][3][2] = 0.0;
    m_defaultValues[8][3][3] = 0.0;
    //
    m_defaultValues[8][4][0] = 0.0;
    m_defaultValues[8][4][1] = 0.0;
    m_defaultValues[8][4][2] = 0.0;
    m_defaultValues[8][4][3] = 0.0;
    //
    m_defaultValues[8][5][0] = 0.0;
    m_defaultValues[8][5][1] = 0.0;
    m_defaultValues[8][5][2] = 0.0;
    m_defaultValues[8][5][3] = 0.0;
}
