#include "CustomerInterface.h"
#include "Common.h"
#include "SpeedCurve.h"
#include "PWMDetection.h"

unsigned int guiLibVersion_CustomerInterface = 0x012;

unsigned char gucLINResponseError = INIT;
unsigned char gucLINGotoSleepFlag = INIT;

unsigned int guiTargetSpeed       = INIT;
unsigned int guiControlSpeed      = INIT;
unsigned int guiActualSpeed       = INIT;

unsigned char gucHighLowStatus    = INIT;
unsigned char gucPWMInvalidStatus = INVALIDPWM_NOERROR;



unsigned char checkhighlowsignal(unsigned char ucPINStatus)
{	
	unsigned char returnvalue = HIGHLOW_NOERROR;
	static unsigned char savedhighlowstatus = HIGHLOW_NOERROR;
	static unsigned char previous_pinlevel  = HIGHLOW_INIT;
	static unsigned int checklowhighcounter = INIT;
	unsigned char current_pinleveltemp      = ucPINStatus;

	
	if(gucPINInterfacePullDownStatus==PULLDOWN_RELEASE)
	{
		if(gucPWMDetection_TriggerFlag==FLAG_SET)
		{
			gucPWMDetection_TriggerFlag = FLAG_RESET;
			checklowhighcounter = INIT;
			savedhighlowstatus  = HIGHLOW_NOERROR;
		}
		else
		{	
		
			if(previous_pinlevel == current_pinleveltemp)
			{
				checklowhighcounter++;
				if(checklowhighcounter>=FILTER_HIGHLOWCHECK_10ms)
				{
					checklowhighcounter = FILTER_HIGHLOWCHECK_10ms;
					
				  if(
						(
							(guiPWMSignal_Duty!=INIT_uimax)&&(guiPWMSignal_Duty!=INIT)
						&&(guiPWMSignal_Freq!=INIT_uimax)&&(guiPWMSignal_Freq!=INIT)
						)
					||(guiLINSignal_Digital != INIT_uimax)
					)
					{
						returnvalue         = HIGHLOW_NOERROR;
						checklowhighcounter = INIT;
					}
					else
					{
						if(current_pinleveltemp==PINSTATUS_LOW)
						{
							returnvalue = HIGHLOW_LOW;
						}
						else
						{
							returnvalue = HIGHLOW_HIGH;
						}						
					}
					
					savedhighlowstatus = returnvalue;
				}
			}
			else
			{
				checklowhighcounter = INIT;
				savedhighlowstatus  = HIGHLOW_NOERROR;
			}
		}	
	}
	previous_pinlevel = current_pinleveltemp;
	return savedhighlowstatus;
}


unsigned char checkinvalidsignal(unsigned int pwmfreq, unsigned int pwmduty)
{
	unsigned int retvalue = INVALIDPWM_NOERROR;
	
	unsigned int newpwmdutycycle = pwmduty;
	unsigned int newpwmfrequency = pwmfreq;	
	
	// freq invalid check
	if((newpwmfrequency<LIMIT_PWM_FREQ_LOW_0_1Hz)||(newpwmfrequency>LIMIT_PWM_FREQ_HIGH_0_1Hz))
	{
		retvalue = INVALIDPWM_ERROR;
	}
	
	// duty invalid check, GWM specific function.
	if( (CUSTOMER_REQ_INVALID_RANGE(newpwmdutycycle))
		&&(newpwmdutycycle != NOSIGNAL_int))
	{
		retvalue = INVALIDPWM_ERROR;
	}
	return retvalue;
}


	unsigned char ucspeeddigital     = INIT;
	unsigned int uispeedvaluerpm     = INIT;
	unsigned char ucdigitaldelta     = INIT;
	unsigned int uispeeddelta        = INIT;
