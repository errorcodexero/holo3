#ifndef CLIMBERENUM_H
#define CLIMBERENUM_H

enum ClimberState {
	StartPos,
	UpLvl2,
	UpLvl3,
	DwnLvl1,
	DwnLvl2,
	DwnLvl3,
	Finished
};

struct ClimberOutput {
	int motor; // 0 == Off; 1 == Forward; -1 == Reverse;
	ClimberOutput ();
	ClimberOutput (int a);
};	

ClimberOutput climberReturnOut (ClimberState climberInput);
ClimberState nextState (ClimberState currentState, bool TopLim, bool BotLim, bool btn);

#endif 
