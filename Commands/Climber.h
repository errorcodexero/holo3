#ifndef CLIMBER_H
#define CLIMBER_H
		
enum ClimberState {
	BothTillLim,
	LTillLim,
	RTillLim,
	UpIdle,
	DwnIdle,
	BothGoingUp,
	LeftGoingUp,
	RightGoingUp,
	LUpIdle,
	RUpIdle,
	BothGoingDwn,
	LeftGoingDwn,
	RightGoingDwn,
	LDwnIdle,
	RDwnIdle,
	ErrorState
};
 	
struct ClimberOutput {
	int motorL; int motorR; // When 0, Off; 1, Forward; -1, Reverse;
	ClimberOutput ();
	ClimberOutput (int a, int b);
};

ClimberOutput climberReturnOut (ClimberState climberInput);
ClimberState nextState (
	ClimberState currentState, 
	bool rTopLim, 
	bool lTopLim, 
	bool rBotLim, 
	bool lBotLim, 
	bool btn, 
	bool errorBtnUp, 
	bool errorBtnDwn
);

//ClimberTest Code
const char* getString (ClimberState );
void print(ClimberOutput printClimberOutput);

#endif
