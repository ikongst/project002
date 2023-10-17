#include "Common.h"
#include "CustomerInterface.h"
#include "PWMDetection.h"

unsigned int guiPWMSignal_Freq       = INIT;
unsigned int guiPWMSignal_Duty       = INIT;
unsigned int guiLINSignal_Digital    = NOSIGNAL_int;
unsigned char gucPINInterfaceStatus  = INIT;
unsigned char gucPINKL15EnableStatus = INIT;
unsigned char gucPINInterfacePullDownStatus   = PULLDOWN_RELEASE;

unsigned char gucPWMSignalFlashStartFlag     = FLAG_RESET;
unsigned char gucPWMSignalDetectedFlag     = FLAG_RESET;

unsigned char gucLINSignalReceivedFlag     = FLAG_RESET;
unsigned char gucLINEOLServiceReceivedFlag = FLAG_RESET;
unsigned int guiLINEOLServiceCounter       = INIT;


unsigned char gucInterfaceStatus  = INIT;


static unsigned char initflagofinterfacestatus = INIT;
static unsigned int suitransfertoLINcounter    = INIT;

unsigned int suiLINOptionValidDelay     = 30000; // 30000*1ms = 30sec, after 30 sec, LIN option not allowed.



void interfacestatusdetection(void);
void updatepwmsignal(void);


static void InterfaceConfig(unsigned char interfacestatus)
{
	if(interfacestatus==INTERFACE_PWM)
	{
		// PWM configuration.
		BSW_PWM_Init();
		gucEOLTFirstSkipFlag = FLAG_RESET;
		// need skip at first to avoid any miss understanding of LIN UDS
		
		PWMDetection_Init();
	}
	else
	{
		if(interfacestatus==INTERFACE_LIN)
		{
			// LIN configuration.
			BSW_LIN_Init();
			gucEOLTFirstSkipFlag = FLAG_RESET;
			// need skip at first to avoid any miss understanding of LIN UDS
		}
	}	
}

void interfacestatusdetection(void)
{
	unsigned char ucinterfacestatus = INIT;
	
	if(suiLINOptionValidDelay)
	{
		suiLINOptionValidDelay--;
	}
	
	if(initflagofinterfacestatus==INIT)
	{
		initflagofinterfacestatus = INITed;

		// default mode is LIN due to register only can be 1 time operation.
//		if(CUSTOMER_REQ_INTERFACE_TYPE==INTERFACE_PWM)
//		{			
//			ucinterfacestatus = INTERFACE_PWM;
//		}
//		else
		{
			ucinterfacestatus = INTERFACE_LIN;
		}
		
		InterfaceConfig(ucinterfacestatus);
		gucInterfaceStatus = ucinterfacestatus;
	}
	else
	{
	#if (CUSTOMER_REQ_INTERFACE_TYPE == INTERFACE_PWM)
		if(gucInterfaceStatus == INTERFACE_LIN)
		{				
			if((gucLINSignalReceivedFlag==FLAG_SET)
				||(gucLINEOLServiceReceivedFlag==FLAG_SET)
			||(guiLINSignal_Digital != NOSIGNAL_int)
				)
			{
				
				suitransfertoLINcounter  = INIT;
				
				suiLINOptionValidDelay   = 30000;
			}
			else
			{					
				suitransfertoLINcounter++;
			}
			
			if((suitransfertoLINcounter>DELAY_INTERFACESTATUS_TRANSFERTO_PWM_1ms)&&(gucInterfaceStatus!=INTERFACE_PWM))
			{					
				suitransfertoLINcounter = INIT;
				InterfaceConfig(INTERFACE_PWM);
				gucInterfaceStatus = INTERFACE_PWM;
			}				
		}
		else
		{			
			if((gucInterfaceStatus == INTERFACE_PWM)&&(suiLINOptionValidDelay!=INIT))
			{					
				if( 
					(guiActualSpeed==INIT)
				&&(guiDiagnosticLowTime==INIT)
				&&(gucPWMSignalFlashStartFlag==INIT)
				&&(gucPWMInvalidStatus == INVALIDPWM_ERROR) // no valid PWM signal
					//&&(guiTargetSpeed == INIT)
					//&&(guiPWMSignal_Freq==NOSIGNAL_int)
					//&&(guiPWMSignal_Duty==NOSIGNAL_int)
				  )
				{
					suitransfertoLINcounter++;	
				}
				else
				{
					suitransfertoLINcounter = INIT;
				}
			
				if((suitransfertoLINcounter>DELAY_INTERFACESTATUS_TRANSFERTO_LIN_1ms)&&(gucInterfaceStatus!=INTERFACE_LIN))
				{
					suitransfertoLINcounter = INIT;
					InterfaceConfig(INTERFACE_LIN);
					gucInterfaceStatus = INTERFACE_LIN;	
				}	
			}
		}	
		
	#endif
	}		
}

