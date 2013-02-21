#ifndef _TRIPLE_SOLENOID_H_
#define _TRIPLE_SOLENOID_H_

class TripleSolenoid : public DoubleSolenoid {
public:
    enum Position {
	kUnknown,
	kRetracted,
	kPartlyRetracted,
	kCenter,
	kPartlyExtended,
	kExtended,
    };

    TripleSolenoid( int forwardChannel, int reverseChannel,
    			   int switchChannel );
    virtual ~TripleSolenoid();
    void SetPosition( Position );
    Position GetPosition(void);
    void Start();
    void Stop();
    std::string GetSmartDashboardType() { return "3PS"; };

private:
    DigitalInput *m_switch;
    Position m_goal;
    Position m_position;
    DoubleSolenoid::Value m_direction;
    Notifier *m_notifier;
    static void TimerEvent( void *param );
    void Run(void);
};

#endif
