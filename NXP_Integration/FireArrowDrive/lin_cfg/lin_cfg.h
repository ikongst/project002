/******************************************************************************
* 
* Freescale Semiconductor Inc.
* (c) Copyright 2013-2016 Freescale Semiconductor, Inc.
* Copyright 2016-2023 NXP
* ALL RIGHTS RESERVED.
* 
****************************************************************************//*!
* 
* @file      lin_cfg.h 
* 
* @author    FPT Software
*  
* @version   1.0 
*  
* @date      Wed Jul 19 15:46:57 CST 2023
*  
* @brief     Hardware configuration file
* 
******************************************************************************/
#ifndef    _LIN_CFG_H_  
#define    _LIN_CFG_H_  
#include "lin_hw_cfg.h" 
/* Define operating mode */
#define _MASTER_MODE_     0 
#define _SLAVE_MODE_      1 
#define LIN_MODE   _SLAVE_MODE_
/* Define protocol version */
#define PROTOCOL_21       0  
#define PROTOCOL_J2602    1  
#define PROTOCOL_20       2 
#define LIN_PROTOCOL    PROTOCOL_21

#define SCI_ADDR        SCI0_ADDR    /* For slave */ 

#define LIN_BAUD_RATE    19200    	 /*For slave*/ 
/**********************************************************************/
/***************          Diagnostic class selection  *****************/
/**********************************************************************/
#define _DIAG_CLASS_I_          0
#define _DIAG_CLASS_II_         1
#define _DIAG_CLASS_III_        2

#define _DIAG_CLASS_SUPPORT_    _DIAG_CLASS_III_

#define MAX_LENGTH_SERVICE 6

#define MAX_QUEUE_SIZE 6


#define _DIAG_NUMBER_OF_SERVICES_    14

#define DIAGSRV_READ_BY_IDENTIFIER_ORDER    0

#define DIAGSRV_SAVE_CONFIGURATION_ORDER    1

#define DIAGSRV_ASSIGN_FRAME_ID_RANGE_ORDER    2

#define DIAGSRV_READ_DATA_BY_IDENTIFIER_ORDER    3

#define DIAGSRV_SESSION_CONTROL_ORDER    4

#define DIAGSRV_IO_CONTROL_BY_IDENTIFIER_ORDER    5

#define DIAGSRV_FAULT_MEMORY_READ_ORDER    6

#define DIAGSRV_FAULT_MEMORY_CLEAR_ORDER    7

#define DIAGSRV_WRITE_DATA_BY_IDENTIFIER_ORDER    8

#define DIAGSRV_DATA_DUMP_ORDER    9

#define DIAGSRV_CONDITIONAL_CHANGE_NAD_ORDER    10

#define DIAGSRV_ASSIGN_NAD_ORDER    11

#define DIAGSRV_ROUTINECONTROL_ORDER    12

#define DIAGSRV_ASSIGN_FRAME_IDENTIFIER_ORDER    13


/**************** FRAME SUPPORT DEFINITION ******************/
#define _TL_SINGLE_FRAME_       0
#define _TL_MULTI_FRAME_        1

#define _TL_FRAME_SUPPORT_      _TL_MULTI_FRAME_

/* frame buffer size */
#define LIN_FRAME_BUF_SIZE			24
#define LIN_FLAG_BUF_SIZE			5

/**********************************************************************/
/***************               Interfaces           *******************/
/**********************************************************************/
typedef enum { 
   LIN_NXP
}l_ifc_handle; 

/**********************************************************************/
/***************               Signals              *******************/
/**********************************************************************/
/* Number of signals */
#define LIN_NUM_OF_SIGS  27
/* List of signals */   
typedef enum {

   /* Interface_name = LIN_NXP */

   LIN_NXP_RefSpeed

   , LIN_NXP_ActSpeed
  
   , LIN_NXP_ActCurrent
  
   , LIN_NXP_ActVoltage
  
   , LIN_NXP_RespErr
  
   , LIN_NXP_StallSt
  
   , LIN_NXP_InnerErr
  
   , LIN_NXP_OverCurrErr
  
   , LIN_NXP_OverTempErr
  
   , LIN_NXP_PowerErr
  
   , LIN_NXP_Temperature
  
   , LIN_NXP_NTC
  
   , LIN_NXP_InternalVer
  
   , LIN_NXP_feedback4
  
   , LIN_NXP_feedback5
  
   , LIN_NXP_feedback6
  
   , LIN_NXP_feedback7
  
   , LIN_NXP_feedback8
  
   , LIN_NXP_SS_GDU
  
   , LIN_NXP_SS_OC
  
   , LIN_NXP_SS_SC
  
   , LIN_NXP_SS_Offset
  
   , LIN_NXP_SS_PB
  
   , LIN_NXP_SS_CurLimit
  
   , LIN_NXP_SS_CurOver
  
   , LIN_NXP_SS_TempLimit
  
   , LIN_NXP_SS_TempOver
  
  
} l_signal_handle; 
/**********************************************************************/
/*****************               Frame             ********************/
/**********************************************************************/
/* Number of frames */
#define LIN_NUM_OF_FRMS  5 
/* List of frames */
typedef enum {
/* All frames for master node */

   /* Interface_name = LIN_NXP */

   LIN_NXP_MotorCtrl

   , LIN_NXP_MotorStatus
  
   , LIN_NXP_SystemStatus
  
   , LIN_NXP_MasterReq
  
   , LIN_NXP_SlaveResp
  
  
} l_frame_handle; 
 
