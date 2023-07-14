/******************************************************************************
*
* Copyright 2006-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2018 NXP
*
******************************************************************************/
/*!
*
* @file     gdu.c
*
* @date     MAY-10-2018
*
* @brief    gdu - GDU peripheral of S12ZVM
* 			dedicated to the S12ZVMxHCEVB
*
*******************************************************************************
*
* This file includes initial setting and MACRO definitions of S12ZVM gdu
* peripheral module.
*
******************************************************************************/

#include "gdu.h"
/******************************************************************************
* Global gdu variables definition
******************************************************************************/


/******************************************************************************
* gdu MACRO definitions
******************************************************************************/


/******************************************************************************
* gdu registers bit definition
******************************************************************************/


/******************************************************************************
* Functions Definitions
*******************************************************************************/
void gdu_init(void)
{
	// GDU.V4 settings	
	  
	  GDUE_GCSE0 = 1; // enable Current Sense Amplifier 0
	  GDUE_GCSE1 = 0; // disable Current Sense Amplifier 1 !!!

	  GDUOC0_GOCA0 = 1; // switch off all MOSFETs on overcurrent
	  GDUOC0_GOCE0 = 0;	// Overcurrent comparator enabled
	  GDUOC0_GOCT0 = 12; // Overcurrent threshold = ((48 + 12) / 64) * VDDA = 4.6875 V
	  // 4.6875 V represents 2.1875 V AC, with A = 20: Vsh = 0.109375 V, with Rsh = 0.001: Iover = 109.375 Amps pk 
	  
	  GDUF = 0xff;	// Flag Register - clear High & Low Voltage Supply flags

	  GDUCLK2_GCPCD = 4;  // Fbus / 64 !_! for bus clock 50Mhz
	  GDUE_GCPE = 1; // charge pump - to be set after the clock is set
	  
	  GDUCTR = 0x3F;	// blanking time ! ! 0x0f
	  GDUCTR_GHHDLVL = 1; // 26 V overvoltage
	  
	  GDUDSLVL = 0x77;	// desat. level !-! previous 0x44

	  GDUDSE = 0x77;	// Clear Desaturation Error Flags
}

#ifndef GDU_FAULTS_AS_MACRO
/**************************************************************************//*!
@brief Read GDU Flags register 

@param[in,out]  

@return  GDUF
******************************************************************************/
unsigned short GetDriverError(void)
{
	return ((unsigned short)((GDUF|GDUDSE)>0));	// Return non zero value if GDU fault or desaturation error occurs
}

/**************************************************************************//*!
@brief Clear GDU flag ragisters 

@param[in,out]  

@return true - if the flags were cleared
		false- if the clearing was not successful  
******************************************************************************/
tBool ClearDriverError(void)
{
	tBool retVal = (tBool)1;

	GDUF = 0xFF;

	if (GDUF != 0)
		retVal = (tBool)0;
	
	GDUDSE = 0xFF;
	
	if (GDUDSE != 0)
		retVal = (tBool)0;

	return(retVal);
}
#endif