unsigned int getcontrolspeedbycustomerinput(unsigned int pwmduty, unsigned int LINsignal)
{
	static unsigned int sucspeeddigital_Previous = INIT;
	static unsigned int suicontrolspeed_previous  = INIT;
	
	unsigned char ucsetspeeddirectly = FLAG_RESET;
	unsigned char uctableselection   = SPEEDCURVETABLE_TYPE_DEFAULT;


	if(CUSTOMER_REQ_INTERFACE_TYPE == INTERFACE_LIN)
	{
		ucspeeddigital     = LINsignal;
		ucsetspeeddirectly = FLAG_SET;
		uctableselection   = SPEEDCURVETABLE_TYPE_CUSTOMER;
	}
	else
	{
		// if PWM interfae, check the LIN communication firstly.
		if(LINsignal != NOSIGNAL_int)
		{
			ucspeeddigital	   = LINsignal;
			ucsetspeeddirectly = FLAG_SET;
			uctableselection   = SPEEDCURVETABLE_TYPE_DEFAULT;
		}
		else
		{
			if(pwmduty!=NOSIGNAL_int)
			{
				ucspeeddigital   = ((long)pwmduty<<7)/1000;
				uctableselection = SPEEDCURVETABLE_TYPE_CUSTOMER;
			}
			else
			{
				ucspeeddigital     = NOSIGNAL_char;
				uctableselection   = SPEEDCURVETABLE_TYPE_DEFAULT;
				ucsetspeeddirectly = FLAG_SET;
			}
		}
	}

	// check if we can transfer target speed to control speed, or not.	
	uispeedvaluerpm = GetSpeedByDigital(ucspeeddigital, uctableselection);

	
	
	if(ucspeeddigital>sucspeeddigital_Previous)
	{
		ucdigitaldelta = ucspeeddigital-sucspeeddigital_Previous;
	}
	else
	{
		ucdigitaldelta = sucspeeddigital_Previous-ucspeeddigital;
	}
	
		
	if(uispeedvaluerpm>suicontrolspeed_previous)
	{
		uispeeddelta = uispeedvaluerpm-suicontrolspeed_previous;
		ucsetspeeddirectly = FLAG_SET;
	}
	else
	{
		if(uispeedvaluerpm==INIT)
		{
			uispeeddelta = INIT;
		}
		else
		{
			uispeeddelta = suicontrolspeed_previous-uispeedvaluerpm;
		}
	}
	
	
	if(
			  (ucsetspeeddirectly==FLAG_SET)
			||(ucdigitaldelta>=SPEEDREGULATION_HYSTHERESIS_dig)
			||(uispeeddelta>=SPEEDREGULATION_HYSTHERESIS_rpm)
	)
	{		
		suicontrolspeed_previous  = uispeedvaluerpm;
		sucspeeddigital_Previous  = ucspeeddigital;
	}
	
	
//	if(
//			  (ucsetspeeddirectly==FLAG_SET)
//			||(ucspeeddigital >= (SPEEDREGULATION_HYSTHERESIS_dig + sucspeeddigital_Previous))
//			||(sucspeeddigital_Previous >= (SPEEDREGULATION_HYSTHERESIS_dig + ucspeeddigital))
//			||((uispeedvaluerpm==INIT)&&(ucspeeddigital >= (SPEEDREGULATION_HYSTHERESIS_dig + sucspeeddigital_Previous)))
//			||((uispeedvaluerpm==INIT)&&(sucspeeddigital_Previous >= (SPEEDREGULATION_HYSTHERESIS_dig + ucspeeddigital)))
//			||((uispeedvaluerpm!=INIT)&&(suicontrolspeed_previous!=INIT)&&(uispeedvaluerpm > suicontrolspeed_previous))
//			||((uispeedvaluerpm!=INIT)&&(suicontrolspeed_previous!=INIT)&&((suicontrolspeed_previous - uispeedvaluerpm) <= SPEEDREGULATION_HYSTHERESIS_rpm))
//		)
//	{
//	}		

	return suicontrolspeed_previous;
}

