/*****************************************************************************\
*                                                                             *
*  KSE GmbH																	  *
*  Ingolstaedter Str. 98													  *
*  85092 Kösching															  *
*  http://www.kse-gmbh.com												      *
*  Phone +49(0) 8459 - 97401 - 50  									          *
*  Fax   +49(0) 8459 - 97401 - 52  									          *
*                                                                             *
*******************************************************************************
*    					                                                      *
*    					                                                      *
* (c) Alle Rechte bei KSE GmbH, auch fuer den Fall von Schutzrechts-    	  *
* anmeldungen. Jede Verfuegungsbefugnis, wie Kopier- und Weitergaberecht  	  *
* bei uns.                                                                    *
*                                                                             *
* (c) All rights reserved by KSE GmbH including the right to file             *
* industrial property rights. KSE GmbH retains the sole power of              *
* disposition such as reproduction or distribution.                           *
*    					                                                      *
*    					                                                      *
\*****************************************************************************/
/**
 * @file appl_diag.h
 * @brief LIN diagnosis application
 * @version 1.0
 * @author Tobias Ott
 *
 * @b History: @n
 * 	Rev 1.0 24.10.2012
 * 			new
 *  Rev 1.1 12.12.2012
 *  		added function (was stub)
 *  Rev 1.2 21.12.2012
 *  		changed service VWSlaveSystemName, time was too long
 *  Rev 1.3 10.01.2013
 *  		added WET production mode
 *  Rev 1.4 12.02.2013
 *  		corrected  au16APPLDIAGServices0x22 (trac #42)
 *
 */
#ifndef APPL_DIAG_H_
#define APPL_DIAG_H_

#include "UDS.h"
#include "kongst_types.h"	/*lint !e537 */

/******************************************************************************
 * DEFINES
 *****************************************************************************/

/** @brief macro to decode battery voltage
 * @details This macro shall be used to decode data that comes from diagnosis, so that
 * 			this battery voltage data can be used in application. From diagnosis, data comes
 * 			with a resolution of 1V/digit, internally we are working with .1V/digit. Therefore
 * 			incoming data has to be multiplied by 10
 * 	@param x battery voltage, MUST be of type uint8_t, MUST be inside range 0..25
 * 	@returns 10 times x
 */
#define APPLDIAG_DECODE_BAT_VOLT(x)	((x) * 10)

/** @brief macro to encode battery voltage
 * @details This macro shall be used to encode data that comes from application and goes out to
 * 			diagnosis. Internally we are working with .1V/digit, diagnosis data has a
 * 			resolution of 1V/digit. Therefore outgoing data must be divided by 10. Division is
 * 			an integer division.
 * 	@param x battery voltage, MUST be of type uint8_t, MUST be inside range 0 .. 255
 * 	@returns x divided by 10
 */
#define APPLDIAG_ENCODE_BAT_VOLT(x)	((x) / 10)

/* Range check for diagnosis Anpassung and Messwerte */
/** Anpassung overvoltage minimum [V] */
#define APPLDIAG_OVER_VOLTAGE_MIN	(12)
/** Anpassung overvoltage maximum [V] */
#define APPLDIAG_OVER_VOLTAGE_MAX	(20)
/** Anpassung undervoltage minimum [V] */
#define APPLDIAG_UNDER_VOLTAGE_MIN	(4)
/** Anpassung undervoltage maximum [V] */
#define APPLDIAG_UNDER_VOLTAGE_MAX	(12)
/** Anpassung voltage hysteresis minimum [0.1V] */
#define APPLDIAG_VOLTAGE_HYSTERESIS_MIN	(5)
/** Anpassung voltage hysteresis maximum [0.1V] */
#define APPLDIAG_VOLTAGE_HYSTERESIS_MAX	(10)
/** Anpassung maximum number of tries minimum */
#define APPLDIAG_TRIES_MIN	(1)
/** Anpassung maximum number of tries maximum */
#define	APPLDIAG_TRIES_MAX	(10)
/** Anpassung delay between retries minimum [s] */
#define APPLDIAG_TRY_DELAY_MIN	(1)
/** Anpassung delay between retries maximum [s] */
#define APPLDIAG_TRY_DELAY_MAX	(60)
/** Anpassung temperature for overtemperture shutdown minimum [°C] */
#define APPLDIAG_MAX_TEMP_MIN	(45)
/** Anpassung temperature for overtemperture shutdown maximum [°C] */
#define APPLDIAG_MAX_TEMP_MAX	(100)
/** Anpassung maximum RPM minimum [1/min] */
#define APPLDIAG_MAX_RPM_MIN		(1500)
/** Anpassung maximum RPM maximum [1/min] */
#define APPLDIAG_MAX_RPM_MAX		(5000)
/** Anpassung minimum RPM minimum [1/min] */
#define APPLDIAG_MIN_RPM_MIN		(1500)
/** Anpassung minimum RPM maximum [1/min] */
#define APPLDIAG_MIN_RPM_MAX		(5000)
/** Messwerte battery voltage maximum [.1V] */
#define APPLDIAG_BAT_VOLT_MAX		(0x00FF)
/** Messwerte temperature minimum [°C] */
#define APPLDIAG_REAL_TEMP_MIN	(0)
/** Messwerte temperature maximum [°C] */
#define APPLDIAG_REAL_TEMP_MAX	(120)
/** Messwerte rotor speed maximum [1/min] */
#define APPLDIAG_REAL_SPEED_MAX	(10000)
/** Messwerte retries maximum */
#define APPLDIAG_REAL_TRY_COUNT_MAX	(10)

/** @brief macro to check if data is outside of range
 * @param d data, MUST be of type word_t
 * @param l lower bound
 * @param h higher bound
 * @returns 0 if d is inside interval l..h including l and h [d <= h and d >= l]
 * @returns 1 if d is outside interval l..h [d < l or d > h]
 */
#define APPLDIAG_DATA_OUT_OF_RANGE(d,l,h)	(((d) < (l)) || ((d) > (h)))

/******************************************************************************
 * TYPEDEFS
 *****************************************************************************/
/**
@struct LIN_DIAG_MREQ_s
@brief   Stucture for diagnostic master request frame
*/
typedef union
{
   l_u8 byte[8];
   struct
   {
      l_u8         NAD;
      l_u8         PCI;
//      union
//      {
//         struct
//         {
//            l_u8   SID;
//            l_u8   data[5];
//         }SF;
//         struct
//         {
//            l_u8   LEN;
//            l_u8   SID;
//            l_u8   data[4];
//         }FF;
//         struct
//         {
            l_u8   data[6];
//         }CF;
//      }type;
   }frame;
}t_lin_diag_frame;

/******************************************************************************
 * EXTERNAL DECLARATION OF GLOBAL VARIABLES
 *****************************************************************************/


/******************************************************************************
 * EXTERNAL DECLARATION OF FUNCTIONS
 *****************************************************************************/

/** LIN diagnosis */
extern void vAPPLLinDiag(void);
/** to set FRD */
extern void vAPPLDiagSetFRD(uint8_t u8FRD);
/** to reset diagnosis statemachine */
extern void vAPPLDiagResetDiag(void);

extern unsigned char vAPPLLinCheckSleep(void);

#endif /* APPL_DIAG_H_ */
