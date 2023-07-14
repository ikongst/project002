#ifndef __DIAGNOSTIC_PLATFORM_H__
#define __DIAGNOSTIC_PLATFORM_H__

#include "ProjectConfig.h"
#if   (PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_PLATFORM)\
		||(PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_GWM)
    
	#define CUSTOMER_DIAGNOSTIC_PERIOD_ms                0
	#define CUSTOMER_DIAGNOSTIC_HIGH_ms               2500
	
	#define DIAGNOSTIC_FAILURE_INTERNAL_ms            4500
	#define DIAGNOSTIC_FAILURE_HIGHTEMP_ERROR_ms      4000
	#define DIAGNOSTIC_FAILURE_VOLTAGE_ms             3500
	#define DIAGNOSTIC_FAILURE_OVERLOAD_ms            3000
	#define DIAGNOSTIC_FAILURE_BLOCKAGE_ms            2500

	#define DIAGNOSTIC_HEART_BEAT_MS                     0 // ms

	#define DIAGNOSTIC_FAILURE_DELAY_ms              30000
#elif (PAR_CUSTOMERINDEX_SELECTION==CUSTOMERINDEX_GEELY)
	#define CUSTOMER_DIAGNOSTIC_PERIOD_ms            10000
	#define CUSTOMER_DIAGNOSTIC_HIGH_ms                  0

	#define DIAGNOSTIC_HEART_BEAT_MS                   525 // ms
	#define DIAGNOSTIC_FAILURE_INTERNAL_ms            3525
	#define DIAGNOSTIC_FAILURE_HIGHTEMP_WARNING_ms    1525
	#define DIAGNOSTIC_FAILURE_HIGHTEMP_ERROR_ms      3025 
	#define DIAGNOSTIC_FAILURE_VOLTAGE_ms             2025
	#define DIAGNOSTIC_FAILURE_OVERLOAD_ms            2525
	#define DIAGNOSTIC_FAILURE_BLOCKAGE_ms            2525

	#define DIAGNOSTIC_FAILURE_DELAY_ms              30000

#elif PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_GAC
	#if PAR_CUSTOMERINTERFACE_SELECTION == CUSTOMERINTERFACE_LIN
		void LINDiagnostic_GAC(void);
		
	#else
	
		#define CUSTOMER_DIAGNOSTIC_PERIOD_ms                0
		#define CUSTOMER_DIAGNOSTIC_HIGH_ms               2000

		#define DIAGNOSTIC_HEART_BEAT_MS                  1000 // ms
		#define DIAGNOSTIC_FAILURE_INTERNAL_ms            3000
		//#define DIAGNOSTIC_FAILURE_HIGHTEMP_WARNING_ms       0
		#define DIAGNOSTIC_FAILURE_HIGHTEMP_ERROR_ms      2500 
		//#define DIAGNOSTIC_FAILURE_VOLTAGE_ms                0
		//#define DIAGNOSTIC_FAILURE_OVERLOAD_ms               0
		#define DIAGNOSTIC_FAILURE_BLOCKAGE_ms            4000
		#define DIAGNOSTIC_FAILURE_OVERCURR_ms            3500
		

		#define DIAGNOSTIC_FAILURE_DELAY_ms              30000
	#endif
	
	
#else

#endif

#endif
