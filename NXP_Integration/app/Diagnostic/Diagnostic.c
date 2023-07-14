#include "Diagnostic.h"
#include "SystemParam.h"
#include "BSW.h"
#include "CustomerInterface.h"

unsigned char gucTest_PINstatus  = INIT;
unsigned int guiTest_diag_period = INIT;
unsigned int guiTest_diag_low    = INIT;
unsigned int guiTest_diag_high   = INIT;



unsigned int guiDiagnosticLowTime        = INIT;

static unsigned int diagnosticTimer      = INIT;
static unsigned int diagnosticPeriodTime = INIT;
static unsigned int diagnosticHighTime   = INIT;
static unsigned int diagnosticLowTime    = INIT;

static unsigned char sucpoweronresetflag   = FLAG_RESET;
static unsigned int suipoweronresetcounter = INIT;
void pwmdiagnostic(void);
void lindiagnostic(void);


void pwmdiagnostic(void)
{

#if SYSTEMPARAM_INTERFACE==DEF_INTERFACE_PWM
	static unsigned char updatediagnosticflag  = INIT;
	static unsigned int t1sthightime_previous  = INIT;
	static unsigned int t2ndpeiodTime_previous = INIT; 
	unsigned int t1sthighTime  = INIT;
	unsigned int t2ndpeiodTime = INIT; 
	unsigned char pinleveltemp = PINSTATUS_HIGH;

	// update the time definition based on failure mode. 
	diagnosticPeriodTime = DIAGNOSTIC_PERIOD_ms;
	diagnosticHighTime   = DIAGNOSTIC_HIGH_ms;
	diagnosticLowTime    = GetLowtimefromFailureMode(gProtectionFlags); // specific time.
	
	if(diagnosticLowTime!= INIT)
	{
		guiDiagnosticLowTime = diagnosticLowTime;
	}	
	
	if(sucpoweronresetflag==FLAG_RESET)
	{
		suipoweronresetcounter++;
		if(suipoweronresetcounter>DIAGNOSTIC_POWERONRESET_DELAY_10ms)
		{
			suipoweronresetcounter = INIT;
			sucpoweronresetflag    = FLAG_SET;
		}
	}
	
	if((guiVoltage>DIAGNOSTIC_OVERVOLTAGELIMIT_FEEDBACK_DISABLE)||(sucpoweronresetflag==FLAG_RESET)
		||(guiVoltage<DIAGNOSTIC_UNDERVOLTAGELIMIT_FEEDBACK_DISABLE)
		||(gucPINKL15EnableStatus==PINSTATUS_LOW)
	  ||(guiTargetSpeed==INIT))
	{
		// no feedback directly.
		diagnosticLowTime    = INIT;
		updatediagnosticflag = INIT;
		diagnosticTimer      = INIT;
	}
	
	// calculate the level opearation.
	t1sthighTime  = diagnosticHighTime;
	t2ndpeiodTime = diagnosticHighTime+diagnosticLowTime;
	
	if(diagnosticPeriodTime!=INIT)
	{
		t1sthighTime  = diagnosticPeriodTime-diagnosticLowTime;
		t2ndpeiodTime = diagnosticPeriodTime;
	}		

	if(updatediagnosticflag==INIT)
	{		
		updatediagnosticflag   = INITed;
		t1sthightime_previous  = t1sthighTime;
		t2ndpeiodTime_previous = t2ndpeiodTime;
	}
	
	guiTest_diag_period = t2ndpeiodTime;
	guiTest_diag_low    = diagnosticLowTime;
	guiTest_diag_high   = t1sthighTime;
	
	
	// operate the PIN level
	diagnosticTimer += DIAGNOSTIC_TASK_PERIOD_1ms;// 10ms interval.
	if(diagnosticTimer<t1sthightime_previous)
	{
		// do nothing.
	}		
	else
	{
		if(diagnosticTimer<t2ndpeiodTime_previous)
		{
			// set pwm feedback signal as 0/low;			
			pinleveltemp      = PINSTATUS_LOW;
			gucTest_PINstatus = PINSTATUS_LOW;
		}
		else
		{
			updatediagnosticflag = INIT; // finished this round of diagnostic.	
			guiDiagnosticLowTime = INIT; // reset
			diagnosticTimer      = INIT;
			// release status, set pwm feedback as 1/high;
			pinleveltemp         = PINSTATUS_HIGH;
			gucTest_PINstatus    = PINSTATUS_HIGH;
		}	
	}

	BSW_setpinstatus_interface(pinleveltemp);
	gucPINInterfacePullDownStatus = ((pinleveltemp==PINSTATUS_HIGH)?PULLDOWN_RELEASE:PULLDOWN_ENABLE);
	
#endif

}

void lindiagnostic(void)
{
	#if PAR_CUSTOMERINTERFACE_SELECTION == CUSTOMERINTERFACE_PWM
		// default LIN protocol.
		LINDiagnostic_Platform();
	
	#else
		#if PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_GAC
			LINDiagnostic_GAC();
		#else
		
		#endif
		
	#endif
	
}

void Diagnostic_Main(void)
{
	if(gucInterfaceStatus == INTERFACE_PWM)
	{
		pwmdiagnostic();
	}
	else
	{
		lindiagnostic();
	}
}


