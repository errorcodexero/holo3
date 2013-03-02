#ifndef CLIMBER_H
#define CLIMBER_H

enum ClimberStateSingle {
	TillLim,
	SingleUpIdle,
	SingleDwnIdle,
	GoingUp,
	GoingDwn,
	SingleErrorState
};

typedef int ClimberMotorOut; // When 0, Off; 1, Forward; -1, Reverse;
	
ClimberMotorOut climberReturnOutSingle (ClimberStateSingle climberInput);
ClimberStateSingle nextStateSingle (ClimberStateSingle currentState, bool TopLim, bool BotLim, bool btn, bool errorbtnDwn, bool errorbtnUp);

//Code for ClimberTest
const char* getStringSingle (ClimberStateSingle );
void printSingle(ClimberMotorOut printClimberMotorOut);

#endif 
