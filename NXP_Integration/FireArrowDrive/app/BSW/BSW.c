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
#include "actuate_s12zvm.h"


extern pwmControl_t pwmControlData;
extern appFaultStatus_t	permFaults;	

extern void 	DisableOutput(void);

INTERRUPT void API_ISR(void);




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
	
//	LP0CR_LPE = 0;       // Enable LIN Phy     disable ???
//    LP0CR_LPPUE = 0;     // Pull up to strong signal
	
//	if(!ucPINstatus)
//	{
//	 DDRS_DDRS1 = 1;	        // PS1 defined as output
//	 PTS_PTS1   = 0;	        //PS1 output low 
//	 MODRR0_S0L0RR = 0x02;	    //LIN routed to PS1
//	}
	//  MODRR0_S0L0RR = 0x01;	    //LIN routed to LPDR1
	//else
	//  MODRR0_S0L0RR = 0x00;     //LIN routed to RX
	//PTS_PTS1   = 1;		        //PS1 output High	
    //MODRR2_T0IC3RR = 0x01;	   //RX routed to TIM0C3
	
	 // LP0DR_LPDR1 = ucPINstatus;
	
}

void EnterintoSleep(void)
{
	DisableOutput();	
	DisableInterrupts;
	
	// KL15 signal
	PIEP_PIEP1 = 1;           // interrupt is enabled
	PIFP_PIFP1 = 1;           // clear PP1         interrupt flag only	  

	// LIN signal 
    CPMUCLKS_COPOSCSEL1 = 1;
    CPMUCLKS_CSAD = 1;
    CPMUCLKS_PCE = 0;
    CPMUCOP = (0b011&CPMUCOP_CR_MASK)|(0&CPMUCOP_WRTMASK_MASK)|(CPMUCOP_RSBCK_MASK)|(0&CPMUCOP_WCOP_MASK);    
    
	CPMUCLKS_PSTP=0;
	asm(CLI);
	asm(NOP);
    asm(andcc #0x7f);
    LP0CR_LPWUE = 1;
	SCI0SR2_AMAP = 1;
	SCI0ACR1_RXEDGIE = 0x01; /* edge interrupt enabled for wake up*/
	SCI0ASR1_RXEDGIF = 0x01; /* clear flag*/
	SCI0SR2_AMAP = 0;	
	EnableInterrupts;    
    asm(stop);    
    
	while(1)
	{
	
	}    
    
//	CPMUAPICTL_APICLK=0; //Use Autonomous Clock as source
//	CPMUACLKTR=0b01111100; //highest
//	CPMUAPICTL_APIE=1; //API interrupt will be requested whenever APIF is set.
//		
//	CPMUAPIRH=0x0A;//0x7F;  //Modify this register to change the wakeup freq.
//	CPMUAPIRL=0xFF;
//		
//	CPMUAPICTL_APIFE=1; //Autonomous periodical interrupt is enabled and timer starts running.
//	
//	asm(CLI);
//  asm(andcc #0x7f);
//  asm(stop);		
}

INTERRUPT void PORTP_ISR(void)
{
	asm(NOP);
	asm(NOP);
	asm(NOP);
		
	guiKL15CheckCntr++;
	
	//PPSP_PPSP1 = !PPSP_PPSP1;
	PIFP_PIFP1 = 1;
}

INTERRUPT void API_ISR(void)
{
 
	//clear timer flag
	CPMUAPICTL_APIF=1; //Clear API flag
	
	if((PTP_PTP1==1)||(LP0DR_LPDR0==0))   //wake
	{
		CPMUAPICTL_APIE = 0;
		CPMUAPICTL_APIFE=0; //Autonomous periodical interrupt is disabled.
	}
	else                                 //stop
	{
		CPMUAPICTL_APICLK=0; //Use Autonomous Clock as source
		CPMUACLKTR=0b01111100; //highest
		CPMUAPICTL_APIE=1; //API interrupt will be requested whenever APIF is set.
			
		CPMUAPIRH=0x0A;//0x7F;  //Modify this register to change the wakeup freq.
		CPMUAPIRL=0xFF;
			
		CPMUAPICTL_APIFE=1; //Autonomous periodical interrupt is enabled and timer starts running.
		
		//EnableInterrupts;
		
		
		asm(CLI);
	    asm(andcc #0x7f);
	    asm(stop);
	}
	
	//change LED state
	//PTP_PTP5 ^= 1;
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
	return MotorDrive_uiTemperatureNTC_Digital/10+50;
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

#include "mc9s12zvml128.h"
//#include "mlib.h"
//#include "gflib.h"
//#include "gmclib.h"
//#include "gdflib.h"
//#include"SWLIBS_Defines.h"
tFrac16 Unum,Vnum,Wnum;
void Set_Bridge_DutyCycle(unsigned int uduty, unsigned int vduty, unsigned int wduty)
{
   
   Unum=(long)((long)uduty*32768)/100/2;//FRAC16(uduty/100);
   Vnum=(long)((long)vduty*32768)/100/2;//FRAC16(vduty/100);
   Wnum=(long)((long)wduty*32768)/100/2;//FRAC16(wduty/100);

   tFrac16     trg[8];
   PTU_TRIGGERS_T		trigs;
   if((Unum&&Vnum)||(Vnum&&Wnum)||(Unum&&Wnum))
   	return;
   else
   	{
      if(Unum||Vnum||Wnum)
       trg[1] = (Unum|Vnum|Wnum);//2;
	  else
	   trg[1] = 0x3FFF/2;
   	}
    
   trigs.ph1Trg1       = (tU16) MLIB_Mul_F16(trg[1],PMFMODA);
   
   trigs.ph2Trg1       = (tU16) PMFMODA*3/4;
   trigs.dcOffsetTrg   = (tU16) PMFMODA;
   trigs.ph2Trg2       = (tU16) PMFMODA*5/4;
   trigs.ph1Trg2       = (tU16) PMFMODA*3/2;
   
   SetPtuTriggers(&trigs);
   
        /* ph A */
		PMFVAL0 = MLIB_Mul(FRAC16(0), PMFMODA<<1, F16);	// duty cycle 0-1 -> 0-PWM_MODULO
		//PMFVAL1 = MLIB_Mul(Unum, PMFMODA<<1, F16);	// duty cycle 0-1 -> 0-PWM_MODULO  //Unum*(PMFMODA<<1);//
		PMFVAL1 = MLIB_Mul(Unum, PMFMODA<<1, F16);	// duty cycle 0-1 -> 0-PWM_MODULO  //Unum*(PMFMODA<<1);//
				
		/* ph B */
		PMFVAL2 = MLIB_Mul(FRAC16(0), PMFMODA<<1, F16);	// duty cycle 0-1 -> 0-PWM_MODULO
		PMFVAL3 = MLIB_Mul(Vnum, PMFMODA<<1, F16);	// duty cycle 0-1 -> 0-PWM_MODULO  //Vnum*(PMFMODA<<1);//
	
	    /* ph C */
	    PMFVAL4 = MLIB_Mul(FRAC16(0), PMFMODA<<1, F16);	// duty cycle 0-1 -> 0-PWM_MODULO
	    PMFVAL5 = MLIB_Mul(Wnum, PMFMODA<<1, F16);	// duty cycle 0-1 -> 0-PWM_MODULO	//Wnum*(PMFMODA<<1);

//	    PMFFQCA_PWMRFA = 1; // Clear flag
//	    PMFENCA_LDOKA = 1;
//	    PMFENCA_GLDOKA = 1;
//	    PMFFQCA_LDFQA = 1;
	    PTUC_PTULDOK = 1;
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

