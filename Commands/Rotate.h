// First Team 1425 "Error Code Xero"
// for FRC 2013 game "Ultimate Ascent"

#ifndef ROTATE_H
#define ROTATE_H

#include <Commands/Command.h>

class Rotate: public Command {
private:
    double m_x, m_y, m_t, m_time;
    double m_startTime;
public:
    Rotate();
    void Set( double x, double y, double t, double seconds );
    virtual void Initialize();
    virtual void Execute();
    void Stop();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();
};

#endif
