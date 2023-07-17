/*
 * BSW.c
 *
 *  Created on: Jun 25, 2023
 *      Author: kongyun
 */
#include "BSW.h"
#include "CustomerInterface.h"
#include "lin_cfg.h"
#include "lin.h"
#include "motor_structure.h"
#include "meas_S12zvm.h"
#include "motorinter.h"
#include "pwm_control.h"

extern pwmControl_t pwmControlData;
extern appFaultStatus_t	permFaults;	






void BSW_PWM_Init(void)
{
  //MODRR0_S0L0RR = 0x00;	    //LIN routed to RX
  MODRR2_T0IC3RR = 0x01;	//RX routed to TIM0C3
  TIM0TCTL4_EDG3A = 1;	  //rising edge
  TIM0TCTL4_EDG3B = 0;    //
  PWMControlInit(&pwmControlData);
}

void BSW_LIN_Init(void)
{
  MODRR0_S0L0RR = 0x00;	    //LIN routed to RX
  //MODRR2_T0IC3RR = 0x01;	//RX routed to TIM0C3
  TIM0TCTL4_EDG3A = 0;	  //disable capture
  TIM0TCTL4_EDG3B = 0;    //
  // test
  // test 2
}

void BSW_LIN_service(void)
{
	
}

void BSW_MotorStop(void)
{
 MotorDrive_Stop();
}
void BSW_MotorStart(void)
{
 MotorDrive_Start();
}

void BSW_MotorRegulation(unsigned int speedrpm)
{
 
  MotorDrive_Regulation(speedrpm,0);
	
}

void BSW_KL15Config(void)
{
	
}

void BSW_setpinstatus_interface(unsigned char ucPINstatus)
{
	//DIAgnostic out
	//MODRR0_S0L0RR = 0x02;	    //LIN routed to PS1
	//PTS_PTS1   = 0;		        //PS1 output high
	
    //MODRR2_T0IC3RR = 0x01;	   //RX routed to TIM0C3
	
	LP0DR_LPDR1 = ucPINstatus;
	
}

void EnterintoSleep(void)
{
   CPMUCLKS_PSTP=1;
}

unsigned int getrawvoltage(void)
{
	return MotorDrive_uiVoltage;
	
}
unsigned long getrawcurrent(void)
{
	return rms;
}
unsigned int getrawtemperature(void)
{
	return MotorDrive_uiTemperature+50;
}
unsigned int getNTCDigitals(void)
{	
	return (MotorDrive_uiTemperatureNTC_Digital*5*1000)>>12;
}
unsigned int getactualspeed(void)
{
	return MotorDrive_uiActualSpeed;
}

unsigned char ucgetPINInterfaceStatus(void)
{
	//PWM-high-low input
	return LP0DR_LPDR0;
}
unsigned char ucgetPINEnableStatus(void)
{
  //KL15 input
  //DDRP_DDRP1 = 0;		// PP1 defined as input 
  //PTP_PTP1   = 1;		//PP1 output high 
	return PTP_PTP1;
}

unsigned int Emo_PWM_test(unsigned int Bcounter,unsigned char Uduty,unsigned char Vduty,unsigned char Wduty,unsigned char pattern)
{
	return 1;
}

void BDRV_Set_Bridge(TBdrv_Ch_Cfg LS1_Cfg, TBdrv_Ch_Cfg HS1_Cfg,
										 TBdrv_Ch_Cfg LS2_Cfg, TBdrv_Ch_Cfg HS2_Cfg, TBdrv_Ch_Cfg LS3_Cfg,
										 TBdrv_Ch_Cfg HS3_Cfg)
{
	
}

void Set_Bridge_DutyCycle(unsigned int uduty, unsigned int vduty, unsigned int wduty)
{
	
}

unsigned int uigetGDUerror(void)
{
	return permFaults.mcu.B.GDU_Error;
}


unsigned int uigetSCerror(void)  //short
{
	return 0;
}
unsigned int uigetPBerror(void)  //phase break
{
	return 0;
}
unsigned int uigetOCerror(void)  //over current
{
	return 0;
}
unsigned int uigetPowererror(void) //DCBUS 
{
	return 0;
}

unsigned int uigetCurOffsetVal(void)  //Offset
{
	return 1600;
}

unsigned char TargetData[FlashPageSize]={0};


static unsigned int clearlindatacounter = 0;
unsigned int uigetlinsignal(void)
{
	// 10ms period.
	static unsigned int previousvalue = NOSIGNAL_int;	
	if(l_flg_tst_LIN_NXP_RefSpeed_flag())
	{
		previousvalue = l_u16_rd_LIN_NXP_RefSpeed();
		l_flg_clr_LIN_NXP_RefSpeed_flag();
		
		clearlindatacounter      = INIT;		
		gucLINSignalReceivedFlag = FLAG_SET;

	}
	else
	{		
		clearlindatacounter++;
		if(clearlindatacounter>=CUSTOMER_REQ_LIN_INPUTSIGNAL_CLEARDELAY_1ms)
		{
			clearlindatacounter = INIT;
			previousvalue       = NOSIGNAL_int;
			
			gucLINSignalReceivedFlag = FLAG_RESET;
		}
	}
	
	return previousvalue;
}

//#define PWMDETECTION_SET_EDGE_RISE()   {TIM0TCTL4_EDG3A = 1;TIM0TCTL4_EDG3B = 0;}//TIMER2->T2MOD.bit.EDGESEL = 1u
//#define PWMDETECTION_SET_EDGE_FALL()   {TIM0TCTL4_EDG3A = 0;TIM0TCTL4_EDG3B = 1;}//TIMER2->T2MOD.bit.EDGESEL = 0u
//#define PWMDETECTION_GET_CAPTURE()     TIM0TCNT//TIMER2_Get_Capture()
//#define PWMDETECTION_GETTIMER_CLK()    (1000000)//PWM2_CLK, ticket frequency.
void settrriger_rise(void)
{
	TIM0TCTL4_EDG3A = 1;
	TIM0TCTL4_EDG3B = 0;
}
void settrriger_fall(void)
{
	TIM0TCTL4_EDG3A = 0;
	TIM0TCTL4_EDG3B = 1;
}
unsigned int gettimercntr(void)
{
	return (TIM0TCNT);
}
long gettimerclk(void)
{
	return (1000000);
}


void getdatafromflash_1(unsigned char *pvaluearr, unsigned int startaddress, unsigned int valuelength)
{
	
}
void flashoperation_1(unsigned char *arrpoints, unsigned int dataaddress, unsigned char datalength)
{
	
}


void NVM_ProgramPage(unsigned char ucpageindex)
{
	
}
unsigned int NVM_ReadData(unsigned char ucpageindex)
{
	return 0xffff;
}

