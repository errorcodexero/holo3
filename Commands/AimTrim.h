#ifndef SELECT_TARGET_H
#define SELECT_TARGET_H

#include "../Robot.h"

class AimTrim: public Command {
public:
	
	bool m_left;
	
    AimTrim(bool left);
    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();
};

#endif
