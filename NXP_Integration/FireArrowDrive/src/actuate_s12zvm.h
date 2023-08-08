/******************************************************************************
*
* Copyright 2006-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
*
******************************************************************************/
/*!
*
* @file     actuate_s12zvm.h
*
* @date     Nov-15-2013
*
* @brief    Header file for actuator module
*
*******************************************************************************
*
*
******************************************************************************/
#ifndef _ACTUATE_S12ZVM_H_
#define _ACTUATE_S12ZVM_H_

#include "mc9s12zvml128.h"
#include "gflib.h"
#include "gmclib.h"
#include "gdflib.h"

#include "adc.h"

/******************************************************************************
| Defines and macros            (scope: module-local)
-----------------------------------------------------------------------------*/

/******************************************************************************
| Typedefs and structures       (scope: module-local)
-----------------------------------------------------------------------------*/

/******************************************************************************
| Exported Variables
-----------------------------------------------------------------------------*/

/******************************************************************************
| Exported function prototypes
-----------------------------------------------------------------------------*/
typedef struct PTU_TRIGGERS_T
{
	tU16	ph1Trg1;
    tU16	ph2Trg1;
    tU16	dcOffsetTrg;
    tU16	ph2Trg2;
    tU16	ph1Trg2;
}PTU_TRIGGERS_T;

extern void 	EnableOutput(void);
extern void 	DisableOutput(void);
extern void 	SetDutycycle(SWLIBS_3Syst_F16 *f16pwm, tU16 sector);
extern void     SetPtuTriggers(PTU_TRIGGERS_T	*pTrg);

/******************************************************************************
| Inline functions
-----------------------------------------------------------------------------*/



#endif /* _ACTUATES_S12ZVM_H_ */
