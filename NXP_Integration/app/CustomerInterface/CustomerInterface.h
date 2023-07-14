#ifndef __CUSTOMERINTERFACE_H__
#define __CUSTOMERINTERFACE_H__


/*
 * 
v001, 2023-7-11, kongyun: initial version
 */

#include "Common.h"

// you should modified this to 0, if you want to use this lib
#define LIB_GENERATION_CUSTOMERINTERFACE       0

#if LIB_GENERATION_CUSTOMERINTERFACE == 1
    // lib need .... 
	//---------------------------------------------------------------------
	#define LIB_PLATFORM_GEN1            0
	#define LIB_PLATFORM_400W            1
	#define LIB_PLATFORM_600W            2

	#define LIB_PLATFORM_SELECTION       LIB_PLATFORM_600W

	#if   (LIB_PLATFORM_SELECTION == LIB_PLATFORM_GEN1)\
			||(LIB_PLATFORM_SELECTION == LIB_PLATFORM_400W)
		#define SYSTEMPARAM_SPEED_MAX_rpm                2311
		#define SYSTEMPARAM_SPEED_RATE_rpm               2311
		
		#define SYSTEMPARAM_SPEED_MIN_rpm                 625
		#define SYSTEMPARAM_SPEEDCURVE_MAX_dig             25
		#define SYSTEMPARAM_SPEEDCURVE_MIN_dig            111
    #elif LIB_PLATFORM_SELECTION == LIB_PLATFORM_600W
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

	#define DEF_INTERFACE_LIN     0
	#define DEF_INTERFACE_PWM     1
	#define DEF_INTERFACE_DEFAULT 0
    #define SYSTEMPARAM_INTERFACE    DEF_INTERFACE_PWM

	// definition of pwm input
	#define SYSTEMPARAM_PWM_FREQ_LOW_0_1_Hz            75
	#define SYSTEMPARAM_PWM_FREQ_HIGH_0_1_Hz          125
	#define SYSTEMPARAM_PWM_DUTY_LOW_0_1_pres           0
	#define SYSTEMPARAM_PWM_DUTY_HIGH_0_1_pres       1000

	#define SYSTEMPARAM_EMERGENCYMODE_HIGH_000_ENABLE     KONGENABLE
	#define SYSTEMPARAM_EMERGENCYMODE_HIGH_100_ENABLE     KONGENABLE
	#define SYSTEMPARAM_EMERGENCYMODE_HIGH_XXX_ENABLE     KONGENABLE
	#define SYSTEMPARAM_EMERGENCYMODE_DELAY_10ms          1000 // 10 sec delay to enter into emergency mode.
	#define SYSTEMPARAM_INVALID_RANGE(x)                  ((x<50)||(x>950))

	#define SYSTEMPARAM_ENABLE_KL15_HAVE                KONGENABLE
	#define SYSTEMPARAM_FLASHMODE_HAVE                  KONGENABLE



	extern unsigned int guiDiagnosticLowTime;
	extern unsigned int guiMaxSpeedCalculated;
	extern unsigned int guiMinSpeedCalculated;
	
	
    void BSW_PWM_Init(void);
    void PWMDetection_Init(void);
    void BSW_LIN_Init(void);
    unsigned int uigetlinsignal(void);
    
    unsigned char ucgetPINInterfaceStatus(void);
    unsigned char ucgetPINEnableStatus(void);
    
    
    void settrriger_rise(void);
    void settrriger_fall(void);
    unsigned int gettimercntr(void);
    long gettimerclk(void);
    
	#define PWMDETECTION_SET_EDGE_RISE()   settrriger_rise()//TIMER2->T2MOD.bit.EDGESEL = 1u
	#define PWMDETECTION_SET_EDGE_FALL()   settrriger_fall//TIMER2->T2MOD.bit.EDGESEL = 0u
	#define PWMDETECTION_GET_CAPTURE()     gettimercntr()//TIMER2_Get_Capture()
	#define PWMDETECTION_GETTIMER_CLK()    gettimerclk()//PWM2_CLK
    

#else
    #include "Common_LIB.h"
#endif


#define INTERFACE_LIN  DEF_INTERFACE_LIN
#define INTERFACE_PWM  DEF_INTERFACE_PWM

#define CUSTOMER_REQ_INTERFACE_TYPE                    SYSTEMPARAM_INTERFACE

#define CUSTOMER_REQ_MINSPEED_rpm                      SYSTEMPARAM_SPEED_MIN_rpm
#define CUSTOMER_REQ_MAXSPEED_rpm                      SYSTEMPARAM_SPEED_MAX_rpm