/**********************************************************************/
/***************             Configuration          *******************/
/**********************************************************************/
/* Size of configuration in ROM and RAM used for interface: LI1 */
#define LIN_SIZE_OF_CFG  7 
#define LIN_CFG_FRAME_NUM  3 
/*********************************************************************
 * global macros
 *********************************************************************/
#define l_bool_rd(SIGNAL) l_bool_rd_##SIGNAL()
#define l_bool_wr(SIGNAL, A) l_bool_wr_##SIGNAL(A)
#define l_u8_rd(SIGNAL) l_u8_rd_##SIGNAL()
#define l_u8_wr(SIGNAL, A) l_u8_wr_##SIGNAL(A)
#define l_u16_rd(SIGNAL) l_u16_rd_##SIGNAL()
#define l_u16_wr(SIGNAL, A) l_u16_wr_##SIGNAL(A)
#define l_bytes_rd(SIGNAL, start, count, data)  l_bytes_rd_##SIGNAL(start, count, data)
#define l_bytes_wr(SIGNAL, start, count, data) l_bytes_wr_##SIGNAL(start, count, data)
#define l_flg_tst(FLAG) l_flg_tst_##FLAG()
#define l_flg_clr(FLAG) l_flg_clr_##FLAG()
#define LIN_TEST_BIT(A,B) ((l_bool)((((A) & (1U << (B))) != 0U) ? 1U : 0U))
#define LIN_SET_BIT(A,B)                      ((A) |= (l_u8) (1U << (B)))
#define LIN_CLEAR_BIT(A,B)               ((A) &= ((l_u8) (~(1U << (B)))))
#define LIN_BYTE_MASK  ((l_u16)(((l_u16)((l_u16)1 << CHAR_BIT)) - (l_u16)1))
#define LIN_FRAME_LEN_MAX                                             10U

/* Returns the low byte of the 32-bit value    */
#define BYTE_0(n)                              ((l_u8)((n) & (l_u8)0xFF))
/* Returns the second byte of the 32-bit value */
#define BYTE_1(n)                        ((l_u8)(BYTE_0((n) >> (l_u8)8)))
/* Returns the third byte of the 32-bit value  */
#define BYTE_2(n)                       ((l_u8)(BYTE_0((n) >> (l_u8)16)))
/* Returns high byte of the 32-bit value       */
#define BYTE_3(n)                       ((l_u8)(BYTE_0((n) >> (l_u8)24)))

/*
 * defines for signal access
 */


#define LIN_BYTE_OFFSET_LIN_NXP_RefSpeed    1
#define LIN_BIT_OFFSET_LIN_NXP_RefSpeed    0
#define LIN_SIGNAL_SIZE_LIN_NXP_RefSpeed    16
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_RefSpeed    0
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_RefSpeed    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_RefSpeed    0

#define LIN_BYTE_OFFSET_LIN_NXP_ActSpeed    8
#define LIN_BIT_OFFSET_LIN_NXP_ActSpeed    0
#define LIN_SIGNAL_SIZE_LIN_NXP_ActSpeed    16
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_ActSpeed    1
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_ActSpeed    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_ActSpeed    1

#define LIN_BYTE_OFFSET_LIN_NXP_ActCurrent    11
#define LIN_BIT_OFFSET_LIN_NXP_ActCurrent    0
#define LIN_SIGNAL_SIZE_LIN_NXP_ActCurrent    8
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_ActCurrent    1
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_ActCurrent    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_ActCurrent    1

#define LIN_BYTE_OFFSET_LIN_NXP_ActVoltage    10
#define LIN_BIT_OFFSET_LIN_NXP_ActVoltage    0
#define LIN_SIGNAL_SIZE_LIN_NXP_ActVoltage    8
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_ActVoltage    1
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_ActVoltage    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_ActVoltage    1

