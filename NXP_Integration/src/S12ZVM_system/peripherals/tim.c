/*
 * tim.c
 *
 *  Created on: Feb 17, 2016
 *      Author: B56863
 */

#include "tim.h"


/******************************************************************************
* Global TIM variables definition
******************************************************************************/
//int TIM0_TC0_INCREMENT = 0;			//Timer C0 increment = initial compare value set in the initialisation of TIM0
//int TIM0_TC1_INCREMENT = 0;			//Timer C1 increment = initial compare value set in the initialisation of TIM0
//int TIM0_TC2_INCREMENT = 0;			//Timer C2 increment = initial compare value set in the initialisation of TIM0


/******************************************************************************
* TIM MACRO definitions
******************************************************************************/


/******************************************************************************
* TIM registers bit definition
******************************************************************************/


/******************************************************************************
* Functions Definitions
*******************************************************************************/
void initTIM(void)
{
	TIM0TIOS_IOS3	= 0;	// ~output compare | Input Capture or Output Compare Channel Configuration
	TIM0TIE_C3I	= 1;		// ~Enabled | Input Capture/Output Compare “x” Interrupt Enable

	TIM0PTPSR 		= 49;		// ~Bus clock / 102 | Timer Prescaler Select
	TIM0TSCR1_PRNT = 1;		// Precission timer divider

	TIM0TSCR2_TOI	= 1;	// Overflow interrupt enabled

	TIM0OCPD_OCPD3	= 1;	// ~Enabled | Output compare pin disconnect register
	TIM0OCPD_OCPD2	= 1;	// ~Enabled | Output compare pin disconnect register
	TIM0OCPD_OCPD1	= 1;	// ~Enabled | Output compare pin disconnect register
	TIM0OCPD_OCPD0	= 1;	// ~Enabled | Output compare pin disconnect register
	TIM0TCTL4_EDG3A = 1;	//rising edge
	TIM0TCTL4_EDG3B = 0;    //1

}

void EnableTIM()
{
	TIM0TC3 = 0;
	TIM0TSCR1_TEN	= 1;	// ~Enabled | Timer Enable	
}

void DisableTIM()
{
	TIM0TSCR1_TEN	= 0;	// ~Disabled | Timer Enable
}
