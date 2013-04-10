// FIRST Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef AUTOCOMMAND_H
#define AUTOCOMMAND_H

#include <Commands/Command.h>
#include <Commands/CommandGroup.h>

#define PRIGHT_FRIGHT 1
#define PRIGHT_FMID   2
#define PRIGHT_FLEFT  3
#define PMID_FRIGHT   4
#define PMID_FMID     5
#define PMID_FLEFT    6
#define PLEFT_FRIGHT  7
#define PLEFT_FMID    8
#define PLEFT_FLEFT   9

// This command group is started whenever the robot enters autonomous mode
// and canceled when the robot enters any other mode.

class BlinkyBreathe;
class TiltCommand;
class TargetCommand;
class ShootCommand;
class TimedDrive;

class AutoCommand: public CommandGroup {
public:	
    AutoCommand();
    virtual ~AutoCommand();
    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();

private:
    BlinkyBreathe *m_blinky;
    TiltCommand *m_tilt;
    TargetCommand *m_target;
    ShootCommand *m_shoot;
    TimedDrive *m_left;
    TimedDrive *m_right;
    TimedDrive *m_back;
    TimedDrive *m_brake;
    TimedDrive *m_halfBack;
    TimedDrive *m_longLeft;
    TimedDrive *m_longRight;
    TimedDrive *m_shortLeft;
    TimedDrive *m_shortRight;
};

#endif
