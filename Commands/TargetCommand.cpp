// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"
#include <math.h>

// ReadCamera returns true if we've received a new camera frame.
//   init - set m_d2Offset and d_deltaOffset to 0, so we start from a known state.
bool TargetCommand::ReadCamera(bool init) 
{
    int frame     = (int) SmartDashboard::GetNumber("frameNum");
    bool newframe = frame > m_cameraFrame;

    if (newframe) {
        int newHeight = (int) (SmartDashboard::GetNumber("height") + 0.5);
        int newWidth  = (int) (SmartDashboard::GetNumber("width") + 0.5);
        int newOffset = (int) (SmartDashboard::GetNumber("offset") + 0.5);

        double ft = Timer::GetFPGATimestamp();

        if (init) {
            m_d2Offset = 0;
            m_deltaOffset = 0;
            m_fps = 10;
        }
        else {
            int newdeltaOffset = newOffset - m_tgtOffset;
        
            m_d2Offset = m_deltaOffset - newdeltaOffset;
            m_deltaOffset = newdeltaOffset;
            m_fps = 1.0 / (ft - m_lastFrameTime);
        }

        m_cameraFrame = frame;
        m_tgtOffset = newOffset;
        m_tgtWidth  = newWidth;
        m_tgtHeight = newHeight;
        m_lastFrameTime = ft;
        
        printf("+++ newframe %d offset %d frame %d fps %g\n", newframe, m_tgtOffset, frame, m_fps);
        // these printf's can upset the delicate timing balance, so caution is advised
        // printf("+++ newframe %s, doffset %d d2offset %d\n", newframe ? "true" : "false", m_deltaOffset, m_d2Offset);
    }

    return newframe;
}

// return show long we've been aiming
double TargetCommand::AimTime() 
{
    return (Timer::GetFPGATimestamp() - m_startAimTime);
}

// TimeDone returns true when we've run out of time...
bool TargetCommand::TimeDone() 
{
    return (AimTime() >= MAX_AIM_TIME);
}

// Identify resources required by this command.
// Other commands that are using these resources will be Canceled
// when this command is Started.
TargetCommand::TargetCommand() 
{
    Requires(Robot::driveBase());

    SmartDashboard::PutNumber("kMaxPower", 0.500);
    SmartDashboard::PutNumber("kMinPower", 0.350);
    SmartDashboard::PutNumber("kMinPowerOffset", 100.0);

    SmartDashboard::PutNumber("frameNum", 0.0);
    SmartDashboard::PutNumber("height", 0.0);
    SmartDashboard::PutNumber("width",  0.0);
    SmartDashboard::PutNumber("offset", 0.0);
    SmartDashboard::PutNumber("aimExCycles", 0.0);
    SmartDashboard::PutNumber("aimFrames", 0.0);
    SmartDashboard::PutNumber("aimTime", 0.0);
    
    SmartDashboard::PutBoolean("aiming", false);
}

// Called just before this Command runs the first time
void TargetCommand::Initialize()
{
    printf("TargetCommand::Initialize\n");

    // let the world know that somebody pushed the button 
    SmartDashboard::PutBoolean("aiming", true);
    
    m_startAimTime   = Timer::GetFPGATimestamp();
    m_kMaxPower      = SmartDashboard::GetNumber("kMaxPower");
    m_kMinPower      = SmartDashboard::GetNumber("kMinPower");
    m_kMinPowerOffset = SmartDashboard::GetNumber("kMinPowerOffset");

    ReadCamera(true);
  
    m_tgtOffset = 0;
    m_aimExCycles = 0;
    m_aimFrames   = 0;
    m_cameraFrame = -1;
    m_done = false;  

    m_timedmode = false;
    m_timedStart = 0;
    m_timedDuration = 0;
}

// Called repeatedly when this Command is scheduled to run
void TargetCommand::Execute()
{
    // printf("TargetCommand::Execute\n");
    
    m_aimExCycles++;

    if (m_timedmode) {
        if ((Timer::GetFPGATimestamp() - m_timedStart) >= m_timedDuration) {
            m_done = true;
            Robot::driveBase()->Drive3(0.0, 0.0, 0.0);  // so, stop already...
        }
    }
    else if (ReadCamera(false)) { // we have a new frame
        m_aimFrames++;

        if (m_tgtHeight <= 1.0 || m_tgtWidth <= 1.0) {
            // if we've lost the target, give up!
            m_done = true;
        } 
        else {
            // double angle = CAMERA_FOV * ((double) m_tgtOffset / IMAGE_WIDTH);
            float twist;
            int absoffset = abs(m_tgtOffset);

            if ((absoffset > m_kMinPowerOffset) || (m_aimExCycles < 4))
                twist = (m_tgtOffset < 0) ? -m_kMaxPower : m_kMaxPower;  
            else
                twist = (m_tgtOffset < 0) ? -m_kMinPower : m_kMinPower;  

            // printf("+++ angle %g twist %g doffset %d time %g\n", angle, twist, m_deltaOffset, AimTime());

            if (absoffset < AIM_MIN) { 
                m_done = true;  // we need to stop
                printf("offset %d - done\n", m_tgtOffset);

                Robot::driveBase()->Drive3(0.0, 0.0, 0.0);  // so, stop already...
            }
            else {
                if (absoffset < TIMED_OFFSET) {
                    // switch to timed drive
                	m_timedmode = true;
                    m_timedStart = Timer::GetFPGATimestamp();
                    // m_timedDuration = fabs((((double) m_tgtOffset) / ((double)m_deltaOffset)) * .9) / m_fps;
                    m_timedDuration = .08 * ((double)absoffset) / ((double) TIMED_OFFSET);
                    
                    printf("timed mode start duration %g\n", m_timedDuration);
                }
                
                Robot::driveBase()->Drive3(0.0, 0.0, twist);  // keep going
            }
        }
    }
}

bool TargetCommand::IsFinished()
{
    if (m_done || TimeDone()) {
         return true;
    }
    else
        return false;
}

// Called once after IsFinished returns true
void TargetCommand::End()
{
    Robot::driveBase()->Drive3(0.0, 0.0, 0.0);  // make sure 

    double tm = AimTime();

	printf("TargetCommand::End time %g\n", tm);

    ReadCamera(true);  // one last time, just to report 

    printf("+++ offset %d frame %d\n", m_tgtOffset, m_cameraFrame);

    SmartDashboard::PutBoolean("aiming", false);
    SmartDashboard::PutNumber("aimExCycles", m_aimExCycles);
    SmartDashboard::PutNumber("aimFrames", m_aimFrames);
    SmartDashboard::PutNumber("aimTime", tm);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TargetCommand::Interrupted()
{
    printf("TargetCommand::Interrupted\n");
}
