#include <WPILib.h>
#include "ClimberEnum.h"
#include "ClimberTest.h"
#include<relay.h>

class BuiltinDefaultCode : public IterativeRobot
{
public:

	// Driver station:
	DriverStation *m_ds;
	
	// Jaguar motor controller:
	//CANJaguar *m_mot1;
	
	//Victor
	Victor *m_mot1,*m_mot2;
	
	//ClimberState
	ClimberState m_state1;
	
	// Joystick:
	Joystick *m_joy1;
	Relay *m_compressor;
	
	// Digital Inputs:
	DigitalInput *m_lTop; // Top Left limit switch
	DigitalInput *m_lBot; // Bot Left limit switch
	DigitalInput *m_rTop; // Top Right Lim switch
	DigitalInput *m_rBot; // Bot Right Lim Switch
	DigitalInput *m_pressure;
	
	// Solenoid valve drivers:
	Solenoid *m_sol1;
	Solenoid *m_sol2;
	
	// Climber mechanism state:
	typedef enum { INVLD = 0, IDLE, UP, DOWN } climberState_t;
	climberState_t m_state;
			
    // Constructor:
	BuiltinDefaultCode()
	{
		printf("BuiltinDefaultCode Constructor Started\n");
				
		// Acquire the Driver Station object
		m_ds = DriverStation::GetInstance();
		
		// Construct new Jaguar controller (channel 6):
		UINT8 deviceNumber = 6;
		CANJaguar::ControlMode controlMode = CANJaguar::kPercentVbus;
		//m_ShooterWheel = new CANJaguar(deviceNumber, controlMode);
		
		m_mot1 = new Victor(7); //CANJaguar(6, controlMode);
		m_mot2 = new Victor(8);
		m_compressor=new Relay(1,Relay::kForwardOnly);
		m_joy1 = new Joystick(1);
	
		//convention from spreadsheet: front=bottom
		m_lTop = new DigitalInput(3);
		m_lBot = new DigitalInput(2);
		m_rTop = new DigitalInput(5);
		m_rBot = new DigitalInput(4);
		m_pressure=new DigitalInput(1);
		
		m_sol1 = new Solenoid(1);
		m_sol2 = new Solenoid(2);
		
		m_state = IDLE; // default state
		
		m_state1 = BothTillLim;
		
		printf("BuiltinDefaultCode Constructor Completed\n");
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
		ShowState("DisabledPeriodic", "Disabled 10:31");
	}
	
	void AutonomousPeriodic(void)
	{	

		// Set motor voltage to 95% of max:
		m_mot1->Set(95);

	}
	
	void TeleopPeriodic(void)
	{		
		Relay::Value v=m_pressure->Get()?(Relay::kOff):(Relay::kOn);
		//Relay::Value v=m_pressure->Get()?(Relay::kOn):(Relay::kOff);
		m_compressor->Set(v);
		//m_compressor->
		
		double f=m_joy1->GetRawAxis(1);
		m_sol1->Set(f<.5);
		
		// Read joystick buttons:
		bool button1 = m_joy1->GetRawButton(3);
		bool button2 = m_joy1->GetRawButton(5);
		bool button3 = m_joy1->GetRawButton(4);
		bool button4 = m_joy1->GetRawButton(6);
		
		// Read limit switches:
		bool lTop = !m_lTop->Get();  // pulled-up, so need to reverse
		bool lBot = !m_lBot->Get();  // ditto
		bool rTop = !m_rTop->Get();
		bool rBot = !m_rBot->Get();
				
		// State Change
		m_state1 = nextState (m_state1, rTop, lTop, rBot, lBot, button1, button2, button3);
			
		//Motor Output
		ClimberOutput motorValue = climberReturnOut(m_state1);
		
		//Based on the two motors mountings, they have to have opposite polarity to go the same direction.  
		m_mot1->Set(motorValue.motorL * 100);
		m_mot2->Set(motorValue.motorR * -100);
		
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
		sprintf (status_str, "%d %d %d %d %d %s %f ]",
				button1, lTop, lBot, rTop, rBot, getString(m_state1),f);
		
		ShowState("DisabledPeriodic", status_str);
		//Jaguar(1, 6).Set(100);
	}

};

START_ROBOT_CLASS(BuiltinDefaultCode);

