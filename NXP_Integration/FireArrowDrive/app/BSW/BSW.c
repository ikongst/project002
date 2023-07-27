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
#include "eeprom_S12Z.h"


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

unsigned char gucmotordirection = 1;   //0
void BSW_MotorRegulation(unsigned int speedrpm)
{
 
  MotorDrive_Regulation(speedrpm,gucmotordirection);
	
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
	return 100;//(MotorDrive_uiTemperatureNTC_Digital*5*1000)>>12;
}
unsigned int getactualspeed(void)
{
	return ((long)MotorDrive_uiActualSpeed*3000)>>15;
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


unsigned int Write_buf[8]={0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,0x0008};
unsigned int read_buf[8];
void BSW_NVM_ProgramPage(unsigned char ucpageindex,unsigned int *ptr)
{
  unsigned char i;
  unsigned long int addr=ucpageindex*16+0x100000;
  for(i=0;i<4;i++)
  EEPROM_Erase_Sector(addr+i*4);
  for(i=0;i<2;i++)
  read_buf[6+i]=EEPROM_Program(addr+i*8,ptr+i*4,4);  
}
unsigned int BSW_NVM_ReadData(unsigned char ucpageindex)
{
   unsigned char i;
   unsigned long int addr=ucpageindex*16+0x100000;
   for(i=0;i<8;i++)
   read_buf[i]=EEPROM_Read_Word(addr+i*2);
   return 0xffff;
}

void flashoperation_1(unsigned char *arrpoints, unsigned int dataaddress, unsigned char datalength)
{	
	Write_buf[0] = arrpoints[0]<<8|arrpoints[1];
	Write_buf[1] = arrpoints[2]<<8|arrpoints[3];
	Write_buf[2] = arrpoints[4]<<8|arrpoints[5];
	Write_buf[3] = arrpoints[6]<<8|arrpoints[7];
	Write_buf[4] = arrpoints[8]<<8|arrpoints[9];
	Write_buf[5] = arrpoints[10]<<8|arrpoints[11];
	Write_buf[6] = arrpoints[12]<<8|arrpoints[13];
	Write_buf[7] = arrpoints[14]<<8|arrpoints[15];
	BSW_NVM_ProgramPage(dataaddress,Write_buf);
}
void getdatafromflash_1(unsigned char *pvaluearr, unsigned int startaddress, unsigned int valuelength)
{
	BSW_NVM_ReadData(startaddress);
	pvaluearr[0] = read_buf[0]>>8;
	pvaluearr[1] = read_buf[0];
	pvaluearr[2] = read_buf[1]>>8;
	pvaluearr[3] = read_buf[1];
	pvaluearr[4] = read_buf[2]>>8;
	pvaluearr[5] = read_buf[2];
	pvaluearr[6] = read_buf[3]>>8;
	pvaluearr[7] = read_buf[3];
	pvaluearr[8] = read_buf[4]>>8;
	pvaluearr[9] = read_buf[4];
	pvaluearr[10] = read_buf[5]>>8;
	pvaluearr[11] = read_buf[5];
	pvaluearr[12] = read_buf[6]>>8;
	pvaluearr[13] = read_buf[6];
	pvaluearr[14] = read_buf[7]>>8;
	pvaluearr[15] = read_buf[7];		
}


void NVM_ProgramPage(unsigned char ucpageindex)
{
	
}
unsigned int NVM_ReadData(unsigned char ucpageindex)
{
	return 0xffff;
}