#define LIN_BYTE_OFFSET_LIN_NXP_RespErr    12
#define LIN_BIT_OFFSET_LIN_NXP_RespErr    0
#define LIN_SIGNAL_SIZE_LIN_NXP_RespErr    1
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_RespErr    1
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_RespErr    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_RespErr    1

#define LIN_BYTE_OFFSET_LIN_NXP_StallSt    12
#define LIN_BIT_OFFSET_LIN_NXP_StallSt    1
#define LIN_SIGNAL_SIZE_LIN_NXP_StallSt    1
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_StallSt    1
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_StallSt    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_StallSt    1

#define LIN_BYTE_OFFSET_LIN_NXP_InnerErr    12
#define LIN_BIT_OFFSET_LIN_NXP_InnerErr    2
#define LIN_SIGNAL_SIZE_LIN_NXP_InnerErr    1
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_InnerErr    1
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_InnerErr    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_InnerErr    1

#define LIN_BYTE_OFFSET_LIN_NXP_OverCurrErr    12
#define LIN_BIT_OFFSET_LIN_NXP_OverCurrErr    3
#define LIN_SIGNAL_SIZE_LIN_NXP_OverCurrErr    1
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_OverCurrErr    1
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_OverCurrErr    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_OverCurrErr    1

#define LIN_BYTE_OFFSET_LIN_NXP_OverTempErr    12
#define LIN_BIT_OFFSET_LIN_NXP_OverTempErr    4
#define LIN_SIGNAL_SIZE_LIN_NXP_OverTempErr    1
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_OverTempErr    1
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_OverTempErr    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_OverTempErr    1

#define LIN_BYTE_OFFSET_LIN_NXP_PowerErr    12
#define LIN_BIT_OFFSET_LIN_NXP_PowerErr    5
#define LIN_SIGNAL_SIZE_LIN_NXP_PowerErr    2
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_PowerErr    2
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_PowerErr    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_PowerErr    1

#define LIN_BYTE_OFFSET_LIN_NXP_Temperature    16
#define LIN_BIT_OFFSET_LIN_NXP_Temperature    0
#define LIN_SIGNAL_SIZE_LIN_NXP_Temperature    8
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_Temperature    3
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_Temperature    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_Temperature    2

#define LIN_BYTE_OFFSET_LIN_NXP_NTC    17
#define LIN_BIT_OFFSET_LIN_NXP_NTC    0
#define LIN_SIGNAL_SIZE_LIN_NXP_NTC    8
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_NTC    3
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_NTC    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_NTC    2

#define LIN_BYTE_OFFSET_LIN_NXP_InternalVer    18
#define LIN_BIT_OFFSET_LIN_NXP_InternalVer    0
#define LIN_SIGNAL_SIZE_LIN_NXP_InternalVer    8
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_InternalVer    3
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_InternalVer    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_InternalVer    2

#define LIN_BYTE_OFFSET_LIN_NXP_feedback7    22
#define LIN_BIT_OFFSET_LIN_NXP_feedback7    0
#define LIN_SIGNAL_SIZE_LIN_NXP_feedback7    8
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_feedback7    4
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_feedback7    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_feedback7    2

#define LIN_BYTE_OFFSET_LIN_NXP_feedback8    23
#define LIN_BIT_OFFSET_LIN_NXP_feedback8    0
#define LIN_SIGNAL_SIZE_LIN_NXP_feedback8    8
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_feedback8    4
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_feedback8    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_feedback8    2

#define LIN_BYTE_OFFSET_LIN_NXP_SS_GDU    19
#define LIN_BIT_OFFSET_LIN_NXP_SS_GDU    0
#define LIN_SIGNAL_SIZE_LIN_NXP_SS_GDU    1
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_GDU    3
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_GDU    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_GDU    2

#define LIN_BYTE_OFFSET_LIN_NXP_SS_OC    19
#define LIN_BIT_OFFSET_LIN_NXP_SS_OC    1
#define LIN_SIGNAL_SIZE_LIN_NXP_SS_OC    1
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_OC    3
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_OC    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_OC    2

#define LIN_BYTE_OFFSET_LIN_NXP_SS_SC    19
#define LIN_BIT_OFFSET_LIN_NXP_SS_SC    2
#define LIN_SIGNAL_SIZE_LIN_NXP_SS_SC    1
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_SC    3
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_SC    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_SC    2

