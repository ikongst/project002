/******************************************************************************
*
* Copyright 2006-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
*
******************************************************************************/
/*!
*
* @file     ptu.h
*
* @date     MAY-16-2018
*
* @brief    ptu - Programmable Trigger Unit of S12ZVM
*
*******************************************************************************
*
* This file includes initial setting and MACRO definitions of S12ZVM ptu
* peripheral module.
*
******************************************************************************/

#ifndef PTU_H_
#define PTU_H_

#include "mc9s12zvml128.h"
#include "S12ZVM_devconfig.h"

/******************************************************************************
* ptu MACRO definitions
******************************************************************************/

#define PTU_TRIGGERs_GEN_NO         2
#define PTU_LISTS_NO                2
#define PTU_COMMANDS				5

#define PTU_FAULTS_AS_MACRO		// Enable this macro to use macro for fault-clearing instead of function call

#ifdef PTU_FAULTS_AS_MACRO
#define GetPTU_Errors() ((unsigned char)(PTUIFL & 0b11101110))
#define ClearPTU_Errors() ((unsigned char)((PTUIFL = PTUIFL)==0))
#endif

/******************************************************************************
* Global ptu variables definition
******************************************************************************/
PR_SECTION(ptuTrigE)
	extern volatile short ptuTriggerList0[PTU_LISTS_NO][PTU_COMMANDS];
  	extern volatile short ptuTriggerList1[PTU_LISTS_NO][PTU_COMMANDS];
PR_SECTION(DEFAULT_SEC)

/******************************************************************************
* ptu registers bit definition
******************************************************************************/


/******************************************************************************
* Exported functions
*******************************************************************************/
extern void ptu_init(void);

#ifndef PTU_FAULTS_AS_MACRO
extern unsigned char GetPTU_Errors();
extern unsigned char ClearPTU_Errors();
#endif


#endif /* PTU_H_ */
