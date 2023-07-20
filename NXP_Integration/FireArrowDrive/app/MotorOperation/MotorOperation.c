#include "MotorOperation.h"
#include "CustomerInterface.h"
#include "Protection.h"
#include "Common.h"
#include "BSW.h"
#include "DataLog.h"
#include "ProjectConfig.h"

unsigned int guiSpeedSet               = INIT;
unsigned char gucMotorDriveState       = INIT;
unsigned char gucMotorDriveStartupTime = INIT;
unsigned char gucFOCError              = INIT;

void stopmotor();
void startmotor();
void speedregulation();
void checksleepmode(void);
void gotosleedmode(void);



void stopmotor()
{
	// stop
	BSW_MotorStop();
	
	guiSpeedSet = INIT;
}

void startmotor()
{	
	// start
	if(guiControlSpeed!=0)
	{
		BSW_MotorStart();
		guiSpeedSet = guiControlSpeed;
	}
}

void speedregulation()
{
	// based on:
	//     control speed
	//     maxspeed
	if(guiControlSpeed>guiMaxSpeedCalculated)
	{
		guiControlSpeed = guiMaxSpeedCalculated;
	}	
	
	// set new speed:
	BSW_MotorRegulation(guiControlSpeed);
	guiSpeedSet = guiControlSpeed;
}

STATEMACHINE gMotorControl = IDEA;
static unsigned int suidelaycounter_Idea = INIT;
static unsigned int suidelaycounter_Stop = INIT;

#include "CustomerInterface.h"
void checksleepmode(void)
{
	#if PAR_CUSTOMERINTERFACE_SELECTION == CUSTOMERINTERFACE_LIN
		//l_set_current_NAD(0x11);
		//l_set_initial_NAD(0x01);
		if(vAPPLLinCheckSleep()==FLAG_SET)
		{
			gucLINGotoSleepFlag = FLAG_SET; 
		}
	#else
	
		// check KL15
	  // check pwm pin as high
		// mode as idea
		if(
			  (gMotorControl==IDEA)
			#if SYSTEMPARAM_ENABLE_KL15_HAVE == KONGENABLE
			&&(gucPINKL15EnableStatus==PINSTATUS_LOW)
		  #endif
			&&(   ((gucHighLowStatus==HIGHLOW_HIGH)&&(SPEEDCURVETABLE_CUSTOMER[SPEEDCURVETABLE_MAXID]==INIT))
					||((gucHighLowStatus==HIGHLOW_LOW)&&(SPEEDCURVETABLE_CUSTOMER[SPEEDCURVETABLE_MINID]==INIT))
				)
			&&(gucLINEOLServiceReceivedFlag!= FLAG_SET)
			&&(gucLINGotoSleepFlag==FLAG_RESET)
			)
		{
			gucLINGotoSleepFlag = FLAG_SET; 
		}		
	#endif
}

void gotosleedmode(void)
{
	if(gucLINGotoSleepFlag==FLAG_SET)
	{
		stopmotor();
		gucPINInterfacePullDownStatus  = PULLDOWN_RELEASE;
		BSW_setpinstatus_interface(PULLDOWN_RELEASE);	

		if((gMotorControl==IDEA)
		//&&(guiActualSpeed<LIMIT_SPEED_MIN_rpm))
		&&(guiActualSpeed<=INIT))
		{
			// do some actions when entered into sleepmode.
			starttimebaserecording();
			startspeedstatusrecording();
			startinternalerrorrecording();
			
			
			gucLINGotoSleepFlag =FLAG_RESET;		
			
			
			// last check the KL15 status.
			if(gucPINKL15EnableStatus==PINSTATUS_LOW)
			{
				EnterintoSleep();	
				return;
			}
		}		
	}
}

