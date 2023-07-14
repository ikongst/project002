#ifndef __SYSTEMPARAM_H__
#define __SYSTEMPARAM_H__

#include "Common.h"
#include "ProjectConfig.h"

// interface definition
#define DEF_INTERFACE_LIN     0
#define DEF_INTERFACE_PWM     1
#define DEF_INTERFACE_DEFAULT 0


#if   (PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_PLATFORM)\
		||(PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_GWM)
	// definitio of interface type
	#define SYSTEMPARAM_INTERFACE                  DEF_INTERFACE_PWM

	// definition of pwm input
	#define SYSTEMPARAM_PWM_FREQ_LOW_0_1_Hz            75
	#define SYSTEMPARAM_PWM_FREQ_HIGH_0_1_Hz          125
	#define SYSTEMPARAM_PWM_DUTY_LOW_0_1_pres           0
	#define SYSTEMPARAM_PWM_DUTY_HIGH_0_1_pres       1000

#if PAR_MOTOR_SELECTION == MOTOR_PLATFORM_400W
	#define SYSTEMPARAM_SPEED_MAX_rpm                2311
	#define SYSTEMPARAM_SPEED_RATE_rpm               2311
	
	#define SYSTEMPARAM_SPEED_MIN_rpm                 625
	#define SYSTEMPARAM_SPEEDCURVE_MAX_dig             25
	#define SYSTEMPARAM_SPEEDCURVE_MIN_dig            111
#elif PAR_MOTOR_SELECTION == MOTOR_PLATFORM_600W
	#define SYSTEMPARAM_SPEED_MAX_rpm                2564
	#define SYSTEMPARAM_SPEED_RATE_rpm               2564
	
	#define SYSTEMPARAM_SPEED_MIN_rpm                 625
	#define SYSTEMPARAM_SPEEDCURVE_MAX_dig             19
	#define SYSTEMPARAM_SPEEDCURVE_MIN_dig            111
#else
	#define SYSTEMPARAM_SPEED_MAX_rpm                2300
	#define SYSTEMPARAM_SPEED_RATE_rpm               2300  
	
	#define SYSTEMPARAM_SPEED_MIN_rpm                 625
	#define SYSTEMPARAM_SPEEDCURVE_MAX_dig             19
	#define SYSTEMPARAM_SPEEDCURVE_MIN_dig            111
#endif
	
#elif PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_GEELY
	// definitio of interface type
	#define SYSTEMPARAM_INTERFACE                  DEF_INTERFACE_PWM

	// definition of pwm input
	#define SYSTEMPARAM_PWM_FREQ_LOW_0_1_Hz           960
	#define SYSTEMPARAM_PWM_FREQ_HIGH_0_1_Hz         3100
	#define SYSTEMPARAM_PWM_DUTY_LOW_0_1_pres           0
	#define SYSTEMPARAM_PWM_DUTY_HIGH_0_1_pres       1000

	#if PAR_PROJECTS_SELECTION == GEELY_SS11_600W
		#define SYSTEMPARAM_SPEED_MAX_rpm              2500
		#define SYSTEMPARAM_SPEED_RATE_rpm             2500
		#define SYSTEMPARAM_SPEED_MIN_rpm               750
		
	#else
		#define SYSTEMPARAM_SPEED_MAX_rpm              2300
		#define SYSTEMPARAM_SPEED_RATE_rpm             2300
		#define SYSTEMPARAM_SPEED_MIN_rpm               700	
		
	#endif	
	#define SYSTEMPARAM_SPEEDCURVE_MAX_dig              8
	#define SYSTEMPARAM_SPEEDCURVE_MIN_dig            112
	
#elif PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_GAC

	#if PAR_PROJECTS_SELECTION==GAC_A20_400W
		// definitio of interface type
		#define SYSTEMPARAM_INTERFACE                  DEF_INTERFACE_PWM

		// definition of pwm input
		#define SYSTEMPARAM_PWM_FREQ_LOW_0_1_Hz          50
		#define SYSTEMPARAM_PWM_FREQ_HIGH_0_1_Hz       1500
		#define SYSTEMPARAM_PWM_DUTY_LOW_0_1_pres         0
		#define SYSTEMPARAM_PWM_DUTY_HIGH_0_1_pres     1000

		#define SYSTEMPARAM_SPEED_MAX_rpm              2300
		#define SYSTEMPARAM_SPEED_RATE_rpm             2300
		#define SYSTEMPARAM_SPEED_MIN_rpm               700
		#define SYSTEMPARAM_SPEEDCURVE_MAX_dig           15
		#define SYSTEMPARAM_SPEEDCURVE_MIN_dig          115
	
	#elif PAR_PROJECTS_SELECTION==GAC_A02_400W
				// definitio of interface type
		#define SYSTEMPARAM_INTERFACE                  DEF_INTERFACE_LIN

		// definition of pwm input
		#define SYSTEMPARAM_PWM_FREQ_LOW_0_1_Hz          50
		#define SYSTEMPARAM_PWM_FREQ_HIGH_0_1_Hz       1500
		#define SYSTEMPARAM_PWM_DUTY_LOW_0_1_pres         0
		#define SYSTEMPARAM_PWM_DUTY_HIGH_0_1_pres     1000

		#define SYSTEMPARAM_SPEED_MAX_rpm              2900
		#define SYSTEMPARAM_SPEED_RATE_rpm             2900
		#define SYSTEMPARAM_SPEED_MIN_rpm               700
		#define SYSTEMPARAM_SPEEDCURVE_MAX_dig           13
		#define SYSTEMPARAM_SPEEDCURVE_MIN_dig           90
		
	#else
	
	#endif
	
