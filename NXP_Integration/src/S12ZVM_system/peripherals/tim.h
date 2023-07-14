/*
 * tim.h
 *
 *  Created on: Feb 17, 2016
 *      Author: B56863
 */

#ifndef TIM_H_
#define TIM_H_

#include "mc9s12zvml128.h"
#include "S12ZVM_devconfig.h"

/******************************************************************************
* TIM MACRO definitions
******************************************************************************/


/******************************************************************************
* Global TIM variables definition
******************************************************************************/
//extern int TIM0_TC0_INCREMENT = 0;			//Timer C0 increment = initial compare value set in the initialisation of TIM0
//extern int TIM0_TC1_INCREMENT = 0;			//Timer C1 increment = initial compare value set in the initialisation of TIM0
//extern int TIM0_TC2_INCREMENT = 0;			//Timer C2 increment = initial compare value set in the initialisation of TIM0


/******************************************************************************
* TIM registers bit definition
******************************************************************************/


/******************************************************************************
* Exported functions
*******************************************************************************/

extern void initTIM(void);

extern void DisableTIM();
extern void EnableTIM();

#endif /* TIM_H_ */
