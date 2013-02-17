// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef OI_H
#define OI_H

#include "WPILib.h"


class OI {
private:
	Joystick* stick;
	JoystickButton* button1; //On Gamepad, is mapped to "A"
	JoystickButton* button2; //On Gamepad, is mapped to "B"
	JoystickButton* button3; //On Gamepad, is mapped to "X"
	JoystickButton* button4; //On Gamepad, is mapped to "Y"
	JoystickButton* button5; //On Gamepad, is mapped to "LeftBumper"
	JoystickButton* button6; //On Gamepad, is mapped to "RightBumper"
	JoystickButton* button7; //On Gamepad, is mapped to "Back"
	JoystickButton* button8; //On Gamepad, is mapped to "Start"
public:
	OI();
	Joystick* getStick() { return stick; }
	float GetDriverThrottle() { return stick->GetThrottle(); }
	// buttons 1-4 are mapped to commands
	// bool GetDriverButton1() {return button1->Get();}
	// bool GetDriverButton2() {return button2->Get();}
	// bool GetDriverButton3() {return button3->Get();}
	// bool GetDriverButton4() {return button4->Get();}
	bool GetDriverButton5() {return button5->Get();}
	bool GetDriverButton6() {return button6->Get();}
	bool GetDriverButton7() {return button7->Get();}
	bool GetDriverButton8() {return button8->Get();}
};

#endif
