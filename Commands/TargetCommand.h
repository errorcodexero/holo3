// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef TARGETCOMMAND_H
#define TARGETCOMMAND_H

#include "Commands/Command.h"

// This is the default command for the drive base:
// drive under joystick control.

class TargetCommand: public Command {
private:
    int m_tgtHeight;
    int m_tgtWidth;
    int m_tgtOffset;
    bool m_done;

public:
    TargetCommand();
    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();
};

#endif