#define LIMIT_PWM_FREQ_LOW_0_1Hz                       SYSTEMPARAM_PWM_FREQ_LOW_0_1_Hz  //  8 Hz
#define LIMIT_PWM_FREQ_HIGH_0_1Hz                      SYSTEMPARAM_PWM_FREQ_HIGH_0_1_Hz  // 12 Hz
#define LIMIT_PWM_DUTY_LOW_pres                        SYSTEMPARAM_PWM_DUTY_LOW_0_1_pres  //   0%
#define LIMIT_PWM_DUTY_HIGH_pres                       SYSTEMPARAM_PWM_DUTY_HIGH_0_1_pres  // 100%

#define LIMIT_PWM_FREQ_DEVIATION_MAX_0_1Hz             10 // 1Hz
#define LIMIT_PWM_DUTY_DEVIATION_MAX_0_1pres           10 // 1%

#define FILTER_PWM_DUTY_MAX_COUNTER                    7
#define FILTER_PWM_DUTY_VALID_COUNTER                  6
#define LIMIT_PWM_DUTY_INVALID_ALLOWED_COUNTER         (FILTER_PWM_DUTY_MAX_COUNTER-FILTER_PWM_DUTY_VALID_COUNTER)
#define CUSTOMER_REQ_PWM_INPUTSIGNAL_CLEARDELAY_1ms    1000

#define CUSTOMER_REQ_EMERGENCYMODE_000_ENABLE          SYSTEMPARAM_EMERGENCYMODE_HIGH_000_ENABLE  // 100%
#define CUSTOMER_REQ_EMERGENCYMODE_100_ENABLE          SYSTEMPARAM_EMERGENCYMODE_HIGH_100_ENABLE  //   0%
#define CUSTOMER_REQ_EMERGENCYMODE_XXX_ENABLE          SYSTEMPARAM_EMERGENCYMODE_HIGH_XXX_ENABLE  // invalid %
#define CUSTOMER_REQ_EMERGENCYMODE_ENTERDELAY_10ms     SYSTEMPARAM_EMERGENCYMODE_DELAY_10ms  // 

#define CUSTOMER_REQ_LIN_INPUTSIGNAL_CLEARDELAY_1ms    4000
#define CUSTOMER_REQ_ENABLE_KL15_ENABLE                SYSTEMPARAM_ENABLE_KL15_HAVE
#define CUSTOMER_REQ_INVALID_RANGE(x)                  SYSTEMPARAM_INVALID_RANGE(x)

#define SPEEDREGULATION_HYSTHERESIS_dig                  2
#define SPEEDREGULATION_HYSTHERESIS_rpm                100
#define FILTER_HIGHLOWCHECK_10ms                       100
#define FILTER_KL15ENABLE_10ms                         100 // KL15 filter 1 sec.
#define FILTER_LINRESPONSEERROR_10ms                   120 // 120 *10 = 1.2sec, response error will be sent after 1.2sec.
#define DELAY_INTERFACESTATUS_TRANSFERTO_LIN_1ms       1000
#define DELAY_INTERFACESTATUS_TRANSFERTO_PWM_1ms       200

#if SYSTEMPARAM_FLASHMODE_HAVE == KONGENABLE
	#define FLASH_START_PWMSIGNAL_FREQ_MAX_0_1_Hz       2200  // 220Hz
	#define FLASH_START_PWMSIGNAL_FREQ_MIN_0_1_Hz       1800  // 180Hz
	#define FLASH_START_PWMSIGNAL_DUTY_MIN_0_1_pres      450  // 45%
	#define FLASH_START_PWMSIGNAL_DUTY_MAX_0_1_pres      550  // 55%

	#define FLASH_START_FILTER_SIGNALKEEP_COUNTER       4000  // period 1ms, -> 400ms
	#define FLASH_START_STEP_COUNTER                      10
	#define FLASH_STOP_FILTER_INPUTVALID_COUNTER       50000  // period 1ms, -> 5s exist flash mode when valid signal.
	#define FLASH_STOP_STEP_COUNTER                       10
#endif

extern unsigned char gucLINResponseError;
extern unsigned char gucLINGotoSleepFlag;

extern unsigned int guiTargetSpeed;
extern unsigned int guiControlSpeed;
extern unsigned int guiActualSpeed;

extern unsigned int guiPWMSignal_Freq;
extern unsigned int guiPWMSignal_Duty;
extern unsigned int guiLINSignal_Digital;
extern unsigned char gucPINInterfaceStatus;
extern unsigned char gucPINInterfacePullDownStatus;
extern unsigned char gucPINKL15EnableStatus;
extern unsigned char gucHighLowStatus;
extern unsigned char gucPWMInvalidStatus;

extern unsigned char gucPWMSignalFlashStartFlag;
extern unsigned char gucPWMSignalDetectedFlag;
extern unsigned char gucLINSignalReceivedFlag;
extern unsigned char gucLINEOLServiceReceivedFlag;
extern unsigned int guiLINEOLServiceCounter;

extern unsigned char gucInterfaceStatus;

void CustomerInterface_Main(void);   // called 10ms period
void InputSignalDetection(void);    // called 1ms period

extern unsigned int guiLibVersion_CustomerInterface;

#endif

