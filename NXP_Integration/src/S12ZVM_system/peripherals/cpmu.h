/******************************************************************************
*
* Copyright 2006-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
*
***************************************************************************/
/*!
*
* @file     cpmu.h
*
* @date     JUL-10-2012
*
* @brief    CPMU - Clock, Reset and Power Management Unit of S12ZVM
*
*******************************************************************************
*
* This file includes initial setting and MACRO definitions of S12ZVM CPMU
* peripheral module.
*
******************************************************************************/

#ifndef CPMU_H_
#define CPMU_H_

/******************************************************************************
* Global CPMU variables definition
******************************************************************************/
#include "mc9s12zvml128.h"

/******************************************************************************
* CPMU MACRO definitions
******************************************************************************/

/******************************************************************************
* CPMU registers bit definition
******************************************************************************/

/******************************************************************************
* Exported functions
*******************************************************************************/
extern void cpmu_init(void);

#endif /* CPMU_H_ */
