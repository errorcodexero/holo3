// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef TARGETCOMMAND_H
#define TARGETCOMMAND_H

#include <Commands/Command.h>

#define CAMERA_FOV   45.0
#define IMAGE_WIDTH 640.0
#define MAX_AIM_TIME  4.00 // in seconds
#define AIM_MIN       20   // pixels
#define TIMED_OFFSET  60   // pixels

// TargetCommand extends TimedDrive to add new behavior

class TargetCommand: public Command  {
private:
    double m_kMaxPower;  // max power to apply while turning 
    double m_kMinPower;  // min power to apply while turning 
    double m_kMinPowerOffset; // angle to switch to min power
    double m_startAimTime;  
    int m_cameraFrame;   // frame number  - from camera
    int m_tgtHeight;     // target height - from camera
    int m_tgtWidth;      // target width  - from camera
    int m_tgtOffset;     // target offset - from camera
    int m_deltaOffset;   // change in offset between movements
    int m_d2Offset;      // change in deltaOffset between movements
    int m_aimFrames;     // #frames it took to aim
    int m_aimExCycles;   // counts Execute() calls
    bool m_done;         // true if we done been aimed
    bool m_timedmode;
    double m_timedStart;
    double m_timedDuration;
    double m_lastFrameTime;
    double m_fps;

    double AimTime();    // returns how long we've been aiming
    bool TimeDone();     // returns true if we've run out of time
    bool ReadCamera(bool init); // returns true if there's a new camera frame

public:
    TargetCommand();
    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();

    virtual void End();
    virtual void Interrupted();
};

#endif
