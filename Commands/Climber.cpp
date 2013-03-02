#include "Climber.h"
#include <cstdio>
#include <cstdlib>

ClimberMotorOut climberReturnOutSingle (ClimberStateSingle climberInput) {
	switch (climberInput ){
		case TillLim: return 1;
		case SingleUpIdle: return 0;
		case SingleDwnIdle: return 0;
		case GoingUp: return 1;
		case GoingDwn: return -1;
		case SingleErrorState: return 0;
        default: return 0;
	}
}

ClimberStateSingle nextStateSingle (ClimberStateSingle currentState, bool TopLim, bool BotLim, bool btn, bool errorbtnDwn, bool errorbtnUp) {
	if (TopLim && BotLim) return SingleErrorState;
    switch (currentState){
		case TillLim: 
			if (TopLim) return SingleDwnIdle;
			return currentState;
		case SingleUpIdle:
			if (btn) return GoingUp;
			return currentState;
		case GoingUp:
			if (!btn) return SingleUpIdle;
			if (TopLim) return GoingDwn;
			return currentState;
		case SingleDwnIdle:
			if (btn) return GoingDwn;
			return currentState;
		case GoingDwn:
			if (!btn) return SingleDwnIdle;
			if (BotLim) return GoingUp;
			return currentState;
		case SingleErrorState:
            if (errorbtnUp)return SingleUpIdle;
            if (errorbtnDwn) return SingleDwnIdle;
            return currentState;          
		default: return SingleErrorState;
	}	

}
//Code for climberTest
const char* getStringSingle (ClimberStateSingle );
void printSingle(ClimberMotorOut printClimberMotorOut);

void printPrintSingle(ClimberMotorOut n) {
    printf("motor = %d", n);
}

const char* getStringSinlge (ClimberStateSingle variName) {
    switch (variName) {
           case TillLim: return "TillLim";       
           case SingleUpIdle: return "UpIdle";
           case SingleDwnIdle: return "DwnIdle";
           #define X(name) case name: return ""#name;
           X (GoingUp)
           X (GoingDwn)
           X (SingleErrorState)
           default: return "Undefined";
           #undef X 
    } 
}
