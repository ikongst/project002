#ifndef __PROTECTION_H__
#define __PROTECTION_H__


/*
v012, 2022-12-01, kongyun: maximum speed set as 3000rpm.
v013, 2023-01-13, kongyun: add power error detection.
v014, 2023-02-01, kongyun: temperature/current/power protection optimized.
v015, 2023-04-24, kongyun: voltage protection updated, speed deviation updated.
v016, 2023-05-09, kongyun: temperature error 148<->146, derating 144.
v017, 2023-05-16, kongyun: temperature - current derating bug fixed.
      2023-06-07, kongyun: 8~11V, 10A ~ 35A
*/



#include "Common.h"

// you should modified this to 0, if you want to use this lib
#define LIB_GENERATION_PROTECTION       0

#if LIB_GENERATION_PROTECTION == 1
	// lib need .... 
	//---------------------------------------------------------------------
	#define LIB_PLATFORM_GEN1            0
	#define LIB_PLATFORM_400W            1
	#define LIB_PLATFORM_600W            2

	#define LIB_PLATFORM_SELECTION       LIB_PLATFORM_600W

	#if   (LIB_PLATFORM_SELECTION == LIB_PLATFORM_GEN1)\
			||(LIB_PLATFORM_SELECTION == LIB_PLATFORM_400W)
		#define SYSTEMPARAM_SPEED_MAX_rpm             2311
		#define SYSTEMPARAM_SPEED_MIN_rpm              625

		#define SYSTEMPARAM_POWER_MAX_mW            473000
		#define SYSTEMPARAM_POWER_RATE_mW           400000

		#define SYSTEMPARAM_CURRENT_MAX_mA           35000
		#define SYSTEMPARAM_CURRENT_RATE_mA          26000
	#elif LIB_PLATFORM_SELECTION == LIB_PLATFORM_600W
		#define SYSTEMPARAM_SPEED_MAX_rpm             2564
		#define SYSTEMPARAM_SPEED_MIN_rpm              625

		#define SYSTEMPARAM_POWER_MAX_mW            700000
		#define SYSTEMPARAM_POWER_RATE_mW           600000

		#define SYSTEMPARAM_CURRENT_MAX_mA           52000
		#define SYSTEMPARAM_CURRENT_RATE_mA          41000

	#endif

	#define SYSTEMPARAM_VOLTAGE_MAX_mV           17000
	#define SYSTEMPARAM_VOLTAGE_RATE_mV          13000
	#define SYSTEMPARAM_VOLTAGE_LOW_mV           11000
	#define SYSTEMPARAM_VOLTAGE_MIN_mV            8000


	#define PLATFORM_DELAY_BLOCKAGECHECK_10ms      800

		
	extern unsigned int guiSpeedSet;
	extern unsigned int guiTargetSpeed;
	extern unsigned int guiControlSpeed;
	extern unsigned int guiVoltage;
	extern unsigned int guiVoltage_nocalibration;
	extern unsigned int guiCurrent;
	extern unsigned int guiCurrent_nocalibration;
	extern unsigned int guiTemperature;
	extern unsigned int guiTemperature_nocalibration;
	extern unsigned int guiTemperatureNTC;
	extern unsigned int guiActualSpeed;
	extern unsigned char gucMotorDriveState;
	extern unsigned char gucMotorDriveStartupTime;

	unsigned int uigetPowererror(void);
	unsigned int uigetGDUerror(void);
	unsigned int uigetSCerror(void);
	unsigned int uigetOCerror(void);
	unsigned int uigetPBerror(void);
	unsigned int uigetCurOffsetVal(void);
	
//------------------------------------------------------------------------
#else
	#include "Common_LIB.h"
#endif


#define LIMIT_PROTECTION_SPEED_MIN_rpm        SYSTEMPARAM_SPEED_MIN_rpm
#define LIMIT_PROTECTION_SPEED_MAX_rpm        SYSTEMPARAM_SPEED_MAX_rpm

// definition of power limitation
#define LIMIT_LIMITPOWER_HIGH_1mW             SYSTEMPARAM_POWER_MAX_mW
#define LIMIT_LIMITPOWER_LOW_1mW              SYSTEMPARAM_POWER_RATE_mW
#define DELAY_LIMITPOWER_10ms                 100
#define LIMIT_LIMITPOWER_HYSTERESIS         15000 // 15W

