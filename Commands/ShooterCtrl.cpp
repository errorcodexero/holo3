#include <WPILib.h>
#include "ClimberEnum.h"
#include "ClimberTest.h"
#include <relay.h>

#include<iostream>
//#include<vector>

using namespace std;

enum Climber_state{WAIT=0,TO_LIM,DOWN4,CLAW_GRASP,DOWN_TO_LIM,UP_TO_LIM,DOWN_TILL_CLAW_HIT,CLAW_RELEASE,CLIMB_ERROR};

string to_string(Climber_state a){
	switch(a){
		#define X(name) case name: return ""#name;
		X(WAIT)
		X(TO_LIM)
		X(DOWN4)
		X(CLAW_GRASP)
		X(DOWN_TO_LIM)
		X(UP_TO_LIM)
		X(DOWN_TILL_CLAW_HIT)
		X(CLAW_RELEASE)
		X(ERROR)
		#undef X
		default: return "invalid";
	}
}

ostream& operator<<(ostream& o,Climber_state a){ return o<<to_string(a); }
//vector<Climber_state> climber_states()

Climber_state next(Climber_state state,bool top_lim,bool bot_lim,bool go,double time_since_state_change,bool recover_up,bool recover_down){
	if(top_lim&&bot_lim) return CLIMB_ERROR;
	if(recover_up){
		if(state==0) return CLIMB_ERROR;
		return (Climber_state)((int)state-1);
	}
	if(recover_down){
		if(state==ERROR) return WAIT;
		return (Climber_state)((int)state+1);
	}
	switch(state){
		case WAIT:
			if(go) return TO_LIM;
			return WAIT;
		case TO_LIM:
			if(top_lim) return DOWN4;
			return TO_LIM;
		case DOWN4:
			if(time_since_state_change>2) return CLAW_GRASP;
			return DOWN4;
		case CLAW_GRASP:
			if(time_since_state_change>2) return DOWN_TO_LIM;
			return CLAW_GRASP;
		case DOWN_TO_LIM:
			if(bot_lim) return UP_TO_LIM;
			return DOWN_TO_LIM;
		case UP_TO_LIM:
			if(top_lim) return DOWN_TILL_CLAW_HIT;
			return UP_TO_LIM;
		case DOWN_TILL_CLAW_HIT:
			if(time_since_state_change>3) return CLAW_RELEASE;
			return DOWN_TILL_CLAW_HIT;
		case CLAW_RELEASE:
			if(time_since_state_change>2) return DOWN4;
			return CLAW_RELEASE;
		case ERROR:
			//if(recover_up) return UP_TO_LIM;
			//if(recover_down) return DOWN_TO_LIM;
			return CLIMB_ERROR;
		default:
			return CLIMB_ERROR;
	}
}

struct Climber_output{
	int motor; //-1=down, 0=stop, 1=up
	bool grasp;

	Climber_output(int a,bool b):motor(a),grasp(b){}
};

Climber_output get_output(Climber_state c){
	switch(c){
		case WAIT: return Climber_output(0,0);
		case TO_LIM: return Climber_output(1,0);
		case DOWN4: return Climber_output(-1,0);
		case CLAW_GRASP: return Climber_output(0,1);
		case DOWN_TO_LIM: return Climber_output(-1,1);
		case UP_TO_LIM: return Climber_output(1,1);
		case DOWN_TILL_CLAW_HIT: return Climber_output(-1,1);
		case CLAW_RELEASE: return Climber_output(0,0);
		case ERROR:
		default:
			return Climber_output(0,1);
	}
}

ostream& operator<<(ostream& o,Climber_output a){
	return o<<"Climber_output("<<a.motor<<" "<<a.grasp<<")";
}

void do_motor(int pwm,bool bot,bool top,int goal){
	if(top&&goal==1) goal=0;
	if(bot&&goal==-1) goal=0;
	cout<<"pwm"<<pwm<<"="<<goal;
}

