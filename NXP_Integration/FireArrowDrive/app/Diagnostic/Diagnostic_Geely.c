#include "Diagnostic.h"


#if (PAR_CUSTOMERINDEX_SELECTION==CUSTOMERINDEX_GEELY)
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
		
		if(failuresignals.bits.OT==ERROR)
		{
			// high temper. error.
			uireturnlowtime = DIAGNOSTIC_FAILURE_HIGHTEMP_ERROR_ms;
		}
		else
		{
			if(
				(failuresignals.bits.EL_GDU==ERROR)
			||(failuresignals.bits.EL_SC==ERROR)
			||(failuresignals.bits.EL_PB==ERROR)
			||(failuresignals.bits.EL_POWER==ERROR)
			||(failuresignals.bits.EL_Curoffset==ERROR)
			)
			{
				// internal failure.
				uireturnlowtime = DIAGNOSTIC_FAILURE_INTERNAL_ms;
				delaytimeforfeedback = FLAG_SET;
			}
			else
			{
				if(failuresignals.bits.Blocked==ERROR)
				{
					// blockage error
					uireturnlowtime = DIAGNOSTIC_FAILURE_BLOCKAGE_ms;
				}
				else
				{
					if(
						(failuresignals.bits.OV==ERROR)
					||(failuresignals.bits.UV==ERROR)
					)
					{
						// high temper. error.
						uireturnlowtime = DIAGNOSTIC_FAILURE_VOLTAGE_ms;
						delaytimeforfeedback = FLAG_SET;
					}
					else
					{
						if(failuresignals.bits.LT==ERROR)
						{
							// high temper. error.
							uireturnlowtime = DIAGNOSTIC_FAILURE_HIGHTEMP_WARNING_ms;
							delaytimeforfeedback = FLAG_SET;
						}
						else
						{
							uireturnlowtime = DIAGNOSTIC_HEART_BEAT_MS;
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
