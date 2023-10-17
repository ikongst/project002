#include "PWMDetection.h"
#include "Common.h"
#include "CustomerInterface.h"

// this function should be called by pulse edge interrupt.
/*
********************************************************************************
**         start          capture   capture                capture            **
**         Timer2         Timer2    Timer2                 Timer2             **
**       -----                --------              ---------                 **
** P1.2       |              |        |            |         |                **
**            :--------------:\       :------------          :------...       **
**            :    capDC     : \      :\                     :    capDC       **
**            :<------------>:  \     : \                    :<-----...       **
**            :                  \    :  \                   :                **
**            :     PWM_Capture() ISR :   \                  :                **
**           (captured on rising edge):    \                 :                **
**            :                       :     \                :                **
**            :    capPer             :      \               :    capPer      **
**            :<--------------------->:       \              :<-----...       **
**                                             \                              **
**                                      PWM_Capture() ISR                     **
**                            (captured on  falling edge)                     **
*******************************************************************************/

unsigned int guiPWMDetection_Duty = INIT;
unsigned int guiPWMDetection_Freq = INIT;

unsigned char gucPWMDetection_TriggerFlag = FLAG_RESET;

static unsigned char suconepwmdetectedflag = FLAG_SET;
static unsigned long suioverflowcounter   = INIT;
static unsigned long suiPWMTimerstep0 = INIT;
static unsigned long suiPWMTimerstep1 = INIT;
static unsigned long suiPWMTimerstep2 = INIT;

static unsigned char sucinitflag = INIT;
static unsigned char sucfallingdetected = FLAG_RESET;
static unsigned char sucplusestep = INIT;	
	
void PWMDetection_Init(void)
{
	sucinitflag           = INIT;
	suconepwmdetectedflag = FLAG_RESET;
	suioverflowcounter    = INIT;
	suiPWMTimerstep0 = INIT;	
	suiPWMTimerstep1 = INIT;	
	suiPWMTimerstep2 = INIT;	
	
	sucfallingdetected = FLAG_RESET;
	sucplusestep = INIT;
}

void PWMDetection_Main(void)
{
	unsigned long ulperiod = INIT;
	unsigned long ulduty   = INIT;
	
	if(sucinitflag==INIT)
	{
		sucinitflag = INITed;
		settrriger_rise();
	}
	else
	{	
		if(gucPINInterfacePullDownStatus==PULLDOWN_ENABLE)
		{	
//			suiPWMTimerstep0 = INIT;
//			suiPWMTimerstep1 = INIT;
//			suiPWMTimerstep2 = INIT;			
//			suconepwmdetectedflag = FLAG_RESET;
		}
		else
		{		
			if(suconepwmdetectedflag==FLAG_SET)
			{
				suconepwmdetectedflag = FLAG_RESET;
				
				ulperiod = suiPWMTimerstep2 - suiPWMTimerstep0;
				ulduty   = suiPWMTimerstep1 - suiPWMTimerstep0;
				
				guiPWMDetection_Duty = ulduty*1000/ulperiod;
				guiPWMDetection_Freq = gettimerclk()*10/ulperiod;//HZ 0.1
				
				gucPWMSignalDetectedFlag = FLAG_SET;
			}
		}
	}	
}

void PWMDetection_INT(void)
{
	
	static unsigned long suirisingpulsetimer0 = INIT;
	static unsigned long suirisingpulsetimer1 = INIT;
	static unsigned long suifallingpulsetimer = INIT;	
	
				
	
	switch(sucplusestep)
	{
		case 0: // rising edge 0 and 1
			if(sucfallingdetected==FLAG_SET)
			{
				suirisingpulsetimer1  = gettimercntr() + (suioverflowcounter<<16);
				
				suiPWMTimerstep0 = suirisingpulsetimer0;
				suiPWMTimerstep1 = suifallingpulsetimer;
				suiPWMTimerstep2 = suirisingpulsetimer1;
				suconepwmdetectedflag = FLAG_SET;
				
				sucfallingdetected = FLAG_RESET;
				suioverflowcounter = INIT;	
				gucPWMDetection_TriggerFlag = FLAG_SET;		
				
			}
			
			suirisingpulsetimer0  = gettimercntr();
			suioverflowcounter    = INIT;			
			suifallingpulsetimer  = INIT;
			
			settrriger_fall();
			sucplusestep++;
				
			break;
			
		case 1: // falling edge
			suifallingpulsetimer = gettimercntr() + (suioverflowcounter<<16);
			
			sucfallingdetected   = FLAG_SET;
			settrriger_rise();
			sucplusestep=0;
			break;
		
		default:
			sucplusestep = INIT;
			break;		
	}
}

void PWM_overflow_INT(void)
{
	suioverflowcounter++;
}
