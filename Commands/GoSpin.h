// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef GOSPIN_H
#define GOSPIN_H

#include <Commands/Command.h>

class GoSpin: public Command {
public:
	GoSpin();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
