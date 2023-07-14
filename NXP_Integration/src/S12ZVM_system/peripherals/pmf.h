/******************************************************************************
*
* Copyright 2006-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
*
******************************************************************************/
/*!
*
* @file     pmf.h
*
* @date     MAY-16-2018
*
* @brief    pmf - Pulse Width Modulator with Fault Protection of S12ZVM
*
*******************************************************************************
*
* This file includes initial setting and MACRO definitions of S12ZVM pmf
* peripheral module.
*
******************************************************************************/

#ifndef PMF_H_
#define PMF_H_

/******************************************************************************
* Global pmf variables definition
******************************************************************************/
#include "mc9s12zvml128.h"


/******************************************************************************
* pmf MACRO definitions
******************************************************************************/
#define PMF_FAULTS_AS_MACRO		// Enable this macro to use macro for fault-clearing instead of function call

#ifdef PMF_FAULTS_AS_MACRO
#define GetPMF_Faults() ((unsigned char)PMFFIF)
#define ClearPMF_Faults() ((unsigned char)((PMFFIF = PMFFIF)==0))
#endif

/******************************************************************************
* pmf registers bit definition
******************************************************************************/


/******************************************************************************
* Exported functions
*******************************************************************************/
extern void pmf_init(void);

#ifndef PMF_FAULTS_AS_MACRO
extern unsigned char GetPMF_Faults();
extern unsigned char ClearPMF_Faults();
#endif

#endif /* PMF_H_ */
