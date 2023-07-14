/*
 * pwm_control.c
 *
 *  Created on: Feb 12, 2016
 *      Author: B56863
 */
#include "pwm_control.h"
#include "mlib.h"

/**************************************************************************//*!
@brief 			Init all the state variables and do the init calculations

@param[in,out]  in: pwmControl_t 	 - parameters and data to be processed

@return			nothing
******************************************************************************/
void PWMControlInit(pwmControl_t * data)
{
	data->flags.risingEdge = 1;
	data->flags.fallingEdge = 0;
	data->flags.fault = 0;
	data->flags.periodDetected = 0;
	data->flags.valueDetected = 0;
	data->period = 0;
	data->dutyCycle = 0;
	data->outputValue = 0;
	data->overflowCntr = 0;
	
	data->ControlInputClass = PWM_NoSignalDetect;
}

/**************************************************************************//*!
@brief 			Check the PWM input signal, calculate period and duty cycle
 	 	 		Call this function within an input capture interrupt of a timer

@param[in,out]  in 				 - input capture register
				pwmControl_t 	 - parameters and data to be processed

@return			Value detected flag (1 - OK, 0 - in progress)
******************************************************************************/
unsigned int PWMControlUpdate(unsigned int in, pwmControl_t * data)
{
	static unsigned int highImpulse = 0;
	static unsigned int lowImpulse = 0;
	static unsigned int prevIn = 0;
	
	data->flags.fault = 0;									//Clear the faults
	
	if(data->flags.risingEdge)								//Rising edge has been detected
	{
		data->flags.risingEdge = 0;							//switch to the falling edge detection
		data->flags.fallingEdge = 1;
		
		lowImpulse = (data->overflowCntr<<16)+in - prevIn;							//save the time between current and previous edge as a low pulse length
		
		data->overflowCntr = 0;								//clear the overflow counter
	}
	else													
	{
		if(data->flags.fallingEdge)							//Falling edge has been detected
		{
			data->flags.risingEdge = 1;						//switch to the rising edge detection
			data->flags.fallingEdge = 0;					
			highImpulse = (data->overflowCntr<<16)+in - prevIn;						//save the time between current and previous edge as a high pulse length
		}
		
		//if((data->flags.fault))								//If a fault has been detected, clear the flags to start over
		//{
		//	prevIn = 0;
		//	highImpulse = 0;
		//	lowImpulse = 0;
		//	data->flags.valueDetected = 0;
		//}
	}
	
	///Period detection
	if((highImpulse > 0)&&(lowImpulse > 0))					// If both low and high pulse have been detected
	{														// Calculate the period and check for the min and max
		data->period = (highImpulse>>1) + (lowImpulse >> 1);
		if((data->period > data->config.maxPeriod)||(data->period < data->config.minPeriod))
		{
			data->flags.periodDetected = 0;
			//data->flags.fault |= 1;
		}
		//if(data->overflowCntr > 0)							// Check for the overflow flag
		//	data->flags.periodDetected = 1;
	}
	else
	{
		data->flags.periodDetected = 0;
		//data->flags.fault |= 1;
	}
	
	///Duty cycle calculation
	if((highImpulse > 0)&&(data->flags.periodDetected)&&(data->period > 0))
	//{
		data->dutyCycle = MLIB_DivSat_F16((highImpulse >> 2), (data->period)>>1);
	//	data->flags.valueDetected = 1;
	//}
	//else
	//{
	//	data->flags.valueDetected = 0;
	//	data->flags.fault |= 1;
	//}
	
	prevIn = in;										//Store current time for the next sample
	return data->flags.periodDetected;
}


/**************************************************************************//*!
@brief 			Timer Overflow handling
 	 	 		Call this function within a timer overflow 

@param[in,out]  pwmControl_t 	 - parameters and data to be processed

@return			Value detected flag (1 - OK, 0 - in progress)
******************************************************************************/
unsigned char PWMControlTimerOverflow(pwmControl_t * data)
{
 #ifndef PWM_CONTROL_SW
	
	data->overflowCntr++;
	if(data->overflowCntr > 3)
	{
		//PWMControlInit(data);
		data->flags.fault |= 1;
	}
	return data->flags.fault;
 #endif
}

/**************************************************************************//*!
@brief 			Output value calculation
 	 	 		Call this function whenever a new updated value is needed 

@param[in,out]  pwmControl_t 	 - parameters and data to be processed

@return			Output value
******************************************************************************/
tFrac16 PWMControlGetOutputValue(pwmControl_t * data)
{
	tFrac16 retVal = FRAC16(0.0);

	//Clasify the input based on the duty cycle
	if(data->dutyCycle < data->config.noSignalLevel)			//No detection
		data->ControlInputClass = PWM_NoSignalDetect;
	else
	{
		if(data->dutyCycle < data->config.hystLowSignalOff)		//Low signal
		{
			data->ControlInputClass = PWM_LowSignalDetect;
		}
		else													//Linear response with hysteresis
		{
			if((data->dutyCycle >= data->config.hystLowSignalOn)&&(data->dutyCycle <= data->config.linearSignalLevelMax))
				data->ControlInputClass = PWM_LinearCtrlDetect;
			else
			{
				if(data->dutyCycle > data->config.linearSignalLevelMax)	//High signal, full output
					data->ControlInputClass = PWM_HighSignalDetect;
			}
		}
	}
	
	if(data->flags.fault)
	{
		data->ControlInputClass = PWM_NoSignalDetect;
		return 0;
	}
	//Calculate the output based on the class
	switch(data->ControlInputClass)
	{
	case PWM_NoSignalDetect:
		retVal = data->config.noSignalOutput;
		break;
	case PWM_LowSignalDetect:
		retVal = data->config.lowSignalOutput;
		break;
	case PWM_LinearCtrlDetect:
		retVal = MLIB_AddSat_F16(MLIB_Mul_F16(data->dutyCycle, data->config.linearSignalSlope),data->config.linearSignalShift);
		if(retVal < data->config.linearSignalOutputMin)
			retVal = data->config.linearSignalOutputMin;
		break;
	case PWM_HighSignalDetect:
		retVal = data->config.linearSignalOutputMax;
		break;
	default:
		retVal = 0;
		break;
	}
	
	return retVal;
}
