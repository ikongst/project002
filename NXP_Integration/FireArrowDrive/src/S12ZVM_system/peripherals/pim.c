/******************************************************************************
*
* Copyright 2006-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
*
******************************************************************************/
/*!
*
* @file     pim.c
*
* @date     JUL-10-2012
*
* @brief    pim - Port Integration Module of S12ZVM
* 			dedicated to the S12ZVMxHCEVB
*
*******************************************************************************
*
* This file includes initial setting and MACRO definitions of S12ZVM pim
* peripheral module.
*
******************************************************************************/

#include "pim.h"

/******************************************************************************
* Global pim variables definition
******************************************************************************/



/******************************************************************************
* pim MACRO definitions
******************************************************************************/


/******************************************************************************
* pim registers bit definition
******************************************************************************/


/******************************************************************************
* Functions Definitions
*******************************************************************************/
void pim_init(void)
{
//  MODRR0_SCI1RR = 1; // SCI - FreeMASTER
//
  DDRS_DDRS0 = 1;	// PS0 defined as output
  DDRS_DDRS1 = 1;	// PS1 defined as output
  DDRS_DDRS4 = 1;	// Debugg Signal
  DDRS_DDRS5 = 1;	// Debugg Signal
  
  DDRT_DDRT0 = 1;	// Debugg Signal
  
  DDRP_DDRP0 = 1;		// EVDD(PP0) defined as Output
  PTP_PTP0   = 1;		//EVDD output high   
  
//  MODRR0_S0L0RR = 0x00;	    //LIN routed to RX
//  MODRR2_T0IC3RR = 0x01;	//RX routed to TIM0C3
  
  
  //MODRR0 = (MODRR0_S0LRR_MASK && 0b000) | (MODRR0_SCI1RR_MASK);  //?????
}
