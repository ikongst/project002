#include "SystemSchedule.h"
#include "Measurement.h"
#include "Protection.h"
#include "MotorOperation.h"
#include "Diagnostic.h"
#include "DataLog.h"
#include "CustomerInterface.h"
#include "Common.h"
#include "BSW.h"
#include "UDS.h"

//#include "UDS.h" // to be added.

static void PWMLIN_quickservice(void);




static void PWMLIN_quickservice(void)
{
	if(gucInterfaceStatus==INTERFACE_PWM)
	{
		PWMDetection_Main();
	}
	else
	{
		BSW_LIN_service();
	}
}

// this variable should be set as 1(true) with 1ms interval.
static unsigned char sucsystemticket_1ms = INIT;
void SetFlag_1MS(void)
{
	sucsystemticket_1ms = KONGTRUE;
}


void SystemSchedule_Init(void)
{
	BSW_MotorStop();
	BSW_KL15Config();
	
	guiMaxSpeedCalculated = SYSTEMPARAM_SPEED_MAX_rpm;
	guiMinSpeedCalculated = SYSTEMPARAM_SPEED_MIN_rpm;
}

unsigned char datapointarr[16]={0,0,0,0,0,0};	
void SystemSchedule_Main(void)
{		
	static unsigned char ticketcounter = INIT;	
	static unsigned char sucBootloaderCntr = INIT;
		
	ANALYSIS_TIMERSTART(TASK_ASAP);
	PWMLIN_quickservice();
	ANALYSIS_TIMERSTOP(TASK_ASAP);

	TaskAnalysis_Main();
	
	
	if(sucsystemticket_1ms==KONGTRUE)
	{
		sucsystemticket_1ms = KONGFALSE; // 1 ms system period interval.
						
		ANALYSIS_TIMERSTART(TASK_1ms);
		InputSignalDetection();
		ANALYSIS_TIMERSTOP(TASK_1ms);
		
		ticketcounter++;
		switch(ticketcounter)
		{
			case 1:					
					ANALYSIS_TIMERSTART(TASK_Measurement);
					Measurement_Main();
					ANALYSIS_TIMERSTOP(TASK_Measurement);
					break;
			
			case 2:				
					ANALYSIS_TIMERSTART(TASK_CustomerInterface);
					CustomerInterface_Main();
					ANALYSIS_TIMERSTOP(TASK_CustomerInterface);
					break;

			case 3:
					ANALYSIS_TIMERSTART(TASK_Protection);
					Protection_Main();			
					ANALYSIS_TIMERSTOP(TASK_Protection);
					break;
			
			case 4:
					ANALYSIS_TIMERSTART(TASK_DataLog);
					DataLog_Main();
					ANALYSIS_TIMERSTOP(TASK_DataLog);
					break;
			
			case 5:
					ANALYSIS_TIMERSTART(TASK_Diagnostic);
			        Diagnostic_Main();
					ANALYSIS_TIMERSTOP(TASK_Diagnostic);
			    break;
			
			case 6:
					ANALYSIS_TIMERSTART(TASK_UDS);
					UDS_Main();
					ANALYSIS_TIMERSTOP(TASK_UDS);
					

					if(gucBootloaderFlag==FLAG_SET)
					{
						sucBootloaderCntr++;
						if(sucBootloaderCntr>100)
						{
							sucBootloaderCntr = INIT;
						    gucBootloaderFlag = FLAG_RESET;

						    DisableInterrupts;
						    
							getdatafromflash_1(datapointarr, FLASH_ADDRESS_SWID/16, SW_READ_ARR_LENGTH);						    
							datapointarr[0]=0xAB;
							flashoperation_1(datapointarr, FLASH_ADDRESS_SWID/16, SW_WRITE_ARR_LENGTH);
						    
							BSW_EnterToBoot();
						    
						    //CPMUCOP = 0x01;     //enable watchdog
						    //CPMUARMCOP = 0x00;
						    //value written to ARMCOP register different from 0xAA or 0x55 will reset
						    //the MCU immediately.
						}
					}
			    break;
			
			case 7:							
					ANALYSIS_TIMERSTART(TASK_MotorOperation);
					MotorOperation_Main();
					ANALYSIS_TIMERSTOP(TASK_MotorOperation);
					break;
			
			case 8:				
					ANALYSIS_TIMERSTART(TASK_RAMROM);
					//InternalDiagnostic_Main();
					ANALYSIS_TIMERSTOP(TASK_RAMROM);
					break;
			
			case 9:			 
					break;
			
			case 10:
					// no break;
			default: 
					ticketcounter = INIT;
					break;
		}
	}
}