// definition of current protection
#define LIMIT_LIMITCURRENT_HIGH_1mA           SYSTEMPARAM_CURRENT_MAX_mA
#define LIMIT_LIMITCURRENT_LOW_1mA            SYSTEMPARAM_CURRENT_RATE_mA
#define LIMIT_LIMITCURRENT_LOWVOLTAGE_1mA     10000
#define LIMIT_OVERCURRENT_HIGH_1mA            LIMIT_LIMITCURRENT_HIGH_1mA + 6000
#define LIMIT_OVERCURRENT_LOW_1mA             LIMIT_LIMITCURRENT_HIGH_1mA + 5000
#define DELAY_OVERCURRENT_10ms                500
#define DELAY_LIMITCURRENT_10ms               100
#define LIMIT_LIMITCURRENT_HYSTERESIS        1000 // 1A

// definition of volatge protection
#define LIMIT_OVERVOLTAGE_HIGH_1mv             SYSTEMPARAM_VOLTAGE_MAX_mV+1000
#define LIMIT_OVERVOLTAGE_LOW_1mv              SYSTEMPARAM_VOLTAGE_MAX_mV
#define LIMIT_VOLTAGE_RATE_1mv                 SYSTEMPARAM_VOLTAGE_RATE_mV
#define LIMIT_LOWVOLTAGE_HIGH_1mv              SYSTEMPARAM_VOLTAGE_LOW_mV
#define LIMIT_LOWVOLTAGE_LOW_1mv               SYSTEMPARAM_VOLTAGE_LOW_mV-500
#define LIMIT_UNDERVOLTAGE_HIGH_1mv            SYSTEMPARAM_VOLTAGE_MIN_mV
#define LIMIT_UNDERVOLTAGE_LOW_1mv             SYSTEMPARAM_VOLTAGE_MIN_mV-500 // motor reduce at low voltage.
#define DELAY_OVERVOLTAGE_10ms                 100
#define DELAY_LOWVOLTAGE_10ms                  100
#define DELAY_UNDERVOLTAGE_10ms                100

// definition of temperature warning and error
#define TEMP_OFFSET                            50
#define LIMIT_TEMPWARNING_1deg               (124+TEMP_OFFSET+20)//el-temp = ambient-temp + offset + 20
#define LIMIT_TEMPERROR_1deg                 (128+TEMP_OFFSET+20)//el-temp = ambient-temp + offset + 20
#define LIMIT_TEMPMAX_1deg                   (150+TEMP_OFFSET)//el-temp
#define DELAY_TEMPWARNING_10ms                500
#define DELAY_TEMPERROR_10ms                18000
#define LIMIT_LIMITTEMP_HYSTERESIS              1 // 1deg-C

#define LIMIT_HIGHLOW_THRESHOLD_HIGH_1deg    (115+TEMP_OFFSET+20) //el-temp = ambient-temp + offset + 20
#define LIMIT_HIGHLOW_THRESHOLD_LOW_1deg     (100+TEMP_OFFSET+20) //el-temp = ambient-temp + offset + 20

// definition of overload and blockage
#define LIMIT_SPEEDDEVIATIONS_HIGH_rpm       1100
#define LIMIT_SPEEDDEVIATIONS_MID_rpm         800
#define LIMIT_SPEEDDEVIATIONS_LOW_rpm         500
#define DELAY_SPEEDDEVIATIONS_10ms           6000

#define FILTER_BLOCKAGE_COUNTER                 6
#define DELAY_BLCOKAGECHECK_10ms              PLATFORM_DELAY_BLOCKAGECHECK_10ms
#define DELAY_BLCOKAGECHECK_Long_10ms         (DELAY_BLCOKAGECHECK_10ms*2) // at low temp. twice startup time.
#define LIMIT_BLOCKAGE_rpm                    200

// definition of electroncis protection.
#define PERIOD_GDU_10ms                       100
#define FILTER_GDU_COUNTER                     10
#define PERIOD_SC_10ms                        100
#define FILTER_SC_COUNTER                      10
#define PERIOD_PB_10ms                        100
#define FILTER_PB_COUNTER                      10
#define PERIOD_OC_10ms                        100
#define FILTER_OC_COUNTER                      10
#define PERIOD_POWER_10ms                     100
#define FILTER_POWER_COUNTER                   10
#define LIMIT_CUROFFSET_LOW_dig              1500
#define LIMIT_CUROFFSET_HIGH_dig             1800
#define DELAY_CUROFFSET_10ms                  200
#define FILTER_BACK_COUNTER                     2


#define LIMITATION_SPEED_STEP_rpm               1
#define LIMITATION_SPEED_RATE_10ms             25