void do_output(Climber_output out,bool lim_lb,bool lim_rb,bool lim_lt,bool lim_rt){
	cout<<"relay="<<out.grasp<<" ";
	do_motor(0,lim_lb,lim_lt,out.motor);
	cout<<" ";
	do_motor(1,lim_rb,lim_rt,out.motor);
}

int main(){
	Climber_state state=WAIT;
	bool lim_lb=0,lim_rb=0,lim_lt=1,lim_rt=1;
	for(unsigned i=0;i<10;i++){
		Climber_output out=get_output(state);
		cout<<to_string(state)<<"\t"<<out<<"\t";
		do_output(out,lim_lb,lim_rb,lim_lt,lim_rt);
		cout<<"\n";
		state=next(state,1,0,1,20,0,0);
	}
	for(unsigned i=0;i<5;i++){
		state=next(state,0,1,1,20,0,0);
		cout<<state<<"\n";
	}
}

class BuiltinDefaultCode : public IterativeRobot
{
public:

	// Driver station:
	DriverStation *m_ds;
	
	// Jaguar motor controller:
	CANJaguar *m_ShooterWheel;
	
	//Victor
	Victor *m_mot1,*m_mot2;
	
	//ClimberState
	ClimberState m_state1;
	
	// Joystick:
	Joystick *gamepad;
	//Joystick *switchboard;
	Relay *m_compressor;
	int m_climbtip; // 0 == all ports blocked, 1 == extended, -1 == retract;
	bool m_shoottip;
	
	Climber_state climber_state;
	double last_climber_state_change;
	
	// Digital Inputs:
	DigitalInput *m_lTop; // Top Left limit switch
	DigitalInput *m_lBot; // Bot Left limit switch
	DigitalInput *m_rTop; // Top Right Lim switch
	DigitalInput *m_rBot; // Bot Right Lim Switch
	DigitalInput *m_pressure;
	
	// Solenoid valve drivers:
	Solenoid *m_sol1;
	Solenoid *m_sol2;
	Solenoid *m_sol3;
	Solenoid *m_sol4,*m_sol5,*m_sol6;
	
	// Climber mechanism state:
	typedef enum { INVLD = 0, IDLE, UP, DOWN } climberState_t;
	climberState_t m_state;
			
    // Constructor:
	BuiltinDefaultCode():climber_state(WAIT)//:gamepad(1),switchboard(2)
	{
		printf("BuiltinDefaultCode Constructor Started\n");
				
		// Acquire the Driver Station object
		m_ds = DriverStation::GetInstance();
		//m_ds->
		// Construct new Jaguar controller (channel 6):
		UINT8 deviceNumber = 6;
		CANJaguar::ControlMode controlMode = CANJaguar::kPercentVbus;
		m_ShooterWheel = new CANJaguar(deviceNumber, controlMode);
		
		m_mot1 = new Victor(7); //CANJaguar(6, controlMode);
		m_mot2 = new Victor(8);
		m_compressor=new Relay(1,Relay::kForwardOnly);
		
		//m_joy1 = new Joystick(1);
		gamepad = new Joystick(1);
		//switchboard = new Joystick(2);
		
		//convention from spreadsheet: front=bottom
		m_lTop = new DigitalInput(3);
		m_lBot = new DigitalInput(2);
		m_rTop = new DigitalInput(5);
		m_rBot = new DigitalInput(4);
		m_pressure=new DigitalInput(1);
		
		m_sol1 = new Solenoid(1);
		m_sol2 = new Solenoid(2);
		m_sol3 = new Solenoid(3);
		m_sol4 = new Solenoid(4);
		m_sol5 = new Solenoid(5);
		m_sol6 = new Solenoid(6);
		
		m_state = IDLE; // default state
		
		m_state1 = InitIdle;
		
		m_climbtip = 0;
		m_shoottip = 0;
		
		printf("BuiltinDefaultCode Constructor Completed\n");
	}

	bool launchbutton() {
		//return switchboard->GetRawButton(6);
		return m_ds->GetDigitalIn(6);
	}
	
