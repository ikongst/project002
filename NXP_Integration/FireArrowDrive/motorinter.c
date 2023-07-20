
#include "motorinter.h"
#include "mlib.h"
#include "motor_structure.h"
#include "state_machine.h"

extern pmsmDrive_t         drvFOC;         //handler of control 
extern driveStates_t 		cntrState;     //handler of state


unsigned char Runcommand=0,directemp=0;         //Command state: 1=run  0=stop; direct state:0=prev  1=invt;
signed int  SpeedIN;                          //speed value input

unsigned int MotorDrive_uiVoltage;            //bus voltage measure
unsigned char MotorDrive_uiCurrent;         //bus current (raw)
unsigned int MotorDrive_uiTemperature;        //MCU temperature
unsigned int MotorDrive_uiTemperatureNTC_Digital;     //PCB temperature

signed int MotorDrive_uiTargetSpeed;        //required speed output
signed int MotorDrive_uiActualSpeed;        //actual speed output

unsigned int MotorDrive_MotorStatus;          //running state of motor

//driveStates_t *Addr_State;         //handler of state
//pmsmDrive_t *Addr_Foc;             //handler of control





/*****start the motor's running******/
void MotorDrive_Start(void)
{    
  cntrState.usrControl.btFlipFlop=0; 
  cntrState.usrControl.btFlipFlopTemp=1;
  Runcommand=1;
  
  cntrState.usrControl.switchFaultClear = true;
}


/*****stop the motor's running******/
void MotorDrive_Stop(void)
{
  cntrState.usrControl.btFlipFlop=1; 
  cntrState.usrControl.btFlipFlopTemp=0;
  Runcommand=0;
  
  cntrState.usrControl.switchFaultClear = true;
}

#include "PMSM_appconfig.h"
/*********input the required speed of motor**************/
void MotorDrive_Regulation(unsigned int uispeedvalue,unsigned char direct)
{	
    MotorDrive_uiTargetSpeed=uispeedvalue;

    long frac16speed = (((long)uispeedvalue<<15)/(unsigned int)N_MAX);
    if(!direct)
      SpeedIN = frac16speed;
	else
	  SpeedIN = frac16speed+0x8000;

	drvFOC.pospeControl.wRotElReq=SpeedIN;
	
	if(MLIB_Abs_F16(SpeedIN))
	{
	  if(direct!=directemp)
	  	{
	     directemp = direct;                    //change the direct
	     cntrState.state   = reset;                  //reset state
	     cntrState.event = e_reset;
	     Runcommand=1;                           //ready for run  again
	  	}
	  else 
	  	{
          if(drvFOC.pospeOpenLoop.wRotEl==0)
		  MotorDrive_Start();
	  	}	    
	}
	else
	MotorDrive_Stop();

	/*
	else if(drvFOC.pospeOpenLoop.wRotEl<SpeedIN)    //speed up 
	{
	   cntrState.usrControl.btSpeedUp=0;
	   cntrState.usrControl.btSpeedDown=1;
	  if(drvFOC.pospeOpenLoop.wRotEl==0)
	    MotorDrive_Start();	  
	}
	else if(drvFOC.pospeOpenLoop.wRotEl>SpeedIN)   //speed down 
	{
	   cntrState.usrControl.btSpeedUp=1;
	   cntrState.usrControl.btSpeedDown=0;
	  if(SpeedIN==0)
	    MotorDrive_Stop();
	}
	else                                             //do nothing
	{
		cntrState.usrControl.btSpeedUp=1;
		cntrState.usrControl.btSpeedDown=1;
	}
	*/
}


