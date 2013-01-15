#ifndef BLINKY_ON_H
#define BLINKY_ON_H

#include "Robot.h"

class BlinkyOn: public Command {
private:
    Timer m_onTimer;

public:
    BlinkyOn();
    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();
};

#endif
