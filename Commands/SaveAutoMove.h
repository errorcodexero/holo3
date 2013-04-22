// FIRST Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef SAVE_AUTOMOVE_H
#define SAVE_AUTOMOVE_H

#include <Commands/Command.h>

#define NUM_MODES 9
#define NUM_MOVES 6
#define NUM_VALUES 4
		
struct sSpecificValues{
	double values[6][4];
};

class SaveAutoMove: public Command {
public:
	SaveAutoMove();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	void GetCurrentValues(int SwitchPos, double (*outp)[6][4]);
	double GetCurrentValueAt(int i, int j, int k);
private:
	char* m_SDLabels[NUM_MODES][NUM_MOVES][NUM_VALUES];
	int m_autoModeKnob;
	double m_currentValues[NUM_MODES][NUM_MOVES][NUM_VALUES];
	double m_defaultValues[NUM_MODES][NUM_MOVES][NUM_VALUES];
	void InitDefaultValues();
	int GetKnob();
};

#endif
