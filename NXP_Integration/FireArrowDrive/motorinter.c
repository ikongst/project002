
#include "motorinter.h"
#include "mlib.h"
#include "motor_structure.h"
#include "state_machine.h"
#include "PMSM_appconfig.h"


extern pmsmDrive_t         drvFOC;         //handler of control 
extern driveStates_t 		cntrState;     //handler of state


unsigned char Runcommand=0,directemp=0;         //Command state: 1=run  0=stop; direct state:0=prev  1=invt;
signed int  SpeedIN;                          //speed value input

unsigned int MotorDrive_uiVoltage;            //bus voltage measure
unsigned int MotorDrive_uiCurrent;         //bus current (raw)
signed int MotorDrive_uiTemperature;        //MCU temperature
signed int MotorDrive_uiTemperatureNTC_Digital;     //PCB temperature

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
short Mat_Ramp(short Input, int Slewrate, short *Output)
{
  int inp;
  int outp;
  outp = * Output;
  inp = Input << 16;

  if (inp > outp)
  {
    outp = outp + Slewrate;

    if (outp > inp)
    {
      outp = inp;
    }
  }
  else
  {
    outp = outp - Slewrate;

    if (outp < inp)
    {
      outp = inp;
    }
  }

  *Output = outp;
  return (outp >> 16);
}
int jytest,jitestTTTTspeed;
/*********input the required speed of motor**************/
extern unsigned int jycnt;
void MotorDrive_Regulation(unsigned int uispeedvalue,unsigned char direct)
{	
    MotorDrive_uiTargetSpeed=uispeedvalue;

    unsigned int frac16speed = ((long)((long)uispeedvalue<<15)/(unsigned int)N_MAX); //(((long)uispeedvalue<<15)/(unsigned int)N_MAX);
    if(!direct)
      SpeedIN = frac16speed;
	else
	  SpeedIN = frac16speed;//+0x8000;

	
//	
	if(MLIB_Abs_F16(SpeedIN))
	{
		drvFOC.pospeControl.wRotElReq=SpeedIN;
	  if(direct!=directemp)
	  	{
	       directemp = direct;                    //change the direct
	       cntrState.state   = reset;             //reset state
	       cntrState.event = e_reset;
	     Runcommand=1;                          //ready for run  again
	  	}
	  else 
	  	{
          if(drvFOC.pospeOpenLoop.wRotEl==0)
		  MotorDrive_Start();
	  	}	    
	  jitestTTTTspeed = drvFOC.pospeControl.wRotElReq;
	}
	else
	{
		if(MLIB_Abs_F16(drvFOC.pospeControl.wRotEl)>3276)
		{
			jytest = 1;
			if(jycnt > 20000)
			{
				jycnt = 0;
				Mat_Ramp(SpeedIN, 8000, &drvFOC.pospeControl.wRotElReq);
			}
		}
		else
		{
			//jytest = 2;
			MotorDrive_Stop();
		}
	}
	

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

#if 0
/*********input the required speed of motor**************/
void MotorDrive_Regulation(unsigned int uispeedvalue,unsigned char direct)
{	
    MotorDrive_uiTargetSpeed=uispeedvalue;

    unsigned int frac16speed = ((long)((long)uispeedvalue<<15)/(unsigned int)N_MAX); //(((long)uispeedvalue<<15)/(unsigned int)N_MAX);
    if(!direct)
      SpeedIN = frac16speed;
	else
	  SpeedIN = frac16speed;//+0x8000;

	drvFOC.pospeControl.wRotElReq=SpeedIN;
	
	if(MLIB_Abs_F16(SpeedIN))
	{
	  if(direct!=directemp)
	  	{
	       directemp = direct;                    //change the direct
	       cntrState.state   = reset;             //reset state
	       cntrState.event = e_reset;
	     Runcommand=1;                          //ready for run  again
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
#endif