#if SYSTEMPARAM_FLASHMODE_HAVE == KONGENABLE
    unsigned char flashstartcheck(unsigned int pwmfreq, unsigned int pwmduty);
	unsigned int suiflashsignalkeepcounter  = INIT;
	unsigned int suiflashsignalexistcounter = INIT;
	unsigned char sucflashmodeflag          = FLAG_RESET;
	unsigned char flashstartcheck(unsigned int pwmfreq, unsigned int pwmduty)
	{
		//unsigned char ucreturnflag = FLAG_RESET;

		if(sucflashmodeflag==FLAG_RESET)
		{
			if(
					((pwmfreq<FLASH_START_PWMSIGNAL_FREQ_MAX_0_1_Hz)&&(pwmfreq>FLASH_START_PWMSIGNAL_FREQ_MIN_0_1_Hz))
				&&((pwmduty<FLASH_START_PWMSIGNAL_DUTY_MAX_0_1_pres)&&(pwmduty>FLASH_START_PWMSIGNAL_DUTY_MIN_0_1_pres))
				//&&(gucPINKL15EnableStatus==PINSTATUS_HIGH)
				)
			{
				// enter into flash mode.
				suiflashsignalkeepcounter += FLASH_START_STEP_COUNTER;
				if(suiflashsignalkeepcounter>FLASH_START_FILTER_SIGNALKEEP_COUNTER)
				{
					suiflashsignalkeepcounter = INIT;
					sucflashmodeflag          = FLAG_SET;
				}
			}
			else
			{
				if(suiflashsignalkeepcounter)
				{
					suiflashsignalkeepcounter--;
				}
			}
		}
		else
		{	
			// exit from flash mode.
			if(gucPINKL15EnableStatus == PINSTATUS_LOW)
			{
				suiflashsignalexistcounter = INIT;
				sucflashmodeflag           = FLAG_RESET;
			}
			else
			{
				if( (pwmfreq<LIMIT_PWM_FREQ_HIGH_0_1Hz)
					&&(pwmfreq>LIMIT_PWM_FREQ_LOW_0_1Hz)
					)
				{
					suiflashsignalexistcounter += FLASH_STOP_STEP_COUNTER;
					if(suiflashsignalexistcounter>FLASH_STOP_FILTER_INPUTVALID_COUNTER)
					{
						suiflashsignalexistcounter = INIT;
						sucflashmodeflag           = FLAG_RESET;
					}
				}
				else
				{
					if(suiflashsignalexistcounter)
					{
						suiflashsignalexistcounter--;
					}
				}
			}
		}
		
		return sucflashmodeflag;
	}
#endif


void updatepwmsignal(void)
{
	static unsigned long nosignalmeasuredcounter = INIT;
	unsigned long currentfreq = INIT;
	unsigned long currentduty = INIT;
	unsigned long deltafreq   = INIT;
	unsigned long deltaduty   = INIT;

	static unsigned long previousfreq =INIT;
	static unsigned long previousduty =INIT;
	static unsigned char pwmsignalsuccesscounter  = INIT;
	static unsigned char pwmsignalfailedcounter   = INIT;
	
	static unsigned char pwmsignaldetectedcounter = INIT;
	
	#if SYSTEMPARAM_FLASHMODE_HAVE == KONGENABLE
		gucPWMSignalFlashStartFlag = flashstartcheck(guiPWMDetection_Freq, guiPWMDetection_Duty);
	#else
		gucPWMSignalFlashStartFlag = FLAG_RESET;
	#endif
	
	if(gucPWMSignalDetectedFlag==FLAG_SET)
	{
		gucPWMSignalDetectedFlag = FLAG_RESET;
		
		currentduty    = guiPWMDetection_Duty;//uigetpwmduty();
		currentfreq    = guiPWMDetection_Freq;//uigetpwmfreq();
		
		if(currentduty>previousduty)
		{
			deltaduty = currentduty-previousduty;
		}
		else
		{
			deltaduty = previousduty - currentduty;
		}
		
		if(currentfreq>previousfreq)
		{
			deltafreq = currentfreq-previousfreq;
		}
		else
		{
			deltafreq = previousfreq - currentfreq;
		}
		
		pwmsignaldetectedcounter++;
		if((deltafreq<LIMIT_PWM_FREQ_DEVIATION_MAX_0_1Hz)&&(deltaduty<LIMIT_PWM_DUTY_DEVIATION_MAX_0_1pres)) // 1hz, 1%
		{
			pwmsignalsuccesscounter++;
		}
		else
		{
			pwmsignalfailedcounter++;
		}
		
		previousduty = currentduty;
		previousfreq = currentfreq;		
		
		if(pwmsignalfailedcounter>=LIMIT_PWM_DUTY_INVALID_ALLOWED_COUNTER)
		{
			pwmsignalsuccesscounter = INIT;
			pwmsignalfailedcounter  = INIT;
		}
		
		if(pwmsignalsuccesscounter>=FILTER_PWM_DUTY_VALID_COUNTER)
		{			
			pwmsignalsuccesscounter = INIT;
			pwmsignalfailedcounter  = INIT;
		
			guiPWMSignal_Duty	= previousduty;
			guiPWMSignal_Freq	= previousfreq;
		}
		
		nosignalmeasuredcounter = INIT;
	}
	else
	{
		if(gucPINInterfacePullDownStatus==PULLDOWN_RELEASE)
		{
			nosignalmeasuredcounter++;
			if(nosignalmeasuredcounter>CUSTOMER_REQ_PWM_INPUTSIGNAL_CLEARDELAY_1ms)
			{
				nosignalmeasuredcounter  = CUSTOMER_REQ_PWM_INPUTSIGNAL_CLEARDELAY_1ms;// 1000ms, maximun time is 1Hz
				guiPWMSignal_Duty = NOSIGNAL_int;
				guiPWMSignal_Freq = NOSIGNAL_int;
			}
		}
	}
}


void InputSignalDetection(void)
{
	// called 1ms period.
	interfacestatusdetection();
	
	if(gucInterfaceStatus==INTERFACE_PWM)
	{
		updatepwmsignal();
		
		guiLINSignal_Digital = NOSIGNAL_int;
	}
	else
	{
		// default and LIN will call the LIN signal.
		guiLINSignal_Digital = uigetlinsignal();
	}

}