#define TYPE_EMERGENCYMODE_NO          0x00
#define TYPE_EMERGENCYMODE_LOW         0x01
#define TYPE_EMERGENCYMODE_HIGH        0x02
#define TYPE_EMERGENCYMODE_XXX         0x03
unsigned char gucEmergencyType = TYPE_EMERGENCYMODE_NO;
unsigned int checkemergencymode(unsigned int uipreviousspeed, unsigned char uchighlowstatus, unsigned char ucinvalidpwmstatus, unsigned int uiLINsignal)
{	
	unsigned int returncontrolspeed = uipreviousspeed;
	unsigned int uifinalyspeed      = uipreviousspeed;
	
	static unsigned int suiemergencyentercounter   = INIT;
	static unsigned char sucemergencytype_previous = TYPE_EMERGENCYMODE_NO;
	static unsigned char suckl15status_previous    = INIT;
		
	gucEmergencyType = TYPE_EMERGENCYMODE_NO;
	if(uiLINsignal==NOSIGNAL_int)
	{
		if(uchighlowstatus==HIGHLOW_LOW)
		{
			gucEmergencyType = TYPE_EMERGENCYMODE_LOW;
		}
		else
		{
			if(uchighlowstatus==HIGHLOW_HIGH)
			{
				gucEmergencyType = TYPE_EMERGENCYMODE_HIGH;				
			}
			else
			{
				if((gucHighLowStatus==HIGHLOW_NOERROR)&&(ucinvalidpwmstatus==INVALIDPWM_ERROR))
				{
					gucEmergencyType = TYPE_EMERGENCYMODE_XXX;				
				}					
			}
		}
	}
		
	//- delay control.
	if(gucEmergencyType != sucemergencytype_previous)
	{
		suiemergencyentercounter   = INIT;			
		sucemergencytype_previous  = gucEmergencyType;
	}
	
	if(suckl15status_previous != gucPINKL15EnableStatus)
	{
		suiemergencyentercounter   = INIT;			
		suckl15status_previous     = gucPINKL15EnableStatus;
	}
	
	if(gucEmergencyType != TYPE_EMERGENCYMODE_NO)
	{			
		#if   (PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_PLATFORM)\
				||(PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_GWM)
			if(  
					(   (gucEmergencyType==TYPE_EMERGENCYMODE_LOW)  // stop directly
			      ||(gucEmergencyType==TYPE_EMERGENCYMODE_HIGH) // stop directly
			      //||(gucEmergencyType==TYPE_EMERGENCYMODE_XXX) // need stop in 10s
					)
				&&(gucPINKL15EnableStatus==PINSTATUS_LOW)
			)
			{
				suiemergencyentercounter = INIT;
				uifinalyspeed            = INIT;			
			}
			else
		#endif	
			{		
				suiemergencyentercounter++;
				if(suiemergencyentercounter>=CUSTOMER_REQ_EMERGENCYMODE_ENTERDELAY_10ms)
				{
					suiemergencyentercounter = INIT;
					
						switch(gucEmergencyType)
						{
							case TYPE_EMERGENCYMODE_LOW:
									if((CUSTOMER_REQ_EMERGENCYMODE_000_ENABLE==KONGENABLE)
										&&(gucPINKL15EnableStatus==PINSTATUS_HIGH)
									)
									{
										uifinalyspeed = CUSTOMER_REQ_MAXSPEED_rpm;
									}
									else
									{
										uifinalyspeed = INIT;
									}
								break;
							case TYPE_EMERGENCYMODE_HIGH:
									if((CUSTOMER_REQ_EMERGENCYMODE_100_ENABLE==KONGENABLE)
										&&(gucPINKL15EnableStatus==PINSTATUS_HIGH)
									)
									{
										uifinalyspeed = CUSTOMER_REQ_MAXSPEED_rpm;
									}
									else
									{
										uifinalyspeed = INIT;
									}
								break;
							case TYPE_EMERGENCYMODE_XXX:
									if((CUSTOMER_REQ_EMERGENCYMODE_XXX_ENABLE==KONGENABLE)
										&&(gucPINKL15EnableStatus==PINSTATUS_HIGH)
									)
									{
										uifinalyspeed = CUSTOMER_REQ_MAXSPEED_rpm;
									}
									else
									{
										uifinalyspeed = INIT;
									}
								break;
							case TYPE_EMERGENCYMODE_NO:
							default:
									uifinalyspeed = INIT;
								break;					
						}	
				}
			}
	}		
	
	returncontrolspeed = uifinalyspeed;
	
	return returncontrolspeed;
}


