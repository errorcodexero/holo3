// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick* stick;
	JoystickButton* button2;
	
public:
	OI();
	Joystick* getStick();
	float GetDriverThrottle() { return stick->GetThrottle(); }
	bool GetDriverButton2() {return button2->Get();}
};

#endif
