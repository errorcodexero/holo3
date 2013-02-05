// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef TARGETCOMMAND_H
#define TARGETCOMMAND_H

#include "TimedDrive.h"

// TargetCommand extends TimedDrive to add new behavior

class TargetCommand: public TimedDrive {
private:
    double m_kP, m_kT;
    int m_tgtHeight;
    int m_tgtWidth;
    int m_tgtOffset;

public:
    TargetCommand();
    virtual void Initialize();
    virtual void Execute();
    // virtual bool IsFinished();
    // virtual void End();
    // virtual void Interrupted();
};

#endif
