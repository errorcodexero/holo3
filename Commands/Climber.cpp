#include <cstdio>
#include <cstdlib>
#include "Climber.h"
	
ClimberOutput::ClimberOutput() {
}
ClimberOutput::ClimberOutput(int a, int b) {
	motorL = a, motorR = b;
}
		
ClimberOutput climberReturnOut (ClimberState climberInput) {
	switch (climberInput ){
		case BothTillLim: return ClimberOutput(1,1);
		case LTillLim: return ClimberOutput(1,0);
		case RTillLim: return ClimberOutput(0,1);
		case UpIdle: return ClimberOutput(0,0);
		case DwnIdle: return ClimberOutput(0,0);
		case BothGoingUp: return ClimberOutput(1,1);
		case LeftGoingUp: return ClimberOutput(1,0);
		case RightGoingUp: return ClimberOutput(0,1);
		case LUpIdle: return ClimberOutput(0,0);
		case RUpIdle: return ClimberOutput(0,0);
		case BothGoingDwn: return ClimberOutput(-1,-1);
		case LeftGoingDwn: return ClimberOutput(-1,0);
		case RightGoingDwn: return ClimberOutput(0,-1);
		case LDwnIdle: return ClimberOutput(0,0);
		case RDwnIdle: return ClimberOutput(0,0);
		case ErrorState: return ClimberOutput(0,0);
		default: return ClimberOutput(0,0);
	 }
}
	 
 ClimberState nextState (ClimberState currentState, bool rTopLim, bool lTopLim, bool rBotLim, bool lBotLim, bool btn, bool errorBtnUp, bool errorBtnDwn) {
		if ((lTopLim && lBotLim) || (rTopLim && rBotLim)) return ErrorState;
		switch (currentState){
			case BothTillLim:
				if (lTopLim && rTopLim) return DwnIdle;
				if (rTopLim) return LTillLim;
				if (lTopLim) return RTillLim;
				return currentState;
			case LTillLim:
				if (lTopLim) return DwnIdle;
				return currentState;
			case RTillLim:
				if (rTopLim) return DwnIdle;
				return currentState;
			case UpIdle:
				if (btn) return BothGoingUp;
				return currentState;
			case BothGoingUp:
				if (!btn) return UpIdle;
				if (lTopLim && rTopLim) return BothGoingDwn;
				if (rTopLim) return LeftGoingUp;
				if (lTopLim) return RightGoingUp;
				return currentState;
			case LeftGoingUp:
				if (!btn) return LUpIdle;
				if (lTopLim) return BothGoingDwn;
				return currentState;
			case LUpIdle:
				if (btn) return LeftGoingUp;
				return currentState;
			case RightGoingUp:
				if (!btn) return RUpIdle;
				if (rTopLim) return BothGoingDwn;
				return currentState;
			case RUpIdle:
				if (btn) return RightGoingUp;
				return currentState;
			case DwnIdle:
				if (btn) return BothGoingDwn;
				return currentState;
			case BothGoingDwn:
				if (!btn) return DwnIdle;
				if (lBotLim && rBotLim) return BothGoingUp;
				if (rBotLim) return LeftGoingDwn;
				if (lBotLim) return RightGoingDwn;
				return currentState;
			case LeftGoingDwn:
				if (!btn) return LDwnIdle;
				if (lBotLim) return BothGoingUp;
 				return currentState;
			case RightGoingDwn:
				if (!btn) return RDwnIdle;
				if (rBotLim) return BothGoingUp;
				return currentState;
			case LDwnIdle:
				if (btn) return LeftGoingDwn;
				return currentState;
			case RDwnIdle:
				if (btn) return RightGoingDwn;
				return currentState;
			case ErrorState:
				if (errorBtnUp)return UpIdle;
				if (errorBtnDwn) return DwnIdle;
				return currentState;
 			default: return ErrorState;
	}
}

//ClimberTest
const char* getString (ClimberState );
void print(ClimberOutput printClimberOutput);

void print(ClimberOutput n) {
    printf("motorL = %d, motorR = %d\n" ,n.motorL ,n.motorR);
}

const char* getString (ClimberState variName) {
    switch (variName) {
           case BothTillLim: return "BothTillLim";       
           case LTillLim: return "LTillLim";
           case RTillLim: return "RTillLim";
           case UpIdle: return "UpIdle";
           case DwnIdle: return "DwnIdle";
           #define X(name) case name: return ""#name;
           X (BothGoingUp)
           X (LeftGoingUp)
           X (RightGoingUp)
           X (LUpIdle)
           X (RUpIdle)
           X (BothGoingDwn)
           X (LeftGoingDwn)
           X (RightGoingDwn)
           X (LDwnIdle)
           X (RDwnIdle)
           X (ErrorState)
           default: return "Undefined";
           #undef X 
    } 
}
