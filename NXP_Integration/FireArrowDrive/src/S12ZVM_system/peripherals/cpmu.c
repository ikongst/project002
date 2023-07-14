/******************************************************************************
*
* Copyright 2006-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2018 NXP
*
******************************************************************************/
/*!
*
* @file     cpmu.c
*
* @date     JUL-10-2012
*
* @brief    cpmu - Clock, Reset and Power Management Unit of S12ZVM
* 			dedicated to S12ZVMxHCEVB / 8MHz external crystal
*
*******************************************************************************
*
* This file includes initial setting and MACRO definitions of S12ZVM cpmu
* peripheral module.
*
******************************************************************************/

#include "cpmu.h"

/******************************************************************************
* Global cpmu variables definition
******************************************************************************/


/******************************************************************************
* cpmu MACRO definitions
******************************************************************************/


/******************************************************************************
* cpmu registers bit definition
******************************************************************************/


/******************************************************************************
* cpmu MACRO definitions
******************************************************************************/
// Internal clock 1MHz, 100/50 MHz CPU/Bus clock, 8.33 MHz ADC clock
#define _INTERNAL_CLOCK						// 1 MHz internal clock is used
#define	CPMU_REFDIV		0
#define	CPMU_SYNDIV		49
#define	CPMU_POSTDIV	0
#define	CPMU_REFFRQ		0
#define	CPMU_VCOFRQ		3

/******************************************************************************
* cpmu registers bit definition
******************************************************************************/


/******************************************************************************
* Functions Definitions
*******************************************************************************/
void cpmu_init(void)
{
	// Wait for stable supply after power up
	while (GDUF_GLVLSF)
		GDUF_GLVLSF = 1;

	CPMUREFDIV_REFDIV = CPMU_REFDIV;
	CPMUREFDIV_REFFRQ = CPMU_REFFRQ;
	CPMUSYNR_SYNDIV = CPMU_SYNDIV;
	CPMUSYNR_VCOFRQ = CPMU_VCOFRQ;
	CPMUPOSTDIV_POSTDIV = CPMU_POSTDIV;
	
	while (CPMUIFLG_LOCK == 0) {};
	
	CPMUHTCTL_VSEL = 0;	//Voltage Access Select Bit
	CPMUHTCTL_HTE = 1;	//High Temperature Sensor/Bandgap Voltage Enable Bit
	CPMURFLG  = 0x60; 	//Clear PORF and LVRF
	
    // Wait for stable supply after power up
//    while (GDUF_GLVLSF)
//    {
//        GDUF_GLVLSF = 1;
//    }

//    CPMUREFDIV_REFDIV = 0;
//    CPMUREFDIV_REFFRQ = 0;
//    CPMUSYNR_SYNDIV = 15;
//    CPMUSYNR_VCOFRQ = 0;
//    CPMUPOSTDIV_POSTDIV = 1;

//    while (CPMUIFLG_LOCK == 0)
//    {}

    //Clear PORF and LVRF
//    CPMURFLG  = 0x60;
}

void COP_init(void)
{
	CPMUCLKS_COPOSCSEL1 = 0;
	CPMUCLKS_COPOSCSEL0 = 0;
	CPMUCOP = 0x45;    // write enables watchdog; maximum time-out based on IRCCLK 4.194S

}