static unsigned int suipinstatuscounter    = INIT;
static unsigned char sucpinstatusfeedback  = INIT;
unsigned char ucPINStatusKL15_filter(void)
{
	static unsigned char sucpinstatus_previous = INIT;
	unsigned char ucpinstatus                  = ucgetPINEnableStatus(); // kl15 signal need filtered.
//	unsigned char filterpinstatus = 0;	
	
	if(sucpinstatus_previous != ucpinstatus)
	{
		suipinstatuscounter   = INIT;
		sucpinstatus_previous = ucpinstatus;
	}
	else
	{
		suipinstatuscounter++;
		if(suipinstatuscounter>=FILTER_KL15ENABLE_10ms)
		{
			suipinstatuscounter  = INIT;
			sucpinstatusfeedback = ucpinstatus;
		}	
	}
	
	return sucpinstatusfeedback;
}


unsigned int finallycontrolspeed = INIT;
void CustomerInterface_Main(void)
{		

//	unsigned char tempinvalidsignal  = INIT;
//	unsigned char temppinstatus      = INIT;

	// 0 - read control signal
	gucPINInterfaceStatus  = ucgetPINInterfaceStatus(); 
	#if SYSTEMPARAM_ENABLE_KL15_HAVE == KONGENABLE	
		gucPINKL15EnableStatus = ucPINStatusKL15_filter();
	#else
		gucPINKL15EnableStatus = PINSTATUS_HIGH;
	#endif
	
	gucHighLowStatus    = checkhighlowsignal(gucPINInterfaceStatus);
	
	gucPWMInvalidStatus = INVALIDPWM_NOERROR;
	#if CUSTOMER_REQ_INTERFACE_TYPE == INTERFACE_PWM
		gucPWMInvalidStatus = checkinvalidsignal(guiPWMSignal_Freq, guiPWMSignal_Duty);
	#endif
	
	// based on highlow signal and PWM estimation, to determine the table search.
	if(
			((gucHighLowStatus==HIGHLOW_HIGH)&&(SPEEDCURVETABLE_CUSTOMER[SPEEDCURVETABLE_MAXID]!=INIT))
		||((gucHighLowStatus==HIGHLOW_LOW)&&(SPEEDCURVETABLE_CUSTOMER[SPEEDCURVETABLE_MINID]!=INIT))
		)
	{
		gucPWMInvalidStatus = INVALIDPWM_NOERROR;
		
		if(gucHighLowStatus==HIGHLOW_HIGH)
		{
			guiPWMSignal_Duty = SYSTEMPARAM_PWM_DUTY_HIGH_0_1_pres;			
		}
		else
		{
			guiPWMSignal_Duty = SYSTEMPARAM_PWM_DUTY_LOW_0_1_pres;
		}
	}
	
	if(
				(gucPWMInvalidStatus == INVALIDPWM_NOERROR)
			||(guiLINSignal_Digital!=NOSIGNAL_int)
		)
	{
		finallycontrolspeed = getcontrolspeedbycustomerinput(guiPWMSignal_Duty, guiLINSignal_Digital);
		guiTargetSpeed  = finallycontrolspeed;	
	}
	else
	{
		guiTargetSpeed = INIT_uimax;
	}

	// emergency mode check.
	finallycontrolspeed = checkemergencymode(finallycontrolspeed, gucHighLowStatus, gucPWMInvalidStatus, guiLINSignal_Digital);
	
	if(gucPWMSignalFlashStartFlag==FLAG_SET)
	{
		finallycontrolspeed = INIT; // if flashstart flag set, stop motor running.
	}

	if(finallycontrolspeed>guiMaxSpeedCalculated)
	{
		finallycontrolspeed = guiMaxSpeedCalculated;
	}
	guiControlSpeed = finallycontrolspeed;	
}


