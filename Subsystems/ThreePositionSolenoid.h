#ifndef _THREE_POSITION_SOLENOID_H
#define _THREE_POSITION_SOLENOID_H

class ThreePositionSolenoid {
public:
    enum Position {
	kUnknown,
	kRetracted,
	kPartlyRetracted,
	kCenter,
	kPartlyExtended,
	kExtended,
    };

    ThreePositionSolenoid( int forwardChannel, int reverseChannel,
    			   int switchChannel );
    ~ThreePositionSolenoid();
    void Set( Position );
    Position Get(void);
    void Start();
    void Stop();

private:
    DoubleSolenoid *m_solenoid;
    DigitalInput *m_switch;
    Position m_goal;
    Position m_position;
    DoubleSolenoid::Value m_direction;
    Notifier *m_notifier;
    static void TimerEvent( void *param );
    void Run(void);
};

#endif