void MotorOperation_Main(void)
{	
	// sleep mode check and implement.
	checksleepmode();	
	gotosleedmode();	
	
	gucMotorDriveState       = 1;//ucgetEMOState();// this state show the motor running or stop;
	gucMotorDriveStartupTime = 0;
	
	gucFOCError              = 0;//ucgetFOCerror();// indicate to FOC agloristhm.
		
	switch(gMotorControl)
	{
		case IDEA:
			if(guiControlSpeed==INIT)
			{
				// clear any flags when speed set as INIT=0.
				gucOneBlockedFlag             = NOERROR;
				gucOneOverloadFlag            = NOERROR;
			}

			if(suidelaycounter_Idea)
			{
				suidelaycounter_Idea--;
			}
			else
			{
				if((guiControlSpeed!=INIT)
					&&(gProtectionFlags.bits.OV!=ERROR)
				  &&(gProtectionFlags.bits.UV!=ERROR)
					&&(gProtectionFlags.bits.OT!=ERROR)
				)
				{
						gMotorControl = STARTUP;		
				}
				else
				{
					if(guiActualSpeed!=INIT)
					{
						stopmotor();
					}
				}
			}
			break;
			
		case STARTUP:
			stopmotor();// stop to reset any registers.
			// directly enter into normal mode running.
			gMotorControl = NORMAL;		
			startmotor();
		
			break;
			
		case DERATING:
		case NORMAL:

			// check errort to stop motor running.
			if(   (gProtectionFlags.bits.OV==ERROR)
					||(gProtectionFlags.bits.UV==ERROR)
					||(gProtectionFlags.bits.OC==ERROR)
					//||(gProtectionFlags.bits.LC==ERROR)
					//||(gProtectionFlags.bits.LP==ERROR)
					||(gProtectionFlags.bits.OT==ERROR)
					//||(gProtectionFlags.bits.LT==ERROR)
					//||(gProtectionFlags.bits.OL==ERROR)
					//||(gProtectionFlags.bits.Blocked==ERROR)
					//||(gProtectionFlags.bits.EL_GDU==ERROR)
					//||(gProtectionFlags.bits.EL_SC==ERROR)
					//||(gProtectionFlags.bits.EL_PB==ERROR)
					||(gucOneElectronicsError!=NOERROR)
					||(gProtectionFlags.bits.EL_Curoffset==ERROR)
					||(gucOneBlockedFlag==ERROR)
					//||(gucOneOverloadFlag==ERROR)
					||(gucOneOverSpeedFlag==ERROR)
					//||(gProtectionFlags.bits.deratingerror==ERROR)
					||(gucLINEOLServiceReceivedFlag==FLAG_SET)
					||(gucLINGotoSleepFlag == FLAG_SET)
					||(INIT==guiControlSpeed)
					//||(ERROR == gucFOCError)
					//||(gucPWMSignalFlashStartFlag == FLAG_SET)
					//||(gucDatalogOperationFlag == FLAG_SET) // datalog operation check			
			)
			{
				suidelaycounter_Stop = 0;
				if((gucOneBlockedFlag==ERROR))//||(gucOneOverloadFlag==ERROR))
				{		
					if(guiTemperature>PLATFORM_TEMPERATURE_HIGH_1deg)
					{
						suidelaycounter_Stop = DELAY_AT_STOPMODE_HIGHLONG_10ms - DELAY_FILTER_BLOCKAGECHECK_10ms;
					}
					else
					{
						if(guiTemperature<PLATFORM_TEMPERATURE_LOW_1deg)
						{
							suidelaycounter_Stop = DELAY_AT_STOPMODE_SHORT_10ms;
						}
						else
						{
							suidelaycounter_Stop = DELAY_AT_STOPMODE_MIDD_10ms - DELAY_FILTER_BLOCKAGECHECK_10ms;
						}
					}
				}				
				else
				{	
					if(gucOneElectronicsError!=NOERROR)
					{
						suidelaycounter_Stop = DELAY_AT_ELECTRONICSERROR_10ms;// delay
					}
					else
					{
						if((gProtectionFlags.bits.OT==ERROR)||(gProtectionFlags.bits.LT==ERROR))
						{
							suidelaycounter_Stop = DELAY_AT_STOPMODE_HIGHLONG_10ms;
						}
						else
						{						
							if(INIT==guiControlSpeed) // if control signal zero.
							{
								suidelaycounter_Stop = DELAY_AT_STOPMODE_SHORT_10ms;
							}
							else
							{
								suidelaycounter_Stop = DELAY_AT_STOPMODE_SHORT_10ms;	
							}								
						}
					}
				}
				gMotorControl      = STOP;			
				// stop motor;
				stopmotor();	

				gucFOCError            = NOERROR;
				gucOneElectronicsError = NOERROR;
				gucOneBlockedFlag      = NOERROR;
				gucOneOverloadFlag     = NOERROR;
				gucOneOverSpeedFlag    = NOERROR;
				//gProtectionFlags.bits.deratingerror = NOERROR;
				break;
			}

			// speed regulation.
			speedregulation();
			break;
			
		case STOP:
		
			stopmotor();			
			// delay
			if(suidelaycounter_Stop)
			{
				suidelaycounter_Stop--;
			}
			else
			{
				gMotorControl        = IDEA;
				suidelaycounter_Idea = DELAY_AT_IDEAMODE_10ms;
			}
			break;
			
		case EOLT:
			break;
			
		case Reverse:
			break;
			
		default:
			break;
			
	}
}