	bool climbbutton() {
		//return switchboard->GetRawAxis(1) > .5;
		return m_ds->GetAnalogIn(1) > 2.25;
	}
	bool climbresetbutton(){
		//return switchboard->GetRawAxis(1) < -.5;
		return m_ds->GetAnalogIn(1) < .75;
	} 
	int climb_dir(){
		double f=m_ds->GetAnalogIn(1);
		if(f>2.25) return 1;
		if(f<.75) return -1;
		return 0;
	}
	
	bool cameralight(){
		//return switchboard->GetRawButton(2);
		return m_ds->GetDigitalIn(2);
	}
	bool dump(){
		//return switchboard->GetRawButton(1);
		return m_ds->GetDigitalIn(1);
	}
	
	int getthreeposition(int axis){
		//float f = switchboard->GetRawAxis(axis);
		float f = m_ds->GetAnalogIn(axis);
		if (f > 2.25){
			return 1;
		}
		if (f > .75){
			return 0;
		}
		return -1;
	}
	
	int tipclimber(){
		return getthreeposition(2);
	}
	bool cameraview(){
		//return switchboard->GetRawButton(3);
		return m_ds->GetDigitalIn(3);
	}
	
	bool speedoverride(){
		//return switchboard->GetRawButton(5);
		return m_ds->GetDigitalIn(5);
	}
	
	int shooterposition(){
		return -getthreeposition(4);		
	}
	
	float speedknob(){
		//return switchboard->GetRawAxis(3);
		return 3.3 - m_ds->GetAnalogIn(3);
	}
	
	bool smallredbutton(){
		//return !switchboard->GetRawButton(4);
		return !m_ds->GetDigitalIn(4);
	}
	bool keyswitch(){
		//return !switchboard->GetRawButton(7);
		return !m_ds->GetDigitalIn(7);
	}
	
	
	void ShowState( const char *mode, const char *state )
	{
		DriverStationLCD *lcd = DriverStationLCD::GetInstance();
		lcd->PrintfLine(DriverStationLCD::kUser_Line1, mode);
		lcd->PrintfLine(DriverStationLCD::kUser_Line2, state);
		lcd->UpdateLCD();
	}
	
	/********************************** Init Routines *************************************/

	// Mealy state-machine:
	static climberState_t CalcNextState
    (
    		// inputs:
    		const climberState_t & cur_state, // current state
    		const bool           & button1,   // climb button
    		const bool           & limit1,    // top limit switch
    		const bool           & limit2     // bot limit switch
    )
	{
		climberState_t nxt_state = INVLD;
		
		switch(cur_state)
		{
		case(IDLE):
		    nxt_state = (button1) ? UP : IDLE; 
			break;
		case(UP):
		    nxt_state = (!button1) ? IDLE : (limit1) ? DOWN : UP; 
			break;
		case(DOWN):
		    nxt_state = (!button1) ? IDLE : (limit2) ? UP : DOWN; 
			break;
		default:
		case(INVLD):
			nxt_state = IDLE; 
			break;
		}
		
		return nxt_state;
	}

	void RobotInit(void)
	{
		ShowState("RobotInit", "Disabled");
	}
	
	void DisabledInit(void)
	{
		ShowState("DisabledInit", "Disabled");
	}

	void AutonomousInit(void)
	{
		ShowState("AutonomousInit", "Autonomous");
	}

	void TeleopInit(void)
	{
		ShowState("TeleopInit", "Teleoperated");
	}

	/********************************** Periodic Routines *************************************/
	
	void DisabledPeriodic(void)
	{
		ShowState("DisabledPeriodic", "Disabled 10:32");
	}
	
	void AutonomousPeriodic(void)
	{	
		char status_str[80]; 
		sprintf (status_str, "%d %d %d %d %d]",
				cameralight(), dump(), cameraview(), speedoverride(), smallredbutton());
		
		ShowState("DisabledPeriodic", status_str);
		

	}
	
