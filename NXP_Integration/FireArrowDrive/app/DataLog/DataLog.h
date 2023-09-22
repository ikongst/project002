#ifndef __DATALOG_H__
#define __DATALOG_H__

/*
v010, 2022-12-01, kongyun: initial version
v011, 2023-01-13, kongyun: add power error detection and record.
v012, 2023-09-22, kongyun: bug fixed regarding timing (unsigned int change to unsigned long)
*/

#include "Common.h"

#define FLASH_TARGETDATA_LENGTH                        128

// you should modified this to 0, if you want to use this lib
#define LIB_GENERATION_DATALOG       0

#if LIB_GENERATION_DATALOG == 1
	// lib need .... 
	//---------------------------------------------------------------------
	// Datalog lib
	
	extern unsigned int guiSpeedSet;
	extern unsigned int guiTargetSpeed;
	extern unsigned int guiControlSpeed;
	extern unsigned int guiVoltage;
	extern unsigned int guiVoltage_nocalibration;
	extern unsigned int guiCurrent;
	extern unsigned int guiCurrent_nocalibration;
	extern unsigned int guiTemperature;
	extern unsigned int guiTemperature_nocalibration;
	extern unsigned int guiActualSpeed;
	extern unsigned char gucLINEOLServiceReceivedFlag;
	
	extern FailureFlagStructure gProtectionFlags;
	extern typeU32 guiInformation_SWIdentifier;
	extern STATEMACHINE gMotorControl;	
    extern InternalDiagnosticStructure gInternalDiagnosticFlags;
  

    void getdatafromflash_1(unsigned char *pvaluearr, unsigned int startaddress, unsigned int valuelength);
    void flashoperation_1(unsigned char *arrpoints, unsigned int dataaddress, unsigned char datalength);
//------------------------------------------------------------------------

	#include "DTC.h"
	#include "TimeBase.h"
#else
	#include "Common_LIB.h"
#endif



// flash operation
#define FLASH_ADDRESS_START_PAGE0                      0x00000000
#define FLASH_ADDRESS_SWID                             0x00000000  // 0x00000000 ~ 0x0000000F : 16 bytes

// 0x00000020 ~ 0x0000002F: 16 bytes - kvoltage, bvoltage, kcurrent, bcurrent, ktemp, btemp...
#define FLASH_ADDRESS_CALCULATION_START                0x00000020  // 0x00000020 ~ 0x0000002F : 16 bytes
#define FLASH_ADDRESS_PARTNUMBER_PCBA                  0x00000030  // 0x00000030 ~ 0x0000003F : 16 bytes
#define FLASH_ADDRESS_PARTNUMBER_MOTOR                 0x00000040  // 0x00000040 ~ 0x0000004F : 16 bytes
#define FLASH_ADDRESS_PARTNUMBER_PRODUCT               0x00000050  // 0x00000050 ~ 0x0000005F : 16 bytes
#define FLASH_ADDRESS_PARTNUMBER_LENGTH                16

#define SW_WRITE_ARR_LENGTH                            FLASH_ADDRESS_PARTNUMBER_LENGTH    
#define SW_READ_ARR_LENGTH                             FLASH_ADDRESS_PARTNUMBER_LENGTH

#define FLASH_ADDRESS_0x00000060                       0x00000060
#define FLASH_ADDRESS_0x00000070                       0x00000070
#define FLASH_ADDRESS_START_PAGE1                      0x00000080
#define FLASH_ADDRESS_0x00000080                       0x00000080
#define FLASH_ADDRESS_0x00000090                       0x00000090
#define FLASH_ADDRESS_0x000000A0                       0x000000A0
#define FLASH_ADDRESS_0x000000B0                       0x000000B0
#define FLASH_ADDRESS_0x000000C0                       0x000000C0
#define FLASH_ADDRESS_INTERNALERROR                    0x000000D0
#define FLASH_ADDRESS_SPEEDSTATUS_1234                 0x000000E0
#define FLASH_ADDRESS_SPEEDSTATUS_5678                 0x000000F0

// DTC address definition - 256 bytes.
#define FLASH_ADDRESS_START_PAGE2                      0x00000100
#define FLASH_ADDRESS_TIMEBASE                         0x00000100   // last 4 bytes for time counter.
#define FLASH_ADDRESS_DTCSUMMARY1                      0x00000110   // 8 DTC counter, each 2 bytes
#define FLASH_ADDRESS_DTCSUMMARY2                      0x00000120   // 8 DTC counter, each 2 bytes

#define FLASH_ADDRESS_DTC1                             0x00000130
#define FLASH_ADDRESS_DCT2                             0x00000140
#define FLASH_ADDRESS_DCT3                             0x00000150
#define FLASH_ADDRESS_DCT4                             0x00000160
#define FLASH_ADDRESS_DCT5                             0x00000170
#define FLASH_ADDRESS_START_PAGE3                      0x00000180
#define FLASH_ADDRESS_DCT6                             0x00000180
#define FLASH_ADDRESS_DCT7                             0x00000190
#define FLASH_ADDRESS_DCT8                             0x000001A0
#define FLASH_ADDRESS_DCT9                             0x000001B0
#define FLASH_ADDRESS_DCT10                            0x000001C0
#define FLASH_ADDRESS_DCT11                            0x000001D0
#define FLASH_ADDRESS_DCT12                            0x000001E0

#define FLASH_ADDRESS_DCT_STARTADDRESS                 FLASH_ADDRESS_DTC1
#define FLASH_ADDRESS_DTC_MAX_INDEX                    ((FLASH_ADDRESS_DCT12-FLASH_ADDRESS_DTC1)>>4)


extern unsigned int guiLibVersion_Datalog;
extern unsigned char gucDatalogOperationFlag;
void DataLog_Main(void);


void starttimebaserecording(void);
void startspeedstatusrecording(void);
void startinternalerrorrecording(void);
void startdtcrecording(unsigned int uidtcaddress, unsigned char *ucpdtcarr);

extern unsigned char gucDTCWriteIndex;
extern unsigned long gulTimebaseSecond;
extern unsigned long gulDCTLastErrorSecond;
extern unsigned long gulTimeSpeedRangeArr[8];

#endif
