// FIRST Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include <WPILib.h>
#include "Robot.h"
#include "DriveBase.h"
#include "SaveAutoMove.h"
#include "OI.h"

double SaveAutoMove::GetCurrentValueAt(int i, int j, int k){
	return m_currentValues[i][j][k];
}
int SaveAutoMove::GetKnob(){
	return Robot::oi()->GetAuto() - 1;
}
void SaveAutoMove::GetCurrentValues(int SwitchPos, double (*outp)[6][4]){
	if (SwitchPos < 0 || SwitchPos > 8){
		outp = NULL;
	}
	else {
		outp = &m_currentValues[SwitchPos];
	}
}

SaveAutoMove::SaveAutoMove() :
    Command("SaveAutoMove")
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	//Requires(Robot::driveBase());
	// The climber is directly controlled by a hard switch;
	//   don't mess with it here.
	Requires(Robot::driveBase());
	InitDefaultValues();
	Preferences *pref = Preferences::GetInstance();

	char* names[] = {"x","y","twist","time"};
	for (int i = 0;i<NUM_MODES;i++){
		for (int j = 0;j<NUM_MOVES;j++){
			for (int k = 0;k<NUM_VALUES;k++){
				char* characters = (char*)malloc(20*sizeof(char));
				sprintf(characters, "Md.%d_Mv.%d_%s",  i, j, names[k]);
				m_SDLabels[i][j][k] = characters;
				m_currentValues[i][j][k] = pref->GetFloat(m_SDLabels[i][j][k], m_defaultValues[i][j][k]); 
				printf("%s\t %s\n", m_SDLabels[i][j][k], characters);
			}
		}
	}
	m_autoModeKnob = GetKnob();
	printf("m_autoModeKnob = %d\n", m_autoModeKnob);
	for (int i = 0;i<NUM_MOVES;i++){
		//printf("i = %d\n", i);
		for (int j = 0;j<NUM_VALUES;j++){
			//printf("j = %d\n", j);
			SmartDashboard::PutNumber(m_SDLabels[m_autoModeKnob][i][j], m_currentValues[m_autoModeKnob][i][j]);
			//printf("%s\t", m_SDLabels[m_autoModeKnob][i][j]);
		}
		printf("\n");
	}

}

// Called just before this Command runs the first time
void SaveAutoMove::Initialize()
{
	printf("SaveAutoMove::Initialize\n");
	Preferences *pref = Preferences::GetInstance();
	
	m_autoModeKnob = GetKnob();
	for (int i = 0;i<NUM_MOVES;i++){
		for (int j = 0;j<NUM_VALUES;j++){
			//SmartDashboard::PutNumber(m_SDLabels[m_autoModeKnob][i][j], m_currentValues[m_autoModeKnob][i][j]);
			m_currentValues[m_autoModeKnob][i][j] = SmartDashboard::GetNumber(m_SDLabels[m_autoModeKnob][i][j]);
			printf("Saving %s: %f\n", m_SDLabels[m_autoModeKnob][i][j],  m_currentValues[m_autoModeKnob][i][j]);
			pref->PutFloat(m_SDLabels[m_autoModeKnob][i][j],  m_currentValues[m_autoModeKnob][i][j]);
		}
	}
	pref->Save();
}

// Called repeatedly when this Command is scheduled to run
void SaveAutoMove::Execute()
{
    ;
}

// Make this return true when this Command no longer needs to run execute()
bool SaveAutoMove::IsFinished()
{
    printf("SaveAutoMove::IsFinished\n");
    return true;
}

// Called once after isFinished returns true
void SaveAutoMove::End()
{
    printf("SaveAutoMove::End\n");
	for (int i = 0;i<NUM_MODES;i++){
		for (int j = 0;j<NUM_MOVES;j++){
			for (int k = 0;k<NUM_VALUES;k++){
				free(m_SDLabels[i][j][k]);
			}
		}
	}
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SaveAutoMove::Interrupted()
{
    printf("SaveAutoMove::Interrupted\n");
}
void SaveAutoMove::InitDefaultValues()
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