	void TeleopPeriodic(void)
	{		
		Relay::Value v=m_pressure->Get()?(Relay::kOff):(Relay::kOn);
		//Relay::Value v=m_pressure->Get()?(Relay::kOn):(Relay::kOff);
		m_compressor->Set(v);
		//m_compressor->
		
		//Tipping for Shooter
		if (tipclimber() == 1){
			m_climbtip = 1;
		}
		if (tipclimber() == -1){
			m_climbtip = -1;
		}
		
		m_sol1->Set(m_climbtip == 1);
		m_sol2->Set(m_climbtip == -1 );

		//making this claw for now.
		if(cameraview()){
			m_sol5->Set(1);
			m_sol5->Set(0);
		}else{
			m_sol5->Set(0);
			m_sol5->Set(1);
		}
		
		//Tipping for Climber
		if (shooterposition() == 1){
			m_shoottip = 1;
		}	
		if (shooterposition() == -1){
			m_shoottip = 0;
		}
				
		m_sol3->Set(m_shoottip == 1);
		
		//Injector
		m_sol4->Set(launchbutton());
		
		//ShooterWheel Volt Control
		if (speedoverride()) {
		m_ShooterWheel->Set(speedknob() * 100 / 3.3);
		}
		else m_ShooterWheel->Set(0);
		// Read joystick buttons:
		bool button1 = climbbutton();
		bool button2 = climbresetbutton();
		bool button3 = 0;
		
		// Read limit switches:
		bool lTop = !m_lTop->Get();  // pulled-up, so need to reverse
		bool lBot = !m_lBot->Get();  // ditto
		bool rTop = !m_rTop->Get();
		bool rBot = !m_rBot->Get();
				
		// State Change
		m_state1 = nextState (m_state1, rTop, lTop, rBot, lBot, button1, button2, button3);
		double now=0;//getMsClock()/1000.0;
		double time_since_change=last_climber_state_change-now;
		Climber_state next_climber_state=next(climber_state,rTop&&lTop,rBot&&lBot,button1,time_since_change,button2,button3);
		if(climber_state!=next_climber_state){
			last_climber_state_change=now;
		}
		climber_state=next_climber_state;
		Climber_output out=get_output(climber_state);

		//doing manual override
		out.motor=climb_dir();
		
#define SETMOT(var,TOP,BOT) { \
			int goal=out.motor;\
			if(TOP && goal==1) goal=0;\
			if(BOT && goal==-1) goal=0;\
			var->Set(goal*100);}
		SETMOT(m_mot1,lTop,lBot);
		SETMOT(m_mot2,rTop,rBot);
#undef SETMOT
		
		//Motor Output
		ClimberOutput motorValue = climberReturnOut(m_state1);
		
		//Based on the two motors mountings, they have to have opposite polarity to go the same direction.  
		//m_mot1->Set(motorValue.motorR * 100);
		//m_mot2->Set(motorValue.motorL * 100);
		
		//m_mot2->Set(m_joy1->GetY() * 100);
		
		// Test out the climbing mechanism:

		// Mealy state-machine:
		/*climberState_t nxt_state = CalcNextState 
		(
	    		// inputs:
	    		m_state, // current state
	    		button1, // climb button
	    		limit1,  // top limit switch
	    		limit2   // bot limit switch
	    );
	    
		// state transition:
		m_state = nxt_state;
		*/
		 
				
				
		//UINT8 status = 4*m_state | 2*limit2 | limit1;

		char status_str[80]; 
		sprintf (status_str, "%d %d %d %d %d %s]",
				button1, lTop, lBot, rTop, rBot, getString(m_state1));
		
		//sprintf (status_str, "%d %d %d %d %d %f]",
		//				launchbutton(), climbbutton(), climbresetbutton(), tipclimber(), shooterposition(), speedknob());
				
		ShowState("DisabledPeriodic", status_str);
		//Jaguar(1, 6).Set(100);
	}
};

START_ROBOT_CLASS(BuiltinDefaultCode);

