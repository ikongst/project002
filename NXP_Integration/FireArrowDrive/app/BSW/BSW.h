/*
 * BSW.h
 *
 *  Created on: Jun 25, 2023
 *      Author: kongyun
 */

#ifndef BSW_H_
#define BSW_H_


#include "Common.h"

// macro definition, to be updated.
//-----------------------------------------------------------------------
#include "mc9s12zvml128.h"

// PWM duty&freq input
void settrriger_rise(void);
void settrriger_fall(void);
unsigned int gettimercntr(void);
long gettimerclk(void);


// task analysis
#define TASKANALYSIS_GETTIMER_CNTR()   gettimercntr()


// functions definition
//-----------------------------------------------------------------------
// PWM or LIN interface definition
void BSW_PWM_Init(void);
void BSW_LIN_Init(void);
void BSW_setpinstatus_interface(unsigned char ucPINstatus);
unsigned char ucgetPINInterfaceStatus(void);

// lin signal input
void BSW_LIN_service(void);
unsigned int uigetlinsignal(void);

// kl15
void BSW_KL15Config(void);
unsigned char ucgetPINEnableStatus(void);

// motor control definition
void BSW_MotorStop(void);
void BSW_MotorStart(void);
void BSW_MotorRegulation(unsigned int speedrpm);

// sleep mode
void EnterintoSleep(void);

// voltage, current, temperature, NTC
unsigned int getrawvoltage(void);
unsigned long getrawcurrent(void);
unsigned int getrawtemperature(void);
unsigned int getNTCDigitals(void);

// speed 
unsigned int getactualspeed(void);

// mosfets operation
unsigned int Emo_PWM_test(unsigned int Bcounter,unsigned char Uduty,unsigned char Vduty,unsigned char Wduty,unsigned char pattern);
typedef enum _TBdrv_Ch_Cfg
{
	Ch_Off = 0u,  /**< \brief channel disabled                           */
	Ch_En  = 1u,  /**< \brief channel enabled                            */
	Ch_PWM = 3u,  /**< \brief channel enabled with PWM (CCU6 connection) */
	Ch_On  = 5u,  /**< \brief channel enabled and static on              */
	Ch_DCS = 9u   /**< \brief channel enabled with Diag.-Current Source  */
} TBdrv_Ch_Cfg;
void BDRV_Set_Bridge(TBdrv_Ch_Cfg LS1_Cfg, TBdrv_Ch_Cfg HS1_Cfg,
										 TBdrv_Ch_Cfg LS2_Cfg, TBdrv_Ch_Cfg HS2_Cfg, TBdrv_Ch_Cfg LS3_Cfg,
										 TBdrv_Ch_Cfg HS3_Cfg);
void Set_Bridge_DutyCycle(unsigned int uduty, unsigned int vduty, unsigned int wduty);

// motor drive error
unsigned int uigetGDUerror(void);
unsigned int uigetSCerror(void);
unsigned int uigetPBerror(void);
unsigned int uigetOCerror(void);
unsigned int uigetPowererror(void);
unsigned int uigetCurOffsetVal(void);

void settrriger_rise(void);
void settrriger_fall(void);
unsigned int gettimercntr(void);
long gettimerclk(void); 

void getdatafromflash_1(unsigned char *pvaluearr, unsigned int startaddress, unsigned int valuelength);
void flashoperation_1(unsigned char *arrpoints, unsigned int dataaddress, unsigned char datalength);

// memory operation.
#define FlashPageSize 128
extern unsigned char TargetData[FlashPageSize];
void BSW_NVM_ProgramPage(unsigned char ucpageindex,unsigned int *ptr);
unsigned int BSW_NVM_ReadData(unsigned char ucpageindex);

#endif /* BSW_H_ */
