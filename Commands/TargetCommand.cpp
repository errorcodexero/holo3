// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#include "Robot.h"
#include <math.h>

// ReadCamera returns true if we've moved.
//   init - set m_d2Offset and d_deltaOffset to 0, so we start from a known state.
bool TargetCommand::ReadCamera(bool init) 
{
    int newHeight = (int)(SmartDashboard::GetNumber("height") + 0.5);
    int newWidth  = (int)(SmartDashboard::GetNumber("width") + 0.5);
    int newOffset = (int)(SmartDashboard::GetNumber("offset") + 0.5);
    bool moved;

    if (init) {
        m_d2Offset = 0;
        m_deltaOffset = 0;
        moved = false;
    }
    else {
        int newdeltaOffset = newOffset - m_tgtOffset;
        
        m_d2Offset = m_deltaOffset - newdeltaOffset;
        m_deltaOffset = newdeltaOffset;

        // camera offset value only accurate to a few pixels per frame, dang...
        moved = fabs(newOffset - m_tgtOffset) >= 2;  
    }

    m_tgtOffset = newOffset;
    m_tgtWidth  = newWidth;
    m_tgtHeight = newHeight;

    printf("+++ offset %d width %d height %d +++\n", m_tgtOffset, m_tgtWidth, m_tgtHeight);
    printf("+++ moved %s, doffset %d d2offset %d +++\n", moved ? "true" : "false", m_deltaOffset, m_d2Offset);
    
    return moved;
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
TargetCommand::TargetCommand() : TimedDrive( 0.0, 0.0, 0.0, 0.0 )
{
    // TimedDrive Requires(Robot::driveBase());
    SmartDashboard::PutNumber("kInitialP", 0.100);
    SmartDashboard::PutNumber("kMovingP", 0.100);
    SmartDashboard::PutNumber("kT", 0.050);   // roughly matches our 10fps camera rate

    SmartDashboard::PutNumber("height", 0.0);
    SmartDashboard::PutNumber("width",  0.0);
    SmartDashboard::PutNumber("offset", 0.0);
}

// Called just before this Command runs the first time
void TargetCommand::Initialize()
{
    printf("TargetCommand::Initialize\n");

    m_startAimTime = Timer::GetFPGATimestamp();
    m_kInitialP = SmartDashboard::GetNumber("kInitialP");
    m_kMovingP  = SmartDashboard::GetNumber("kMovingP");
    m_kT        = SmartDashboard::GetNumber("kT");
    
    ReadCamera(true);

    m_moving = false;
    m_done   = false;  // that's why we're here
}

// Called repeatedly when this Command is scheduled to run
void TargetCommand::Execute()
{
    printf("TargetCommand::Execute\n");
    
    if (!m_done) {
        ReadCamera(true);

        if (m_moving) {
            // let the motor spin already
            m_moving = !TimedDrive::IsFinished();

            printf("--- still moving, offset %d, time %g\n", m_tgtOffset, AimTime());
        }
        else {  // 
            if (m_tgtHeight <= 1.0 || m_tgtWidth <= 1.0) {
                // if we've lost the target, give up!
                m_done = true;
            } 
            else {
            	// not actually the true angle, but a reasonable proxy
                double angle = (double) m_tgtOffset / (double) m_tgtWidth;
                float twistpower = ((angle < 0) ? -m_kMovingP : m_kMovingP);  // how hard to twist
                float secs  = m_kT;   // how long to twist

                printf("+++ angle %g twist %g time %g time %g\n", angle, twistpower, secs, AimTime());

                if (fabs(angle) < AIM_ANGLE_MIN) { 
                    m_done = true;  // we can't get any closer

                    Set(0.0, 0.0, 0.0, 0.0);  // so, stop already...
                }
                else {
                    Set(0.0, 0.0, twistpower, secs);

                    m_moving = true;
                }

                TimedDrive::Execute();  // actually tell the motors to spin, or not
            }
        }
    }
}

bool TargetCommand::IsFinished()
{
    if (m_done || TimeDone()) {
    	printf("TargetCommand::IsFinished time %g\n", AimTime());

        Set(0.0, 0.0, 0.0, 0.0);  // stop already...
 
        ReadCamera(true);  // one last time, just to report 

        return true;
    }
    else
        return false;
}