#else
	// definitio of interface type
	#define SYSTEMPARAM_INTERFACE                  DEF_INTERFACE_PWM

	// definition of pwm input
	#define SYSTEMPARAM_PWM_FREQ_LOW_0_1_Hz          xx
	#define SYSTEMPARAM_PWM_FREQ_HIGH_0_1_Hz        xxx
	#define SYSTEMPARAM_PWM_DUTY_LOW_0_1_pres         x
	#define SYSTEMPARAM_PWM_DUTY_HIGH_0_1_pres     xxxx

	#define SYSTEMPARAM_SPEED_MAX_rpm              2x00
	#define SYSTEMPARAM_SPEED_RATE_rpm             2x00
	#define SYSTEMPARAM_SPEED_MIN_rpm               600
	#define SYSTEMPARAM_SPEEDCURVE_MAX_dig            8
	#define SYSTEMPARAM_SPEEDCURVE_MIN_dig          112
	
#endif


// definition of voltage
#define SYSTEMPARAM_VOLTAGE_MAX_mV              17000
#define SYSTEMPARAM_VOLTAGE_RATE_mV             13000
#define SYSTEMPARAM_VOLTAGE_LOW_mV              11000
#define SYSTEMPARAM_VOLTAGE_MIN_mV               8000


// definition of power and current
#if (PAR_MOTOR_SELECTION == MOTOR_PLATFORM_GEN1)\
   ||(PAR_MOTOR_SELECTION == MOTOR_PLATFORM_400W)
	#define SYSTEMPARAM_POWER_MAX_mW             473000
	#define SYSTEMPARAM_POWER_RATE_mW            400000

	#define SYSTEMPARAM_CURRENT_MAX_mA            35000
	#define SYSTEMPARAM_CURRENT_RATE_mA           26000
#elif PAR_MOTOR_SELECTION == MOTOR_PLATFORM_600W
	#define SYSTEMPARAM_POWER_MAX_mW             700000
	#define SYSTEMPARAM_POWER_RATE_mW            600000

	#define SYSTEMPARAM_CURRENT_MAX_mA            52000
	#define SYSTEMPARAM_CURRENT_RATE_mA           41000
#endif


// definition of emergency mode
#if   (PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_PLATFORM)\
		||(PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_GWM)
	#define SYSTEMPARAM_EMERGENCYMODE_HIGH_000_ENABLE     KONGENABLE
	#define SYSTEMPARAM_EMERGENCYMODE_HIGH_100_ENABLE     KONGENABLE
	#define SYSTEMPARAM_EMERGENCYMODE_HIGH_XXX_ENABLE     KONGENABLE
	#define SYSTEMPARAM_EMERGENCYMODE_DELAY_10ms          1000 // 10 sec delay to enter into emergency mode.
	#define SYSTEMPARAM_INVALID_RANGE(x)                  ((x<50)||(x>950))
	
#elif PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_GEELY
	#define SYSTEMPARAM_EMERGENCYMODE_HIGH_000_ENABLE     KONGENABLE    // low, as 100%, full speed.
	#define SYSTEMPARAM_EMERGENCYMODE_HIGH_100_ENABLE     KONGDISABLE   // high, as 0%, stop mode.
	#define SYSTEMPARAM_EMERGENCYMODE_HIGH_XXX_ENABLE     KONGDISABLE
	#define SYSTEMPARAM_EMERGENCYMODE_DELAY_10ms          100 // 1 sec delay to enter into emergency mode.
	#define SYSTEMPARAM_INVALID_RANGE(x)                    0 //
	
#elif PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_GAC
	#define SYSTEMPARAM_EMERGENCYMODE_HIGH_000_ENABLE     KONGENABLE    // low, as 100%, full speed.
	#define SYSTEMPARAM_EMERGENCYMODE_HIGH_100_ENABLE     KONGENABLE    // high, as 0%, stop mode.
	#define SYSTEMPARAM_EMERGENCYMODE_HIGH_XXX_ENABLE     KONGDISABLE
	#define SYSTEMPARAM_EMERGENCYMODE_DELAY_10ms          100 // 1 sec delay to enter into emergency mode.
	#define SYSTEMPARAM_INVALID_RANGE(x)                    0 //
	
#else
	#define SYSTEMPARAM_EMERGENCYMODE_HIGH_000_ENABLE     KONGDISABLE
	#define SYSTEMPARAM_EMERGENCYMODE_HIGH_100_ENABLE     KONGDISABLE
	#define SYSTEMPARAM_EMERGENCYMODE_HIGH_XXX_ENABLE     KONGDISABLE
	#define SYSTEMPARAM_EMERGENCYMODE_DELAY_10ms          100 // 1 sec delay to enter into emergency mode.
	#define SYSTEMPARAM_INVALID_RANGE(x)                    0 //
	
#endif


// definition of enable/KL15 signal.
#if   (PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_PLATFORM)\
		||(PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_GWM)
	#define SYSTEMPARAM_ENABLE_KL15_HAVE                KONGENABLE
	#define SYSTEMPARAM_FLASHMODE_HAVE                  KONGENABLE
	
#else
	#define SYSTEMPARAM_ENABLE_KL15_HAVE                KONGDISABLE
	#define SYSTEMPARAM_FLASHMODE_HAVE                  KONGDISABLE
	
#endif


// environment temp. definition. not use, just a reminder.
#define SYSTEMPARAM_TEMPERATURE_WARNING_1deg          135 // environment temp.
#define SYSTEMPARAM_TEMPERATURE_ERROR_1deg            145 // environment temp.

#endif

