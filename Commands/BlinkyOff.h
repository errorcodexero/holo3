#ifndef BLINKY_OFF_H
#define BLINKY_OFF_H

#include "Robot.h"

class BlinkyOff: public Command {
public:
    BlinkyOff();
    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();
};

#endif
