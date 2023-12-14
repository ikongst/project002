#include "Diagnostic.h"
#include "Protection.h"
#include "Common.h"
#include "CustomerInterface.h"
#include "Measurement.h"
#include "ProjectConfig.h"
#include "lin_cfg.h"
#include "lin.h"


#if   (PAR_CUSTOMERINTERFACE_SELECTION == CUSTOMERINTERFACE_PWM)\
    ||(PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_PLATFORM)\
		||(PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_GWM)
		
	static unsigned int responseerrorcounter = 0;
	void LINDiagnostic_Platform(void)
	{			
		unsigned char tempvalue = INIT;		
		l_u16_wr_LIN_NXP_ActSpeed(guiActualSpeed);
		
		l_u8_wr_LIN_NXP_ActVoltage(guiVoltage/100);
		l_u8_wr_LIN_NXP_ActCurrent((long)guiCurrent*5/2000);
		l_bool_wr_LIN_NXP_OverTempErr((gProtectionFlags.bits.OT+gProtectionFlags.bits.LT)>FLAG_RESET?FLAG_SET:FLAG_RESET);

		l_bool_wr_LIN_NXP_InnerErr((gProtectionFlags.bits.EL_GDU
										 +gProtectionFlags.bits.EL_SC
										 +gProtectionFlags.bits.EL_OC
										 +gProtectionFlags.bits.EL_PB
										 +gProtectionFlags.bits.EL_POWER
										 +gProtectionFlags.bits.EL_Curoffset)>FLAG_RESET?FLAG_SET:FLAG_RESET);
		
		l_bool_wr_LIN_NXP_StallSt((gProtectionFlags.bits.OL+gProtectionFlags.bits.Blocked)>FLAG_RESET?FLAG_SET:FLAG_RESET);
		l_bool_wr_LIN_NXP_OverCurrErr((gProtectionFlags.bits.OC+gProtectionFlags.bits.LC)>FLAG_RESET?FLAG_SET:FLAG_RESET);
		
		tempvalue = INIT;
		if(gProtectionFlags.bits.OV==FLAG_SET)
		{
			tempvalue = 1;
		}
		else
		{
			if(gProtectionFlags.bits.UV==FLAG_SET)
			{
				tempvalue = 2;
			}
		}		
		l_u8_wr_LIN_NXP_PowerErr(tempvalue);

		// 10ms period.
		// after defined filter time, start the response error feedback.
		if(gucLINResponseError==FLAG_RESET)
		{
			if(responseerrorcounter)
			{
				responseerrorcounter--;
			}
			else
			{
				l_bool_wr_LIN_NXP_RespErr(FLAG_RESET);
			}
		}
		else
		{
			if(responseerrorcounter>= FILTER_LINRESPONSEERROR_10ms)
			{
				l_bool_wr_LIN_NXP_RespErr(FLAG_SET);
			}
			else
			{
				responseerrorcounter++;
			}
		}
		
		// next frame
		l_u8_wr_LIN_NXP_Temperature(guiTemperature);
		l_u8_wr_LIN_NXP_NTC(guiTemperatureNTC);
		l_u8_wr_LIN_NXP_InternalVer(gucswversion_internal);
		
		l_bool_wr_LIN_NXP_SS_GDU(gProtectionFlags.bits.EL_GDU);
		l_bool_wr_LIN_NXP_SS_OC(gProtectionFlags.bits.EL_OC);
		l_bool_wr_LIN_NXP_SS_SC(gProtectionFlags.bits.EL_SC);
		l_bool_wr_LIN_NXP_SS_Offset(gProtectionFlags.bits.EL_Curoffset);
		l_bool_wr_LIN_NXP_SS_PB(gProtectionFlags.bits.EL_PB);
		l_bool_wr_LIN_NXP_SS_CurLimit(gProtectionFlags.bits.LC);
		l_bool_wr_LIN_NXP_SS_CurOver(gProtectionFlags.bits.OC);
		l_bool_wr_LIN_NXP_SS_TempLimit(gProtectionFlags.bits.LT);
		l_bool_wr_LIN_NXP_SS_TempOver(gProtectionFlags.bits.OT);

		l_u8_wr_LIN_NXP_feedback7(guiInformation_BootVersion);
		l_u8_wr_LIN_NXP_feedback8(guiLibVersion_Protection);
		
	}
#endif

#if   (PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_PLATFORM)\
		||(PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_GWM)

	//     |< ------     period = 0  ------->|
	//      _____________________             ___________
	//     |    high             |____low____|
	//
	//
	//     |< ------     period = 10  ------->|
	//      ______________________             ___________
	//     |    high = 0          |____low____|
	//

	static unsigned int feedbacklowtimeOLD  = 0;
	static unsigned int feedbacklowtimeOLD2 = 0;

	static unsigned int delaytimeforfeedbackcounter = 0;

	unsigned int GetLowtimefromFailureMode(FailureFlagStructure failuresignals)
	{
		unsigned int uireturnlowtime      = INIT;
		unsigned int delaytimeforfeedback = FLAG_RESET;
		if(
				(failuresignals.bits.EL_GDU==ERROR)
			||(failuresignals.bits.EL_SC==ERROR)
			||(failuresignals.bits.EL_PB==ERROR)
			||(failuresignals.bits.EL_OC==ERROR)
			||(failuresignals.bits.EL_POWER==ERROR)
			||(failuresignals.bits.EL_Curoffset==ERROR)
			)
		{
			// internal failure.
			uireturnlowtime = DIAGNOSTIC_FAILURE_INTERNAL_ms;
		}
		else
		{
//			if(failuresignals.bits.OL==ERROR)
//			{
//				// overload error.
//				uireturnlowtime = DIAGNOSTIC_FAILURE_OVERLOAD_ms;
//				delaytimeforfeedback = FLAG_SET;
//			}
//			else
			{				
				if(failuresignals.bits.OT==ERROR)
				{
					// high temper. error.
					uireturnlowtime = DIAGNOSTIC_FAILURE_HIGHTEMP_ERROR_ms;
				}
				else
				{						
					if(failuresignals.bits.Blocked==ERROR)
					{
						// blockage error
						uireturnlowtime = DIAGNOSTIC_FAILURE_BLOCKAGE_ms;
						delaytimeforfeedback = FLAG_SET;
					}
					else
					{				
						if(
								(failuresignals.bits.OV==ERROR)
							||(failuresignals.bits.UV==ERROR)
							)
						{
							// voltage. error.
							uireturnlowtime = DIAGNOSTIC_FAILURE_VOLTAGE_ms;
						}
						else
						{
							uireturnlowtime      = INIT;
							delaytimeforfeedback = FLAG_SET;
						}						
					}
				}
			}
		}

		if(feedbacklowtimeOLD != uireturnlowtime)
		{	
			feedbacklowtimeOLD2  = feedbacklowtimeOLD; // save old output		
			
			if(delaytimeforfeedback==FLAG_RESET)
			{
				delaytimeforfeedbackcounter = DIAGNOSTIC_FAILURE_DELAY_ms;
			}
			else
			{
				delaytimeforfeedbackcounter = INIT;
			}
			
			feedbacklowtimeOLD   = uireturnlowtime;
		}
		
		if(delaytimeforfeedbackcounter>DIAGNOSTIC_TASK_PERIOD_1ms)
		{
			delaytimeforfeedbackcounter -= DIAGNOSTIC_TASK_PERIOD_1ms;
			uireturnlowtime = feedbacklowtimeOLD2;
		}
		else
		{
			uireturnlowtime = feedbacklowtimeOLD;
		}
		
		return uireturnlowtime;
	}

#endif

