// FIRST Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef SELECT_TARGET_H
#define SELECT_TARGET_H

#include <Commands/Command.h>

class SelectTarget: public Command {
private:
    const char* m_targetName; 

public:
    SelectTarget(const char* targetName);
    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();
};

#endif
