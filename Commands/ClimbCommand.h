// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef CLIMB_COMMAND_H
#define CLIMB_COMMAND_H

#include <Commands/Command.h>

class ClimbCommand : public Command
{
public: 
    ClimbCommand();
    ~ClimbCommand();
    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void Stop();
    virtual void Interrupted();
};

#endif
