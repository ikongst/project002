#ifndef __UDS_H__
#define __UDS_H__

/*
v010, 2022-12-01, kongyun: initial version
v011, 2023-01-13, kongyun: uds function optimized.
*/

#include "Common.h"

// you should modified this to 0, if you want to use this lib
#define LIB_GENERATION_UDS       0

#if LIB_GENERATION_UDS == 1
    // lib need .... 
	//---------------------------------------------------------------------	
	//- customer index - 6 bits, maximum 64
	#define CUSTOMERINDEX_PLATFORM                          (0<<PAR_BITS_START_CUSTOMERINDEX)
	#define CUSTOMERINDEX_GWM                               (1<<PAR_BITS_START_CUSTOMERINDEX)
	#define CUSTOMERINDEX_GEELY                             (2<<PAR_BITS_START_CUSTOMERINDEX)
	#define CUSTOMERINDEX_GAC                               (3<<PAR_BITS_START_CUSTOMERINDEX)
	#define CUSTOMERINDEX_MAX                            (0x3F<<PAR_BITS_START_CUSTOMERINDEX) // maximum
	
	#define LIN_PROTOCOL_SELECTION                         CUSTOMERINDEX_PLATFORM	
	
	extern unsigned int guiSpeedSet;
	extern unsigned int guiTargetSpeed;
	extern unsigned int guiControlSpeed;
	extern unsigned int guiActualSpeed;
	extern unsigned int guiVoltage_nocalibration;
	extern unsigned int guiCurrent_nocalibration;
	extern unsigned int guiCurrent;
	extern unsigned int guiTemperature_nocalibration;
	extern unsigned char gucLINEOLServiceReceivedFlag;
  extern unsigned int guiLINEOLServiceCounter;
  extern unsigned char gucLINSignalReceivedFlag;
	extern unsigned char gucLINResponseError;
	extern unsigned char gucLINGotoSleepFlag;
	
	extern unsigned char gucInterfaceStatus;	
	
	
	typedef enum _TBdrv_Ch_Cfg
	{
		Ch_Off = 0u,  /**< \brief channel disabled                           */
		Ch_En  = 1u,  /**< \brief channel enabled                            */
		Ch_PWM = 3u,  /**< \brief channel enabled with PWM (CCU6 connection) */
		Ch_On  = 5u,  /**< \brief channel enabled and static on              */
		Ch_DCS = 9u   /**< \brief channel enabled with Diag.-Current Source  */
	} TBdrv_Ch_Cfg;
	void BDRV_Set_Bridge(TBdrv_Ch_Cfg LS1_Cfg, TBdrv_Ch_Cfg HS1_Cfg,
											 TBdrv_Ch_Cfg LS2_Cfg, TBdrv_Ch_Cfg HS2_Cfg, TBdrv_Ch_Cfg LS3_Cfg,
											 TBdrv_Ch_Cfg HS3_Cfg);
	void Set_Bridge_DutyCycle(unsigned int uduty, unsigned int vduty, unsigned int wduty);
	void flashoperation(unsigned char *arrpoints, unsigned int dataaddress, unsigned char datalength);
  void getdatafromflash(unsigned char *pvaluearr, unsigned int startaddress, unsigned int valuelength);
	void PWMDetection_INT(void);
	void KONGST_TIMER21_Start(void);
	
	typedef unsigned short int l_u16;
	typedef unsigned char l_u8;
	void ld_receive_message(l_u16* const length, l_u8* const data);
	void ld_send_message(l_u16 length, const l_u8* const data);
	typedef enum { 
	   LIN_NXP
	}l_ifc_handle; 
	l_u16 l_ifc_read_status
	(
	    /* [IN] interface name */
	    l_ifc_handle iii
	);
	l_u8 ld_tx_status(void);
	l_u8 ld_rx_status(void);
	typedef union wstatus {
	    l_u16 word; /**< this is a word, refer to 16 data bits follow*/
	    /**
	    * @struct bit
	    *
	    */
	    struct {
	        l_u16 error_in_res:1;               /**< Error in response */
	        l_u16 successful_transfer:1;        /**< Successful transfer */
	        l_u16 overrun:1;                    /**< Overrun */
	        l_u16 gotosleep:1;                  /**< Goto sleep */
	        l_u16 bus_activity:1;               /**< Bus activity */
	        l_u16 etf_collision:1;              /**< Event trigger collision */
	        l_u16 save_conf:1;                  /**< Save configuration */
	        l_u16 dummy:1;                      /**< Dummy */
	        l_u16 last_pid:8;                   /**< Last PID */
	    } bit; /**< these bits contain data of status */
	} lin_word_status_str;
	

	typedef enum {
	    LD_NO_MSG,            /**< no message */
	    LD_IN_PROGRESS,       /**< in progress */
	    LD_COMPLETED,         /**< completed */
	    LD_FAILED,            /**< failed */
	    LD_N_AS_TIMEOUT,      /**< N_As timeout */
	    LD_N_CR_TIMEOUT,      /**< N_Cr timeout */
	    LD_WRONG_SN           /**< wrong sequence number */
	} lin_message_status;
	
	l_u8 getnad(void);
  //------------------------------------------------------------------------	
	
	#define INTERFACE_LIN 0
	#define INTERFACE_PWM 1	
	
	#define FLASH_ADDRESS_SWID                             0x00000000  // 0x00000000 ~ 0x0000000F : 16 bytes

	// 0x00000020 ~ 0x0000002F: 16 bytes - kvoltage, bvoltage, kcurrent, bcurrent, ktemp, btemp...
	#define FLASH_ADDRESS_CALCULATION_START                0x00000020  // 0x00000020 ~ 0x0000002F : 16 bytes
	#define FLASH_ADDRESS_PARTNUMBER_PCBA                  0x00000030  // 0x00000030 ~ 0x0000003F : 16 bytes
	#define FLASH_ADDRESS_PARTNUMBER_MOTOR                 0x00000040  // 0x00000040 ~ 0x0000004F : 16 bytes
	#define FLASH_ADDRESS_PARTNUMBER_PRODUCT               0x00000050  // 0x00000050 ~ 0x0000005F : 16 bytes
	#define FLASH_ADDRESS_PARTNUMBER_LENGTH                16

	#define SW_WRITE_ARR_LENGTH                            FLASH_ADDRESS_PARTNUMBER_LENGTH    
	#define SW_READ_ARR_LENGTH                             FLASH_ADDRESS_PARTNUMBER_LENGTH	
	
	
#else
	#include "Common_LIB.h"
#endif

extern unsigned int guiLibVersion_UDS;
extern unsigned char gucEOLTFirstSkipFlag;
void UDS_Main(void);
extern unsigned char vAPPLLinCheckSleep(void);

#endif
