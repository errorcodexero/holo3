#include <cstdio>
#include <cstdlib>
#include "ClimberTest.h"

const char* getString (ClimberState );
void print(ClimberOutput printClimberOutput);

/*
int main() {
   
    ClimberState printedName;
    printedName = BothTillLim;
    getString(printedName);
    puts(getString(printedName)); 
   
    //printf("Hello World \n");
    print(climberReturnOut(BothTillLim ));
    ClimberState currentState;
    currentState = BothTillLim;
    //nextState (currentState, 1, 1, 1, 1, 1);
    //getString(nextState(currentState, 1, 1, 1, 1, 1));
    for (int loopTimes = 0; loopTimes < 10; loopTimes++){
    puts(getString(currentState));
    currentState = nextState(currentState, 1, 1, 1, 1, 1);
    puts(getString(currentState));
    }
    system ("PAUSE");

}
*/
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

//int ClimberPrint ( string ClimberPrintString) 
//             return  
//} 
