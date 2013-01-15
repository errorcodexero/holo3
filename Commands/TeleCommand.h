// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef TELECOMMAND_H
#define TELECOMMAND_H

#include "Commands/CommandGroup.h"

// This command group is started whenever the robot enters teleoperated mode
// and canceled when the robot enters any other mode.

class TeleCommand: public CommandGroup {
public:	
	TeleCommand();
};

#endif