#define LIN_BYTE_OFFSET_LIN_NXP_SS_Offset    19
#define LIN_BIT_OFFSET_LIN_NXP_SS_Offset    4
#define LIN_SIGNAL_SIZE_LIN_NXP_SS_Offset    1
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_Offset    3
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_Offset    7
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_Offset    2

#define LIN_BYTE_OFFSET_LIN_NXP_SS_PB    19
#define LIN_BIT_OFFSET_LIN_NXP_SS_PB    3
#define LIN_SIGNAL_SIZE_LIN_NXP_SS_PB    1
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_PB    3
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_PB    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_PB    2

#define LIN_BYTE_OFFSET_LIN_NXP_SS_CurLimit    19
#define LIN_BIT_OFFSET_LIN_NXP_SS_CurLimit    5
#define LIN_SIGNAL_SIZE_LIN_NXP_SS_CurLimit    1
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_CurLimit    4
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_CurLimit    0
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_CurLimit    2

#define LIN_BYTE_OFFSET_LIN_NXP_SS_CurOver    19
#define LIN_BIT_OFFSET_LIN_NXP_SS_CurOver    6
#define LIN_SIGNAL_SIZE_LIN_NXP_SS_CurOver    1
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_CurOver    4
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_CurOver    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_CurOver    2

#define LIN_BYTE_OFFSET_LIN_NXP_SS_TempLimit    19
#define LIN_BIT_OFFSET_LIN_NXP_SS_TempLimit    7
#define LIN_SIGNAL_SIZE_LIN_NXP_SS_TempLimit    1
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_TempLimit    4
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_TempLimit    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_TempLimit    2

#define LIN_BYTE_OFFSET_LIN_NXP_SS_TempOver    20
#define LIN_BIT_OFFSET_LIN_NXP_SS_TempOver    0
#define LIN_SIGNAL_SIZE_LIN_NXP_SS_TempOver    1
#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_TempOver    4
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_TempOver    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_TempOver    2




#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_MotorCtrl             0
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_MotorCtrl              0

#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_MotorStatus             1
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_MotorStatus              0

#define LIN_FLAG_BYTE_OFFSET_LIN_NXP_SystemStatus             3
#define LIN_FLAG_BIT_OFFSET_LIN_NXP_SystemStatus              0


/**********************************************************************/
/***************        Static API Functions        *******************/
/**********************************************************************/
/*
 * the static signal access macros
 */




/* static access macros for signal LIN_NXP_ActCurrent */
   
#define l_u8_rd_LIN_NXP_ActCurrent() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_ActCurrent] & \
    (((1U << LIN_SIGNAL_SIZE_LIN_NXP_ActCurrent) - 1) \
    << LIN_BIT_OFFSET_LIN_NXP_ActCurrent )) >> LIN_BIT_OFFSET_LIN_NXP_ActCurrent))
#define l_u8_wr_LIN_NXP_ActCurrent(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_ActCurrent] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_ActCurrent] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LIN_NXP_ActCurrent) - 1) << LIN_BIT_OFFSET_LIN_NXP_ActCurrent)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LIN_NXP_ActCurrent) - 1) & (A)) << LIN_BIT_OFFSET_LIN_NXP_ActCurrent))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_ActCurrent] = 1;}

/* static access macros for signal LIN_NXP_ActVoltage */
   
#define l_u8_rd_LIN_NXP_ActVoltage() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_ActVoltage] & \
    (((1U << LIN_SIGNAL_SIZE_LIN_NXP_ActVoltage) - 1) \
    << LIN_BIT_OFFSET_LIN_NXP_ActVoltage )) >> LIN_BIT_OFFSET_LIN_NXP_ActVoltage))
#define l_u8_wr_LIN_NXP_ActVoltage(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_ActVoltage] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_ActVoltage] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LIN_NXP_ActVoltage) - 1) << LIN_BIT_OFFSET_LIN_NXP_ActVoltage)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LIN_NXP_ActVoltage) - 1) & (A)) << LIN_BIT_OFFSET_LIN_NXP_ActVoltage))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_ActVoltage] = 1;}

/* static access macros for signal LIN_NXP_RespErr */
   
#define l_bool_rd_LIN_NXP_RespErr() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_RespErr], \
   	LIN_BIT_OFFSET_LIN_NXP_RespErr))
#define l_bool_wr_LIN_NXP_RespErr(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_RespErr], \
  	LIN_BIT_OFFSET_LIN_NXP_RespErr)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_RespErr], \
  	LIN_BIT_OFFSET_LIN_NXP_RespErr));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_RespErr] = 1;}

/* static access macros for signal LIN_NXP_StallSt */
   
