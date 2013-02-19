// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef TARGETCOMMAND_H
#define TARGETCOMMAND_H

#include "TimedDrive.h"

#define MAX_AIM_TIME  3.00  // seconds
#define AIM_ANGLE_MIN  .05

// TargetCommand extends TimedDrive to add new behavior

class TargetCommand : public TimedDrive {
private:
    double m_kInitialP;  // initial power to apply while turning
    double m_kMovingP;   // power to apply while turning after moving
    double m_kT;         // time to apply power
    double m_startAimTime;  
    int m_tgtHeight;     // target height - from camera
    int m_tgtWidth;      // target width  - from camera
    int m_tgtOffset;     // target offset - from camera
    int m_deltaOffset;   // change in offset between movements
    int m_d2Offset;      // change in deltaOffset between movements
    bool m_done;         // true if we done been aimed
    bool m_moving;       // true if we're supposed to be moving

    double AimTime();       // returns how long we've been aiming
    bool TimeDone();     // returns true if we've run out of time
    bool ReadCamera(bool init); // returns true if we've moved

public:
    TargetCommand();
    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();

    // virtual void End();
    // virtual void Interrupted();
};

#endif