#define LIMITATION_CURRENT_STEP_rpm             1
#define LIMITATION_CURRENT_RATE_10ms           25

#define LIMITATION_POWER_STEP_rpm               1
#define LIMITATION_POWER_RATE_10ms             25

#define LIMITATION_TEMP_STEP_rpm                1
#define LIMITATION_TEMP_RATE_10ms              25

//unsigned int currentlimitation(unsigned int speedlimitinput, unsigned char limitflag);
//unsigned int powerlimitation(unsigned int speedlimitinput, unsigned char limitflag);
//unsigned int temperaturelimitation(unsigned int speedlimitinput, unsigned char limitflag);

// internal functions will be called by Protection_Mian()
unsigned char overvoltage_protection(unsigned int voltagevalue, unsigned int minlimit, unsigned int maxlimit, unsigned int filtertime);
unsigned char lowvoltage_protection(unsigned int voltagevalue, unsigned int minlimit, unsigned int maxlimit, unsigned int filtertime);
unsigned char undervoltage_protection(unsigned int voltagevalue, unsigned int minlimit, unsigned int maxlimit, unsigned int filtertime);
unsigned char overcurrent_protection(unsigned int currentvalue, unsigned int minlimit, unsigned int maxlimit, unsigned int filtertime);
unsigned char limitcurrent_protection(unsigned int currentvalue, unsigned int minlimit, unsigned int maxlimit, unsigned int filtertime);
unsigned char limitpower_protection(unsigned int voltagevalue, unsigned int currentvalue, unsigned int minlimit, unsigned int maxlimit, unsigned int filtertime);
unsigned char temperaturewarning_protection(unsigned int temperaturevalue, unsigned int deratinglimit, unsigned int deratingfilter);
unsigned char temperatureerror_protection(unsigned int temperaturevalue, unsigned int distorylimit, unsigned int distoryfilter);
unsigned char overload_protection(unsigned int setspeedvalue, unsigned int actualspeedvalue, unsigned int speeddeviationlimit, unsigned int speeddeviationdelay);
unsigned char blockage_protection(unsigned int setspeedvalue, unsigned int actualspeedvalue, unsigned int stalllimit, unsigned char stallcounterlimit, unsigned int stallfilter, unsigned char motordrivestatus);

// electronics protection lists.
unsigned char el_GDU_protection(unsigned int electricerror, unsigned int filterperiod, unsigned int electricerrorlimit);
unsigned char el_shortcircuit_protection(unsigned int electricerror, unsigned int filterperiod, unsigned int electricerrorlimit);
unsigned char el_phasesbroken_protection(unsigned int electricerror, unsigned int filterperiod, unsigned int electricerrorlimit);
unsigned char el_overcurrentHW_protection(unsigned int electricerror, unsigned int filterperiod, unsigned int electricerrorlimit);
unsigned char el_POWER_protection(unsigned int electricerror, unsigned int filterperiod, unsigned int electricerrorlimit);
unsigned char el_currentoffset_protection(unsigned int offsetvalue, unsigned int offsetmin, unsigned int offsetmax, unsigned int filtertime);


#define ELECTRONICS_ERROR_NA       0
#define ELECTRONICS_ERROR_GDU      1
#define ELECTRONICS_ERROR_SC       2
#define ELECTRONICS_ERROR_PB			 3
#define ELECTRONICS_ERROR_OC       4
#define ELECTRONICS_ERROR_POWER    5
extern unsigned int electronicserrorcounter;
extern unsigned int electronicserrorcounter2;
extern unsigned int electronicserrorcounter3;
extern unsigned int electronicserrorcounter4;
extern unsigned int electronicserrorcounter5;
extern unsigned char gucOneElectronicsError;

extern typeS32 sslsumcurrentdelta;
extern typeS32 sslsumpowerdelta;
extern typeS32 sslsumtempdelta;

extern unsigned char gucOneBlockedFlag;
extern unsigned char gucBlockedCounter;
extern unsigned int blockageprotectioncounter;
extern unsigned char gucOneOverloadFlag;
extern unsigned char gucOneOverSpeedFlag;
extern FailureFlagStructure gProtectionFlags;
extern unsigned int guiMaxSpeedCalculated;
extern unsigned int guiMinSpeedCalculated;
extern unsigned int guiLibVersion_Protection;

void Protection_Main(void);

extern typeS32 speedlimitcurrent;
extern typeS32 speedlimitpower;
extern typeS32 speedlimittemp;
	
#endif
