/******************************************************************************
*
* Copyright 2006-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
*
******************************************************************************/
/*!
*
* @file     gdu.h
*
* @date     MAY-16-2018
*
* @brief    gdu - Gate Drive Unit of S12ZVM
*
*******************************************************************************
*
* This file includes initial setting and MACRO definitions of S12ZVM gdu
* peripheral module.
*
******************************************************************************/

#ifndef GDU_H_
#define GDU_H_

/******************************************************************************
* Global gdu variables definition
******************************************************************************/
#include "mc9s12zvml128.h"


/******************************************************************************
* gdu MACRO definitions
******************************************************************************/
#define GDU_FAULTS_AS_MACRO			// Enable this macro to use macro for fault-clearing instead of function call

#ifdef GDU_FAULTS_AS_MACRO
#define GetDriverError() ((unsigned short)((GDUF|GDUDSE)>0))
#define ClearDriverError() (!((GDUF = 0xFF)||(GDUDSE = 0xFF)))
#endif 

/******************************************************************************
* gdu registers bit definition
******************************************************************************/


/******************************************************************************
* Exported functions
*******************************************************************************/
extern void 			gdu_init(void);

#ifndef GDU_FAULTS_AS_MACRO
extern unsigned short 	GetDriverError(void);
extern tBool 			ClearDriverError(void);
#endif 
#endif /* GDU_H_ */
