#ifndef __DIAGNOSTIC_H__
#define __DIAGNOSTIC_H__

#include "Diagnostic_Customer.h"

// definition of diagnostic
#define DIAGNOSTIC_PERIOD_ms                CUSTOMER_DIAGNOSTIC_PERIOD_ms
#define DIAGNOSTIC_HIGH_ms                  CUSTOMER_DIAGNOSTIC_HIGH_ms

#define DIAGNOSTIC_UNDERVOLTAGELIMIT_FEEDBACK_DISABLE       7000
#define DIAGNOSTIC_OVERVOLTAGELIMIT_FEEDBACK_DISABLE       19000
#define DIAGNOSTIC_POWERONRESET_DELAY_10ms                  1000 // 10 sec delay send the diagnostic feedback.

#include "Protection.h"
unsigned int GetLowtimefromFailureMode(FailureFlagStructure failuresignals); // specific time.

#if   (PAR_CUSTOMERINTERFACE_SELECTION == CUSTOMERINTERFACE_PWM)\
    ||(PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_PLATFORM)\
		||(PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_GWM)
	void LINDiagnostic_Platform(void);
	
#elif (PAR_CUSTOMERINDEX_SELECTION==CUSTOMERINDEX_GAC)
	void LINDiagnostic_GAC(void);
	
#else

#endif

extern unsigned int guiDiagnosticLowTime;

#define DIAGNOSTIC_TASK_PERIOD_1ms           10  // 10ms task period.
void Diagnostic_Main(void);

#endif