#define l_bool_rd_LIN_NXP_StallSt() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_StallSt], \
   	LIN_BIT_OFFSET_LIN_NXP_StallSt))
#define l_bool_wr_LIN_NXP_StallSt(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_StallSt], \
  	LIN_BIT_OFFSET_LIN_NXP_StallSt)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_StallSt], \
  	LIN_BIT_OFFSET_LIN_NXP_StallSt));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_StallSt] = 1;}

/* static access macros for signal LIN_NXP_InnerErr */
   
#define l_bool_rd_LIN_NXP_InnerErr() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_InnerErr], \
   	LIN_BIT_OFFSET_LIN_NXP_InnerErr))
#define l_bool_wr_LIN_NXP_InnerErr(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_InnerErr], \
  	LIN_BIT_OFFSET_LIN_NXP_InnerErr)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_InnerErr], \
  	LIN_BIT_OFFSET_LIN_NXP_InnerErr));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_InnerErr] = 1;}

/* static access macros for signal LIN_NXP_OverCurrErr */
   
#define l_bool_rd_LIN_NXP_OverCurrErr() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_OverCurrErr], \
   	LIN_BIT_OFFSET_LIN_NXP_OverCurrErr))
#define l_bool_wr_LIN_NXP_OverCurrErr(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_OverCurrErr], \
  	LIN_BIT_OFFSET_LIN_NXP_OverCurrErr)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_OverCurrErr], \
  	LIN_BIT_OFFSET_LIN_NXP_OverCurrErr));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_OverCurrErr] = 1;}

/* static access macros for signal LIN_NXP_OverTempErr */
   
#define l_bool_rd_LIN_NXP_OverTempErr() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_OverTempErr], \
   	LIN_BIT_OFFSET_LIN_NXP_OverTempErr))
#define l_bool_wr_LIN_NXP_OverTempErr(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_OverTempErr], \
  	LIN_BIT_OFFSET_LIN_NXP_OverTempErr)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_OverTempErr], \
  	LIN_BIT_OFFSET_LIN_NXP_OverTempErr));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_OverTempErr] = 1;}

/* static access macros for signal LIN_NXP_PowerErr */
   
#define l_u8_rd_LIN_NXP_PowerErr() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_PowerErr] & \
    (((1U << LIN_SIGNAL_SIZE_LIN_NXP_PowerErr) - 1) \
    << LIN_BIT_OFFSET_LIN_NXP_PowerErr )) >> LIN_BIT_OFFSET_LIN_NXP_PowerErr))
#define l_u8_wr_LIN_NXP_PowerErr(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_PowerErr] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_PowerErr] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LIN_NXP_PowerErr) - 1) << LIN_BIT_OFFSET_LIN_NXP_PowerErr)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LIN_NXP_PowerErr) - 1) & (A)) << LIN_BIT_OFFSET_LIN_NXP_PowerErr))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_PowerErr] = 1;}

/* static access macros for signal LIN_NXP_Temperature */
   
#define l_u8_rd_LIN_NXP_Temperature() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_Temperature] & \
    (((1U << LIN_SIGNAL_SIZE_LIN_NXP_Temperature) - 1) \
    << LIN_BIT_OFFSET_LIN_NXP_Temperature )) >> LIN_BIT_OFFSET_LIN_NXP_Temperature))
#define l_u8_wr_LIN_NXP_Temperature(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_Temperature] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_Temperature] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LIN_NXP_Temperature) - 1) << LIN_BIT_OFFSET_LIN_NXP_Temperature)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LIN_NXP_Temperature) - 1) & (A)) << LIN_BIT_OFFSET_LIN_NXP_Temperature))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_Temperature] = 1;}

/* static access macros for signal LIN_NXP_NTC */
   
#define l_u8_rd_LIN_NXP_NTC() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_NTC] & \
    (((1U << LIN_SIGNAL_SIZE_LIN_NXP_NTC) - 1) \
    << LIN_BIT_OFFSET_LIN_NXP_NTC )) >> LIN_BIT_OFFSET_LIN_NXP_NTC))
#define l_u8_wr_LIN_NXP_NTC(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_NTC] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_NTC] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LIN_NXP_NTC) - 1) << LIN_BIT_OFFSET_LIN_NXP_NTC)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LIN_NXP_NTC) - 1) & (A)) << LIN_BIT_OFFSET_LIN_NXP_NTC))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_NTC] = 1;}

/* static access macros for signal LIN_NXP_InternalVer */
   
#define l_u8_rd_LIN_NXP_InternalVer() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_InternalVer] & \
    (((1U << LIN_SIGNAL_SIZE_LIN_NXP_InternalVer) - 1) \
    << LIN_BIT_OFFSET_LIN_NXP_InternalVer )) >> LIN_BIT_OFFSET_LIN_NXP_InternalVer))
