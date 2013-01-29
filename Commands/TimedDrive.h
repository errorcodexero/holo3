// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef TIMED_DRIVE_H
#define TIMED_DRIVE_H

#include "Commands/Command.h"

class TimedDrive: public Command {
private:
    double m_cycleTime;
    double m_startTime;
public:
    TimedDrive( float seconds );
    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();
};

#endif
