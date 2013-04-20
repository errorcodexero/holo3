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


#define NUM_MODES 9
#define NUM_MOVES 6
#define NUM_VALUES 4

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
	
    TimedDrive *m_firstMove;
    TimedDrive *m_secondMove;
    TimedDrive *m_thirdMove;
    TimedDrive *m_fourthMove;
    TimedDrive *m_fifthMove;
    TimedDrive *m_sixthMove;

    char* m_SDLabels[NUM_MODES][NUM_MOVES][NUM_VALUES];
    double m_modes[NUM_MODES][NUM_MOVES][NUM_VALUES];
    int m_autoModeKnob;
    
    double m_defaultValues[NUM_MODES][NUM_MOVES][NUM_VALUES];

};   
#endif