#define l_u8_wr_LIN_NXP_InternalVer(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_InternalVer] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_InternalVer] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LIN_NXP_InternalVer) - 1) << LIN_BIT_OFFSET_LIN_NXP_InternalVer)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LIN_NXP_InternalVer) - 1) & (A)) << LIN_BIT_OFFSET_LIN_NXP_InternalVer))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_InternalVer] = 1;}

/* signal LIN_NXP_feedback4 is not used in any frame */

/* signal LIN_NXP_feedback5 is not used in any frame */

/* signal LIN_NXP_feedback6 is not used in any frame */

/* static access macros for signal LIN_NXP_feedback7 */
   
#define l_u8_rd_LIN_NXP_feedback7() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_feedback7] & \
    (((1U << LIN_SIGNAL_SIZE_LIN_NXP_feedback7) - 1) \
    << LIN_BIT_OFFSET_LIN_NXP_feedback7 )) >> LIN_BIT_OFFSET_LIN_NXP_feedback7))
#define l_u8_wr_LIN_NXP_feedback7(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_feedback7] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_feedback7] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LIN_NXP_feedback7) - 1) << LIN_BIT_OFFSET_LIN_NXP_feedback7)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LIN_NXP_feedback7) - 1) & (A)) << LIN_BIT_OFFSET_LIN_NXP_feedback7))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_feedback7] = 1;}

/* static access macros for signal LIN_NXP_feedback8 */
   
#define l_u8_rd_LIN_NXP_feedback8() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_feedback8] & \
    (((1U << LIN_SIGNAL_SIZE_LIN_NXP_feedback8) - 1) \
    << LIN_BIT_OFFSET_LIN_NXP_feedback8 )) >> LIN_BIT_OFFSET_LIN_NXP_feedback8))
#define l_u8_wr_LIN_NXP_feedback8(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_feedback8] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_feedback8] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LIN_NXP_feedback8) - 1) << LIN_BIT_OFFSET_LIN_NXP_feedback8)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LIN_NXP_feedback8) - 1) & (A)) << LIN_BIT_OFFSET_LIN_NXP_feedback8))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_feedback8] = 1;}

/* static access macros for signal LIN_NXP_SS_GDU */
   
#define l_bool_rd_LIN_NXP_SS_GDU() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_GDU], \
   	LIN_BIT_OFFSET_LIN_NXP_SS_GDU))
#define l_bool_wr_LIN_NXP_SS_GDU(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_GDU], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_GDU)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_GDU], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_GDU));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_GDU] = 1;}

/* static access macros for signal LIN_NXP_SS_OC */
   
#define l_bool_rd_LIN_NXP_SS_OC() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_OC], \
   	LIN_BIT_OFFSET_LIN_NXP_SS_OC))
#define l_bool_wr_LIN_NXP_SS_OC(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_OC], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_OC)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_OC], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_OC));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_OC] = 1;}

/* static access macros for signal LIN_NXP_SS_SC */
   
#define l_bool_rd_LIN_NXP_SS_SC() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_SC], \
   	LIN_BIT_OFFSET_LIN_NXP_SS_SC))
#define l_bool_wr_LIN_NXP_SS_SC(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_SC], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_SC)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_SC], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_SC));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_SC] = 1;}

/* static access macros for signal LIN_NXP_SS_Offset */
   
#define l_bool_rd_LIN_NXP_SS_Offset() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_Offset], \
   	LIN_BIT_OFFSET_LIN_NXP_SS_Offset))
#define l_bool_wr_LIN_NXP_SS_Offset(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_Offset], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_Offset)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_Offset], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_Offset));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_Offset] = 1;}

/* static access macros for signal LIN_NXP_SS_PB */
   
#define l_bool_rd_LIN_NXP_SS_PB() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_PB], \
   	LIN_BIT_OFFSET_LIN_NXP_SS_PB))
#define l_bool_wr_LIN_NXP_SS_PB(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_PB], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_PB)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_PB], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_PB));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_PB] = 1;}

/* static access macros for signal LIN_NXP_SS_CurLimit */
   
#define l_bool_rd_LIN_NXP_SS_CurLimit() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_CurLimit], \
   	LIN_BIT_OFFSET_LIN_NXP_SS_CurLimit))
#define l_bool_wr_LIN_NXP_SS_CurLimit(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_CurLimit], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_CurLimit)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_CurLimit], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_CurLimit));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_CurLimit] = 1;}

