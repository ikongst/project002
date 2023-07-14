/******************************************************************************
*
* Copyright 2006-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2018 NXP
*
******************************************************************************/
/*!
*
* @file     pwm_control.h
*
* @date     JUN-12-2018
*
* @brief    PWM Control signal processing - Duty cycle measurement for 
* 			automotive-specific PWM Command control
*
*******************************************************************************
*
*
******************************************************************************/

#ifndef PWM_CONTROL_H_
#define PWM_CONTROL_H_
#include "mlib.h"									//tFrac16 type and FRAC16 macro

/* PWM Control status bits */
typedef struct
{
	unsigned int		pinState 		: 1;		//State of the input pin
	unsigned int		risingEdge 		: 1;		//Rising edge detected
	unsigned int		fallingEdge		: 1;		//Falling edge detected
	unsigned int		periodDetected	: 1;		//Modulation frequency detected
	unsigned int		valueDetected 	: 1;		//Duty cycle value detected
	unsigned int		fault			: 1;		//Fault flag
	unsigned int						: 10;		//Reserved
} pwmControlStatus_t;

/* PWM Control configuration */
/*
 * O  |                  _____
 * u  |                 /
 * t  |                /
 * p  |               / 
 * u  |              / 
 * t  |       __<___/
 *[%] |______|__>__|___________
 *   (0) (1)(2)   (3)  (4)   (5)
 *         PWM Duty Cycle [%]
 *  
 *  (0) ... Duty cycle is undetectable or the signal is low, the output is defined by noSignalOutput
 *  (1) ... noSignalLevel, 			the output is defined by noSignalOutput
 *  (2) ... hystLowSignalOff, 		the output is defined by lowSignalOutput and linearSignalOutputMin
 *  (3) ... hystLowSignalOn, 		the output is defined by linearSignalOutputMin
 *  (4) ... linearSignalLevelMax, 	the output is defined by linearSignalOutputMax
 *  (5) ... Duty cycle is undetectable or the signal is high, the output is defined by linearSignalOutputMax
 * Areas:
 *  (0) - (1) ..... No signal area (defined from 0% to noSignalLevel with output of noSignalOutput)
 *  (1) - (2) ..... Low signal area, between (1) and (2), the output is lowSignalOutput
 *  (2) - (3) ..... Linear signal area with hysteresis. The output remains lowSignalOutput
 *  				if the duty cycle stays below (3) defined by lowSignalOutput.
 *  				Falling duty cycle between (3) and (2), the output is defined by linearSignalOutputMin
 *  (3) - (4) ..... Linear signal area, the output is defined by dutyCycle*linearSignalSlope + linearSignalShift
 *  (4) - (5) ..... High signal area, the output is defined by linearSignalOutputMax
 *  	
 *  
 * */
typedef struct
{
	/* No signal definition */
	tFrac16					noSignalLevel;			//Level of the duty cycle for NoSignal detection
	tFrac16					noSignalOutput;			//Output when NoSignal is detected
	/* Low signal definition */
	tFrac16					lowSignalOutput;		//Output when LowSignal is detected
	/* Linear signal definition */
	tFrac16					hystLowSignalOff;		//LowSignal-to-NoSignal hysteresis level
	tFrac16					hystLowSignalOn;		//NoSignal-to-LowSignal hysteresis level
	tFrac16					linearSignalLevelMax;	//Level of the duty cycle for LinearSignal saturation
	tFrac16					linearSignalOutputMin;	//Output at hystLowSignalOn
	tFrac16					linearSignalOutputMax;	//Output at linearSignalLevelMax
	tFrac16					linearSignalSlope;		// (linearSignalOutputMax - linearSignalOutputMin)/(hystLowSignalOn - linearSignalLevelMax))
	tFrac16					linearSignalShift;		//  linearSignalOutputMax - (linearSignalSlope * linearSignalLevelMax)
	
	/* timing settings */
	unsigned int			minPeriod;				//minimal period of the signal to be detected, shorter period leads to PWM_NoSignalDetect
	unsigned int			maxPeriod;				//maximal period of the signal to be detected, longer period leads to PWM_NoSignalDetect
} pwmControlConfig_t;

/* PWM Control data structure */
typedef struct
{
		pwmControlStatus_t	flags;					//Control status bits
		pwmControlConfig_t	config;					//Configuration
		unsigned int		period;					//Modulation period
		unsigned int		dutyCycle;				//dutyCycle
		unsigned int		hystDutyCycle;			//previous hysteresis of duty cycle

#ifndef PWM_CONTROL_SW
		unsigned int		overflowCntr;			//timer overflow counter
#endif
		tFrac16				outputValue;			//Output value
		unsigned int		ControlInputClass;		//Classification of the input signal
} pwmControl_t;

/* PWM Control levels definition */
typedef enum
{
	PWM_NoSignalDetect	=	0,
	PWM_LowSignalDetect =	1,
	PWM_LinearCtrlDetect =	2,
	PWM_HighSignalDetect = 	3	
} pwmControlInputRange_Enum;

/* Exported function headers */
extern void 		        PWMControlInit(pwmControl_t * data);
extern unsigned int         PWMControlUpdate(unsigned int pin, pwmControl_t * data);
extern tFrac16 		        PWMControlGetOutputValue(pwmControl_t * data);
extern unsigned char		PWMControlTimerOverflow(pwmControl_t * data);

#endif /* PWM_CONTROL_H_ */
