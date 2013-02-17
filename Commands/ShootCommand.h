// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef SHOOT_COMMAND_H
#define SHOOT_COMMAND_H

#include <Commands/Command.h>

class ShootCommand: public Command {
public:
	ShootCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void Interrupted();
	virtual void End();
};

#endif