/* static access macros for signal LIN_NXP_SS_CurOver */
   
#define l_bool_rd_LIN_NXP_SS_CurOver() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_CurOver], \
   	LIN_BIT_OFFSET_LIN_NXP_SS_CurOver))
#define l_bool_wr_LIN_NXP_SS_CurOver(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_CurOver], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_CurOver)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_CurOver], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_CurOver));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_CurOver] = 1;}

/* static access macros for signal LIN_NXP_SS_TempLimit */
   
#define l_bool_rd_LIN_NXP_SS_TempLimit() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_TempLimit], \
   	LIN_BIT_OFFSET_LIN_NXP_SS_TempLimit))
#define l_bool_wr_LIN_NXP_SS_TempLimit(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_TempLimit], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_TempLimit)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_TempLimit], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_TempLimit));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_TempLimit] = 1;}

/* static access macros for signal LIN_NXP_SS_TempOver */
   
#define l_bool_rd_LIN_NXP_SS_TempOver() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_TempOver], \
   	LIN_BIT_OFFSET_LIN_NXP_SS_TempOver))
#define l_bool_wr_LIN_NXP_SS_TempOver(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_TempOver], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_TempOver)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_SS_TempOver], \
  	LIN_BIT_OFFSET_LIN_NXP_SS_TempOver));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_SS_TempOver] = 1;}



/* static access macros for signal LIN_NXP_RefSpeed */
#define l_u16_rd_LIN_NXP_RefSpeed() \
    ((l_u16) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_RefSpeed + 1] & 0xff) << 8) + ((l_u16) (lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_RefSpeed]) >> 0x00))
#define l_u16_wr_LIN_NXP_RefSpeed(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_RefSpeed + 1] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_RefSpeed + 1] &  (0x00))) | \
	((l_u8) ((l_u8) ((A) >> 8)) & 0xff))); \
	lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_RefSpeed] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_RefSpeed] & (0x00))) | \
	((l_u8) (A) << LIN_BIT_OFFSET_LIN_NXP_RefSpeed))); \
	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_RefSpeed] = 1;}

/* static access macros for signal LIN_NXP_ActSpeed */
#define l_u16_rd_LIN_NXP_ActSpeed() \
    ((l_u16) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_ActSpeed + 1] & 0xff) << 8) + ((l_u16) (lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_ActSpeed]) >> 0x00))
#define l_u16_wr_LIN_NXP_ActSpeed(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_ActSpeed + 1] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_ActSpeed + 1] &  (0x00))) | \
	((l_u8) ((l_u8) ((A) >> 8)) & 0xff))); \
	lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_ActSpeed] = \
	((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LIN_NXP_ActSpeed] & (0x00))) | \
	((l_u8) (A) << LIN_BIT_OFFSET_LIN_NXP_ActSpeed))); \
	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LIN_NXP_ActSpeed] = 1;}





/* Signal flag APIs */

#define l_flg_tst_LIN_NXP_RefSpeed_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_RefSpeed],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_RefSpeed)
#define l_flg_clr_LIN_NXP_RefSpeed_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_RefSpeed],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_RefSpeed)

#define l_flg_tst_LIN_NXP_ActSpeed_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_ActSpeed],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_ActSpeed)
#define l_flg_clr_LIN_NXP_ActSpeed_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_ActSpeed],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_ActSpeed)

#define l_flg_tst_LIN_NXP_ActCurrent_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_ActCurrent],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_ActCurrent)
#define l_flg_clr_LIN_NXP_ActCurrent_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_ActCurrent],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_ActCurrent)

#define l_flg_tst_LIN_NXP_ActVoltage_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_ActVoltage],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_ActVoltage)
#define l_flg_clr_LIN_NXP_ActVoltage_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_ActVoltage],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_ActVoltage)

#define l_flg_tst_LIN_NXP_RespErr_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_RespErr],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_RespErr)
#define l_flg_clr_LIN_NXP_RespErr_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_RespErr],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_RespErr)

#define l_flg_tst_LIN_NXP_StallSt_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_StallSt],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_StallSt)
#define l_flg_clr_LIN_NXP_StallSt_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_StallSt],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_StallSt)

#define l_flg_tst_LIN_NXP_InnerErr_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_InnerErr],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_InnerErr)
#define l_flg_clr_LIN_NXP_InnerErr_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_InnerErr],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_InnerErr)

#define l_flg_tst_LIN_NXP_OverCurrErr_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_OverCurrErr],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_OverCurrErr)
#define l_flg_clr_LIN_NXP_OverCurrErr_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_OverCurrErr],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_OverCurrErr)

#define l_flg_tst_LIN_NXP_OverTempErr_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_OverTempErr],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_OverTempErr)
#define l_flg_clr_LIN_NXP_OverTempErr_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_OverTempErr],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_OverTempErr)

#define l_flg_tst_LIN_NXP_PowerErr_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_PowerErr],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_PowerErr)
#define l_flg_clr_LIN_NXP_PowerErr_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_PowerErr],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_PowerErr)

#define l_flg_tst_LIN_NXP_Temperature_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_Temperature],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_Temperature)
#define l_flg_clr_LIN_NXP_Temperature_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_Temperature],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_Temperature)

#define l_flg_tst_LIN_NXP_NTC_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_NTC],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_NTC)
#define l_flg_clr_LIN_NXP_NTC_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_NTC],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_NTC)

#define l_flg_tst_LIN_NXP_InternalVer_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_InternalVer],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_InternalVer)
#define l_flg_clr_LIN_NXP_InternalVer_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_InternalVer],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_InternalVer)




#define l_flg_tst_LIN_NXP_feedback7_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_feedback7],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_feedback7)
#define l_flg_clr_LIN_NXP_feedback7_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_feedback7],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_feedback7)

#define l_flg_tst_LIN_NXP_feedback8_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_feedback8],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_feedback8)
#define l_flg_clr_LIN_NXP_feedback8_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_feedback8],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_feedback8)

#define l_flg_tst_LIN_NXP_SS_GDU_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_GDU],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_GDU)
#define l_flg_clr_LIN_NXP_SS_GDU_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_GDU],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_GDU)

#define l_flg_tst_LIN_NXP_SS_OC_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_OC],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_OC)
#define l_flg_clr_LIN_NXP_SS_OC_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_OC],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_OC)

#define l_flg_tst_LIN_NXP_SS_SC_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_SC],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_SC)
#define l_flg_clr_LIN_NXP_SS_SC_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_SC],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_SC)

#define l_flg_tst_LIN_NXP_SS_Offset_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_Offset],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_Offset)
#define l_flg_clr_LIN_NXP_SS_Offset_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_Offset],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_Offset)

#define l_flg_tst_LIN_NXP_SS_PB_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_PB],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_PB)
#define l_flg_clr_LIN_NXP_SS_PB_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_PB],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_PB)

#define l_flg_tst_LIN_NXP_SS_CurLimit_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_CurLimit],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_CurLimit)
#define l_flg_clr_LIN_NXP_SS_CurLimit_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_CurLimit],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_CurLimit)

#define l_flg_tst_LIN_NXP_SS_CurOver_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_CurOver],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_CurOver)
#define l_flg_clr_LIN_NXP_SS_CurOver_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_CurOver],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_CurOver)

#define l_flg_tst_LIN_NXP_SS_TempLimit_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_TempLimit],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_TempLimit)
#define l_flg_clr_LIN_NXP_SS_TempLimit_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_TempLimit],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_TempLimit)

#define l_flg_tst_LIN_NXP_SS_TempOver_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_TempOver],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_TempOver)
#define l_flg_clr_LIN_NXP_SS_TempOver_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SS_TempOver],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SS_TempOver)



/* Frame flag APIs */

#define l_flg_tst_LIN_NXP_MotorCtrl_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_MotorCtrl],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_MotorCtrl)
#define l_flg_clr_LIN_NXP_MotorCtrl_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_MotorCtrl],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_MotorCtrl)

#define l_flg_tst_LIN_NXP_MotorStatus_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_MotorStatus],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_MotorStatus)
#define l_flg_clr_LIN_NXP_MotorStatus_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_MotorStatus],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_MotorStatus)

#define l_flg_tst_LIN_NXP_SystemStatus_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SystemStatus],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SystemStatus)
#define l_flg_clr_LIN_NXP_SystemStatus_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LIN_NXP_SystemStatus],\
         LIN_FLAG_BIT_OFFSET_LIN_NXP_SystemStatus)



/* INTERFACE MANAGEMENT */

#define l_ifc_init_LIN_NXP() l_ifc_init(LIN_NXP)



#define l_ifc_wake_up_LIN_NXP() l_ifc_wake_up(LIN_NXP)



#define l_ifc_rx_LIN_NXP() l_ifc_rx(LIN_NXP)



#define l_ifc_tx_LIN_NXP() l_ifc_tx(LIN_NXP)



#define l_ifc_aux_LIN_NXP() l_ifc_aux(LIN_NXP)



#define l_ifc_read_status_LIN_NXP() l_ifc_read_status(LIN_NXP)


#endif    /* _LIN_CFG_H_ */
