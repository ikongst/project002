/*
 * appl_diag.c
 *
 *  Created on: Jun 26, 2023
 *      Author: kongyun
 */

/******************************************************************************
 * INCLUDES
 *****************************************************************************/
//#include "board.h"
#include "appl_diag.h"
#include "UDS.h"

t_lin_diag_frame  g_lin_diag_mreq = {{0,0,0,0,0,0,0,0}};
/******************************************************************************
 * DEFINES
 *****************************************************************************/
/** Rev 1.11 Override aligning in Gcc */
#ifdef MODULETEST
#define COMPILER_ATTRIBUTE_PACKED  __attribute__ ((__packed__))
#else
#define COMPILER_ATTRIBUTE_PACKED
#endif

/** maximum length of request -> KSE data dump 20bytes + 1 NAD + 1 SID + 2 RDID + 1 spare */
#define APPLDIAG_MAX_REQ_LENGTH			(24)

/** maximum length of request -> SerialNumber 20bytes + 1 NAD + 1 SID + 2 RDID + 1 spare */
#define APPLDIAG_MAX_RESP_LENGTH		(24)

/** Uninitialized EEP byte */
#define APPLDIAG_UNINITIALIZED_BYTE		((uint8_t)0xFF)

/** number of different slaves */
#define APPLDIAG_NUMBER_OF_SLAVES		(16) /** Changerequest #76, old value was '8' */

/** tTimeout-LIN as defined in LIN Konzernlastenheft V2.1 ID LIN_712
 * After this time, server must send a response pendig max. one time.
 * One tick is 10ms long
 */
#define APPLDIAG_TTimeout_LIN 			(35)	/* *10ms */

/** marker if WET production mode is active */
#define APPLDIAG_VICKPRODMODEACTIVE		(0x55AA)

/** number of data byte to reset for WET prod write job EEP reset */
#define APPLDIAG_NO_DATA_TO_RESET		(2)

/** data length of VWSlaveSystemName */
#define APPLDIAG_SLAVESYSTEMNAME_DATALENGTH		(13)

/** UDS negative response */
#define APPLDIAG_UDS_NEG_RESPONSE		(0x7F)

/** response pending */
#define APPLDIAG_UDS_NRC_ResponsePendig	(0x78)
/** general programming failure */
#define APPLDIAG_UDS_NRC_GeneralProgrammingFailure	(0x72)
/** SID not supported */
#define APPLDIAG_UDS_NRC_SIDNotSupported	(0x11)
/** incorrect message length */
#define APPLDIAG_UDS_NRC_InCorrectMessageLenght	(0x13)
/** RDID not supported */
#define APPLDIAG_UDS_NRC_RequestOutOfRange	(0x31)
/** NRC conditions ot correct */
#define APPLDIAG_UDS_NRC_ConditionsNotCorrect (0x22)
/** SID for read data by identifier */
#define APPLDIAG_UDS_SID_ReadDataByIdentifier	(0x22)
/** SID for write data by identifier */
#define APPLDIAG_UDS_SID_WriteDataByIdentifier	(0x2E)
/** SID for eol routinues control by identifier */
#define APPLDIAG_UDS_SID_RoutinesControlByIdentifier	(0x31)
/** response SID for read data by identifier */
#define APPLDIAG_UDS_RESP_ReadDataByIdentifier	(0x62)
/** response SID for write data by identifier */
#define APPLDIAG_UDS_RESP_WriteDataByIdentifier	(0x6E)

/** request length for service 0x22 */
#define APPLDIAG_UDS_RDBI_Length			       (3)
#define APPLDIAG_UDS_RDBI_Length_With2Params (5)

#define APPLDIAG_UDS_ROUTINES_CONTROL_Length			(6)  // NAD PCI SID INDEX ID0 ID1 Par1 Par2

/** @brief to add the SID and RDID bytes to length of data
 * @param x datalength of UDS data, MUST be an integer [0..APPLDIAG_MAX_REQ_LENGTH-3]
 * @returns length of complete UDS data frame; that is length of data + 3bytes */
#define APPLDIAG_MAKE_UDS_DATA_LENGTH(x)				((x)+3)

/** offset of UDS Response code in diagnosis data stream */
#define APPLDIAG_UDS_RESPONSE_OFFSET					(0)
/** offset of UDS service request code in diagnosis data stream */
#define APPLDIAG_UDS_REQUEST_SERVICE_OFFSET			(0)
/** offset of UDS RDID highbyte in diagnosis data stream */
#define APPLDIAG_UDS_RDID_HIGHBYTE_OFFSET			(1)
/** offset of UDS RDID lowbyte in diagnosis data stream */
#define APPLDIAG_UDS_RDID_LOWBYTE_OFFSET				(2)
/** offset of UDS first data byte in diagnosis data stream */
#define APPLDIAG_UDS_DATA_OFFSET						(3)
/** offset of UDS negative response in diagnosis data stream */
#define APPLDIAG_UDS_NEGATIVE_RESPONSE_SERVICE_OFFSET (1)
/** offset of UDS negative response code in diagnosis data stream */
#define APPLDIAG_UDS_NEG_RESP_NRC_OFFSET	(2)
/** length of UDS negative response */
#define APPLDIAG_UDS_NEG_RESP_LENGTH		(3)
/** length of UDS positive response without data */
#define APPLDIAG_UDS_POSITIVE_RESPONSE_DATALENGTH	(3)
/** length of KSE data dump data frame */
#define APPLDIAG_KSE_DATA_DUMP_LENGTH				(20)
/** length command "open ECU" */
#define APPLDIAG_OPEN_ECU_DATALENGTH					(3)
/** UDS broadcast NAD */
#define APPLDIAG_BROADCAST_NAD						(0x7F)


/** @brief macro to convert a big endian input from diagosis to little endian for PIC16F
 * @details What this macro does: it places lowbyte of d in h, then highbyte of d in lowbyte
 * 			of d, then it places h in highbyte of d
 * @param d data, MUST be of type word_t
 * @param h databyte helper
 */
#define APPLDIAG_CONVERT_TO_LITTLE_ENDIAN(d,h)	h = d.bytes.lowbyte; \
		d.bytes.lowbyte = d.bytes.highbyte; \
		d.bytes.highbyte = h;

/** @brief macro to convert a little endian input from PIC16F application to big endian for diagosis
 * @details It just uses macro APPLDIAG_DATA_OUT_OF_RANGE as this macro interchanges high- and lowbyte, too
 * @sa APPLDIAG_DATA_OUT_OF_RANGE
 */
#define APPLDIAG_CONVERT_TO_BIG_ENDIAN(d,h) APPLDIAG_CONVERT_TO_LITTLE_ENDIAN(d,h)





/** @brief this macro converts a UDS request to a negative response with NRC x
 * @details A UDS request looks like this:  Bytes 00     01        02
 * 												  SID RDID_high RDID_low
 * 			For example, if data shall be read from RDID 0x0123 with service
 * 			0x22 (read data by identifier), the request would be 0x22 0x01 0x23
 * 			A negative response with for example NRC 0x31 (request out of range)
 * 			would be 0x7F 0x22 0x31
 * 			Therefore, this macro does the following: It places the SID, with is in
 * 			request byte 0 in response byte 1, it writes 0x7F to response byte 0 and
 * 			writes the NRC to response byte 2.
 * 	@param x NRC, MUST be of type uint8_t
 */
#define APPLDIAG_CONVERT_REQUEST_TO_NEG_RESPONSE_WITH_NRC(x)		au8TXData[APPLDIAG_UDS_NEGATIVE_RESPONSE_SERVICE_OFFSET] = au8TXData[APPLDIAG_UDS_REQUEST_SERVICE_OFFSET]; \
		au8TXData[APPLDIAG_UDS_RESPONSE_OFFSET] = APPLDIAG_UDS_NEG_RESPONSE; \
		au8TXData[APPLDIAG_UDS_NEG_RESP_NRC_OFFSET] = (x);

/** datalength of Messwerte1 service */
#define	APPLDIAG_MESSWERTE1_DATALENGTH	(7) /** Rev. 1.11, CR #76 Changed from "8" to "7", removed unused Byte in struct*/
/** datalength of Anpassung1 service */
#define APPLDIAG_ANPASSUNG1_DATALENGTH	(10)
/** datalength of Anpassung2 service */
#define APPLDIAG_ANPASSUNG2_DATALENGTH	(1)
/** datalength of read temperature for WET production service */
#define APPLDIAG_WET_READ_TEMPERATURE_DATALENGTH	(1)
/** datalength for read all error counters for WET production service */
#define APPLDIAG_WET_READ_ERROR_COUNTER_DATALENGTH (7)

/******************************************************************************
 * TYPEDEFS
 *****************************************************************************/

/** Statmachine of diagnosis */
typedef enum
{
	LD_INIT,				/**< initializing */
	LD_WAIT_FOR_REQUEST,	/**< wait for a request */
	LD_PROCESS_REQUEST,		/**< preocess the request */
	LD_SEND_RESPONSE		/**< send the response */
} APPLDiag_DiagStatemachineType;

/** type for determining 0x22 service */
typedef enum
{
	SlaveCoding,
	SlaveSparePartNumber,
	SlaveApplicationSWNumber,
	SlaveHWNumber,
	SlaveHWVersion,
	SlaveSerialNumber,
	SlaveSystemName,
	SlaveMWB1,
	SlaveReadAnp1,
	SlaveReadAnp2,

	WETProdReadSerialNumber,
	WETProdReadHWNumber,
	WETProdReadSparePartNumber,
	WETProdReadHWVersion,
	WETProdReadTemperature,
	WETProdReadErrorCounter,

	NoOfAPPLDIAGService0x22Position
} APPLDIAGService0x22PositionType;

/** type for determining 0x2E service */
typedef enum
{
	SlaveAnpassungen1,
	SlaveAnpassungZuruecksetzen1,

	WETProdWriteSerialNumber,
	WETProdWriteHWNumber,
	WETProdWriteSparePartNumber,
	WETProdWriteHWVersion,
	WETProdOpenECU,
	WETProdResetEEP,

	VICKDataDump,

	NoOfAPPLDIAGService0x2EPosition
} APPLDIAGService0x2EPositionType;

/** denotes the active diagnosis service */
typedef enum
{
	LD_None,						/**< no service */
	LD_ProdReadPCBANumber,		/**< pcba number */
	LD_ProdReadMotorNumber,	/**< VWSlaveApplicationSoftwareVersionNumber */
	LD_ProdReadCalibration,		/**< VWSlaveHardwareNumber */
	LD_VWSlaveHardwareVersionNum,	/**< VWSlaveHardwareVersionNumber */
	LD_VWSlaveSerialNumber,			/**< VWSlaveSerialNumber */
	LD_VWSlaveSystemName,			/**< VWSlaveSystemName */
	LD_Messwerte1,					/**< Messwerte 1 */
	LD_SIDNotSupported,				/**< Service not supported */
	LD_RDIDNotSupported,			/**< RDID not supported */
	LD_Anpassung1,					/**< Anpassung */
	LD_AnpassungZuruecksetzen1,		/**< Anpassung zurücksetzen */
	LD_WETProdWriteSerialNumber,	/**< write serial number in WET production */
	LD_ProdWritePCBANumber,		/**< write HW number in WET production */
	LD_ProdWriteProductNumber,	/**< write spare part number in WET production */
	LD_ProdWriteMotorNumber,		/**< write HW version in WET production */
	LD_WaitEEPROM,					/**< wait EEPROM write finished */
	LD_SendResponsePending,			/**< send response pending to LIN master */
	LD_WaitEEPROMSecondTime,		/**< wait EEPROM after first response pendig was sent */
	LD_ProdWriteCalibration,				/**< open ECU fro data write */
	LD_VICKProdOpenECU,				/**< reset EEP to default state (serial number is not reset) */
	LD_WETProdReadSerialNumber,		/**< read serial number in WET production */
	LD_ProdReadProductNumber,			/**< read HW number in WET production */
	LD_ProdReadSWID,	/**< read software id for this electronics */
	LD_WETProdReadHWVersion,		/**< read HW version in WET production */
	LD_IncorrectLength,				/**< request length is not correct */
	LD_VICKDataDump,					/**< data dump */
	LD_ConditionsNotCorrect,		/**< conditions not correct */
	LD_RequestOutOfRange,			/**< request out of range */
	LD_AnpassungCommandWrite,		/**< Anpassung command EEM to write data to EE */
	LD_Anpassung1Read,				/**< read Anpassung1 values frm EEM */
	LD_AnpassungZuruecksetzen1Read,	/**< read Anpassung2 value (always 0) */
	LD_WETReadTemperature,			/**< read real temperature for WET production */
	LD_WETReadErrorCounter,			/**< read all error counters for WET production */
	LD_WETProdWriteSerialNumber2,	/**< second stage of write SN: copy data to diagnosis internal RAM buffer (WCET!) */

	LD_EOLNULL,
	LD_EOLService1,
	LD_EOLService2,
	LD_EOLService3,
	LD_EOLService4,
	LD_EOLService5,
	LD_EOLService6,
	LD_EOLService7,
	LD_EOLService8
		
} APPLDiagActiveServiceType;

/** data dump request and response functions */
typedef enum
{
	DDReqRAMByteRead = 0x00,
	DDReqRAMWordRead = 0x01,
	DDReqEEPROMByteRead = 0x02,
	DDReqEEPROMWordRead = 0x03,
	DDReqFlashWordRead = 0x04,
	DDReqRAMByteWrite = 0x05,
	DDReqRAMWordWrite = 0x06,
	DDReqEEPROMByteWrite = 0x07,
	DDReqEEPROMWordWrite = 0x08,
	DDReqStackDepth = 0x09,
	DDReqTaskTime = 0x0A,
	DDReqWETSWVersion = 0x0B,
	DDReqKSEBuildVersion = 0x0C,
	DDReqEEPROMEraseAll = 0x0D,
	DDReqEEPROMReadRow = 0x0E,

	DDRespRAMByteRead = 0x80,
	DDRespRAMWordRead = 0x81,
	DDRespEEPROMByteRead = 0x82,
	DDRespEEPROMWordRead = 0x83,
	DDRespFlashWordRead = 0x84,
	DDRespRAMByteWrite = 0x85,
	DDRespRAMWordWrite = 0x86,
	DDRespEEPROMByteWrite = 0x87,
	DDRespEEPROMWordWrite = 0x88,
	DDRespStackDepth = 0x89,
	DDRespTaskTime = 0x8A,
	DDRespWETSWVersion = 0x8B,
	DDRespKSEBuildVersion = 0x8C,
	DDRespEEPROMEraseAll = 0x8D,
	DDRespEEPROMReadRow = 0x8E,

	DDRespError = 0xFF

} DDFunctionType;

/** data dump error returns */
typedef enum
{
	DDErrorCS = 0x01,
	DDErrorAdress = 0x02,
	DDErrorUnknownService = 0x03,
	DDErrorEEPROMNotReady = 0x04,
	DDErrorFlashNotReady = 0x05,
	DDErrorParameter = 0x06
}DDErrorType;

/** KSE data dump state statemachine */
typedef enum
{
	DDStateSetup,
	DDStateExecute,
	DDStateResponse,
	DDStateSendResponse
}DDStateType;


/** Messwerte1 data structure */
/*lint -save -e754 */
typedef union
{
	struct  COMPILER_ATTRIBUTE_PACKED
	{
		struct
		{
			uint8_t u81;						/**< unused byte */
			uint8_t u82;						/**< unused byte */
			uint8_t u83;						/**< unused byte */
		} unused;
		uint8_t u8CurrentSupplyVoltage;		/**< supply voltage in V, resolution 0,1V per digit, min 0V max (40V spec Audi) 25.5V */
		/*uint8_t u8Unused1;*/				/**< unused byte */ /* Rev. 1.11, CR #76 removed u8Unused1 */
		uint8_t u8CurrentTemperature;		/**< current PCB temperature, resolution 1°C per digit, min 0°C max 120°C */
		word_t  u16CurrentSpeedRPM;			/**< current spped in PRM, resolution 1/min per digit, min 0/min max 10000/min */
		uint8_t u8CurrentHWCodingPins;		/**< current HW coding pins, valid [0 .. 7] */
		uint8_t u8CodingPinsFromEE;			/**< coding pin saved in EE, valid [0 .. 7] */
		uint8_t u8CurrentTryCount;			/**< current try count, resolution 1 per digit, min 0 max 10 */
	} symbols;							    /**< symbol access to Messwerte */
    /* Rev. 1.11 Removed unused bytewise access to Messwerte data */
} APPLDIAGMesswerte1Type;
/*lint -restore */

/** Anpassung2 data structure */
/*lint -save -e46 -e754 */
typedef union
{
	struct
	{
		uint8_t bAktiv:1;					/**< Anpassung2 aktiv flag */
		uint8_t unused:7;					/**< not used */
	} symbols;							    /**< symbol access */
	uint8_t byte;							/**< byte access */
} APPLDIAGAnpassung2Type;
/*lint -restore */

/******************************************************************************
 * LOCAL FUNCTION FORWARD DECLARATIONS
 *****************************************************************************/

/** This function reads data directly from EE and places the data inside Diagnosis buffer */
static void vAPPLDIAGReadFromEEDirect(uint8_t u8Adress, uint8_t u8DataLength);
/** This function reads data from ROM and places the data inside Diagnosis buffer */
static void vAPPLDIAGReadFromROM(unsigned int addressdefined, unsigned char datalength);
static void vAPPLDIAGWriteToROM(unsigned int addressdefined, unsigned char datalength);



/** This function just sends a negative answer to an UDS request */
static void vAPPLDIAGSendNegativeResponse(uint8_t u8NRC);
/** Fill diagnosis buffer with Messwerte */
static void vAPPLDIAGMesswerte1(void);
/** Write values via diagnosis, Anpassung */
static void vAPPLDIAGAnpassung1Write(void);
/** read Anpassung2 (Anpassung zurücksetzen) */
static void vAPPLDIAGAnpassungReset1Read(void);
/** Reset Anpassung data to ROM default data  */
static void vAPPLDIAGAnpassungReset1Write(void);
/** Evaluates if data access can be granted */
static void vAPPLDIAGEvalOpenECU(void);
/** Evaluates if a request has to be serviced by ECU */
static void tAPPLDIAGEvaluateRequest(void);
/** Read Anpassung values */
static void vAPPLDIAGAnpassung1Read(void);
/** read data directly from RAM in diagnosis buffer */
static void vAPPLDIAGReadFromRAM(const uint8_t * pu8Adress, uint8_t u8DataLength);
/** data dump for development */
static void vVICKDataDump(void);



/******************************************************************************
 * GLOBALS
 *****************************************************************************/

/******************************************************************************
 * LOCALS
 *****************************************************************************/

/** state of diagnosis */
APPLDiag_DiagStatemachineType tDiagState = LD_INIT;

/** length of received data
 *
 * Note usage of type l_u16, defined in lin_types.h of IHR lin driver. Reason is that fucntion ld_receive_message requires a pointer to l_u16
 * and I want to avoid pointer casts. */
static l_u16 u16RXLength;
/** Maximum length of RX data */
static l_u16 u16ReceivedDataLength;
/** buffer for diagnosis response */
static uint8_t au8TXData[APPLDIAG_MAX_RESP_LENGTH];
/** buffer for diagnosis request */
static uint8_t au8RXData[APPLDIAG_MAX_REQ_LENGTH];

/** active diagnosis service */
static APPLDiagActiveServiceType tActiveService = LD_None;
/** WET production mode active */
static uint16_t u16VICKProdMode = 0;

/** Subsystem Names for each NAD */
/** CR #76  */
static const uint8_t acu8SystemNames[APPLDIAG_NUMBER_OF_SLAVES][APPLDIAG_SLAVESYSTEMNAME_DATALENGTH+1] =
{
		{"vick CFModule"},
		{"0000 00000000"},
		{"0000 00000000"},
		{"0000 00000000"},
		{"0000 00000000"},
		{"0000 00000000"},
		{"0000 00000000"},
		{"0000 00000000"},
		{"0000 00000000"},
		{"0000 00000000"},
		{"0000 00000000"},
		{"0000 00000000"},
		{"0000 00000000"},
		{"0000 00000000"},
		{"0000 00000000"},
		{"0000 00000000"}
};

/** Config table for 0x22 services */
/*lint -save -e708 */
/** Rev. 1.11, CR #76 Added entries for rear modules */
static const word_t au16APPLDIAGServices0x22[APPLDIAG_NUMBER_OF_SLAVES][NoOfAPPLDIAGService0x22Position] =
{

		/*  Coding  PCBANum(X) MotorNum(X) Calib(X) HWVer     SerialNr SystemName MWB1      Anp1(X)  Anp2   ProdSerNr ProductNum(X) ProdHWVer SWID(X)    ProdTemp  ProdError*/
		{ {0xFFFF}, {0xFD01}, {0xFD02}, {0xFD03}, {0xFD04}, {0xFD05}, {0xFD06}, {0xFD07}, {0xFD08}, {0xFD09}, {0xFD0A}, {0xFD0B}, {0xFD0C}, {0xFD0D}, {0xFD0E}, {0xFD0F} },	
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },	
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },	
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },	
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },	
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },	
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },	

		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },	
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },	
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },	
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },	
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },	
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },	
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} }

};
/*lint -restore */

/** @brief active service state dependent on 0x22 service config table
 *
 * This table sets the state for the statemachine, where the requested service is executed.
 * Dependent on the column of table au16APPLDIAGServices0x22, next state is pulled from this stable and executed.
 * Internal services, that are opened by service 0xFD04 and password KSE have to be put behind position tAPPLDIAGService0x22StartinternalServices!!
 * @sa tAPPLDIAGService0x22StartinternalServices*/
static const APPLDiagActiveServiceType atAPPLDIAGService0x22DiagState[NoOfAPPLDIAGService0x22Position] =
{
		LD_RDIDNotSupported,
		LD_ProdReadPCBANumber,
		LD_ProdReadMotorNumber,
		LD_ProdReadCalibration,
		LD_VWSlaveHardwareVersionNum,
		LD_VWSlaveSerialNumber,
		LD_VWSlaveSystemName,
		LD_Messwerte1,
		LD_Anpassung1Read,
		LD_AnpassungZuruecksetzen1Read,

		LD_WETProdReadSerialNumber,
		LD_ProdReadProductNumber,
		LD_WETProdReadHWVersion,
		LD_ProdReadSWID,
		LD_WETReadTemperature,
		LD_WETReadErrorCounter

};

/** to determine if the requersted service is an internal service */
static const APPLDIAGService0x22PositionType tAPPLDIAGService0x22StartinternalServices = WETProdReadSerialNumber;

/** Config table for 0x2E services */
/*lint -save -e708 */
/** Rev. 1.11, CR #76 Added entries for rear modules */
static const word_t au16APPLDIAGServices0x2E[APPLDIAG_NUMBER_OF_SLAVES][NoOfAPPLDIAGService0x2EPosition] =
{
		/*   Anp1     Anp2  ProdSerNr  PCBANum(X) MotorNum(X) ProdNum(X) Calib(X) Access[X]  DataDump*/
		{ {0xFD00}, {0xFD01}, {0xFD02}, {0xFD03}, {0xFD04}, {0xFD05}, {0xFD06}, {0xFD07}, {0xFD08} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },

		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} }
};
/*lint -restore */

/** @brief active service state dependent on 0x2E service config table
 *
 * This table sets the state for the statemachine, where the requested service is executed.
 * Dependent on the column of table au16APPLDIAGServices0x2E, next state is pulled from this stable and executed.
 * Internal services, that are opened by service 0xFD04 and password KSE have to be put behind position tAPPLDIAGService0x22StartinternalServices!!
 * @sa tAPPLDIAGService0x2EStartinternalServices*/
static const APPLDiagActiveServiceType atAPPLDIAGService0x2EDiagState[NoOfAPPLDIAGService0x2EPosition] =
{
		LD_Anpassung1,
		LD_AnpassungZuruecksetzen1,

		LD_WETProdWriteSerialNumber,
		LD_ProdWritePCBANumber,
		LD_ProdWriteMotorNumber,
		LD_ProdWriteProductNumber,
		LD_ProdWriteCalibration,
		LD_VICKProdOpenECU,

		LD_VICKDataDump
};

/** to determine if the requersted service is an internal service */
static const APPLDIAGService0x2EPositionType tAPPLDIAGService0x2EStartinternalServices = WETProdWriteSerialNumber;


typedef enum
{
	EOLNULL,
  EOLService1,
	EOLService2,
	EOLService3,
	EOLService4,
	EOLService5,
	EOLService6,
	EOLService7,
	EOLService8,

	NoOfAPPLDIAGService0x31Position
} APPLDIAGService0x31PositionType;

static const word_t au16APPLDIAGServices0x31[APPLDIAG_NUMBER_OF_SLAVES][NoOfAPPLDIAGService0x31Position] =
{
	 /*  EOLNULL    EOL1      EOL2       EOL3     EOL4       EOL5     EOL6      EOL7      EOL8*/
		{ {0xFD00}, {0xFD01}, {0xFD02}, {0xFD03}, {0xFD04}, {0xFD05}, {0xFD06}, {0xFD07}, {0xFD08} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },

		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} },
		{ {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF}, {0xFFFF} }
};

static const APPLDiagActiveServiceType atAPPLDIAGService0x31DiagState[NoOfAPPLDIAGService0x31Position] =
{
		LD_EOLNULL,
		LD_EOLService1,
		LD_EOLService2,
		LD_EOLService3,
		LD_EOLService4,
		LD_EOLService5,
		LD_EOLService6,
		LD_EOLService7,
		LD_EOLService8
};

static const APPLDIAGService0x31PositionType tAPPLDIAGService0x31StartinternalServices = EOLService1;

/** struct placed over diagnosis buffer to access data object in an easy way */
static volatile APPLDIAGAnpassung2Type * ptAnpassung2 = (APPLDIAGAnpassung2Type *)&(au8TXData[APPLDIAG_UDS_DATA_OFFSET]);
/** struct placed over diagnosis buffer to access data object in an easy way */
static volatile APPLDIAGMesswerte1Type * ptMesswerte1 = (APPLDIAGMesswerte1Type *)au8TXData;


/******************************************************************************
 * FUNCTIONS
 *****************************************************************************/

unsigned int uipresendlength = INIT;
void ld_send_message_preparing(l_u16 length, const l_u8* const data)
{
	uipresendlength = length;	
}


/**
 * @brief Resets diagnosis statemachine
 * @details This function is called when ECU is configured to a new HW coding.
 * 			It shall reset the diagnosis statemachine.
 */
void vAPPLDiagResetDiag(void)
{
	tDiagState = LD_INIT;
}

// SID 0x31 routine
// temperature calibration
// eol machine read temperature from CFM
// eol machine read temperature from external
// eol machine do calculation
void RunEOLService_TemperatureCalibration()
{
	unsigned char  routinetype = au8TXData[1];
	
	if(routinetype==0x03)
	{		
		// save temperature to au8TXData;
		au8TXData[4] = (unsigned char)((guiTemperature_nocalibration>>8)&0x00ff);
		au8TXData[5] = (unsigned char)(guiTemperature_nocalibration&0x00ff);
		
		ld_send_message_preparing(6,au8TXData);
		tDiagState = LD_SEND_RESPONSE;		
	}	
	else
	{
		vAPPLDIAGSendNegativeResponse(APPLDIAG_UDS_NRC_ConditionsNotCorrect);
	}
}




// SID 0x31 routine
// current calibration
// eol machine set low current  - 0A
// eol machine read low current offset

// eol machine set high current - 30A
// eol machine start routine with high current
// eol machine stop routine with high current
// eol machine read high current
#include "EOLT.h"

// eol machine do calculation
void RunEOLService_CurrentCalibration()
{
	unsigned char  routinetype = au8TXData[1];
	unsigned int routineoption = au8TXData[4]<<8|au8TXData[5];
	
	if((guiControlSpeed!=0)||(guiActualSpeed!=0))
	{
		routinetype = 0x00; // if the motor is running, skip this eol service.
	}
			
	gEOLTRoutinues.ids = CURRENTCalib;
	gEOLTRoutinues.steps = routinetype;
	
	switch(routinetype)
	{		
		case 0x00: 
			vAPPLDIAGSendNegativeResponse(APPLDIAG_UDS_NRC_ConditionsNotCorrect);
			break;
		
		case 0x01: // start
			// open low-3-phase mosfets
			// BDRV_Set_Bridge(l1,h1,l2,h2,l3,h3)
			
			gEOLTRoutinues.Paramters.uiparameters = 0;
			gEOLTRoutinues.uireturndata = 0;
		
			ld_send_message_preparing(APPLDIAG_UDS_POSITIVE_RESPONSE_DATALENGTH+1,au8TXData);
			tDiagState = LD_SEND_RESPONSE;
			break;
		case 0x02: // stop 
			// current measurement
			// closed low-3-phase mosfets
		
			ld_send_message_preparing(APPLDIAG_UDS_POSITIVE_RESPONSE_DATALENGTH+1,au8TXData);
			tDiagState = LD_SEND_RESPONSE;
			break;		
		case 0x03: // read data
		    // save current to au8TXData;
			gEOLTRoutinues.uireturndata = guiEOLTCurrentFilteredValue;
			au8TXData[4] = (unsigned char)((gEOLTRoutinues.uireturndata>>8)&0x00ff);
			au8TXData[5] = (unsigned char)(gEOLTRoutinues.uireturndata&0x00ff);
		
			ld_send_message_preparing(6,au8TXData);
			tDiagState = LD_SEND_RESPONSE;		
			break;
		default: 
			vAPPLDIAGSendNegativeResponse(APPLDIAG_UDS_NRC_ConditionsNotCorrect);
			break;		
	}	
}

// SID 0x31 routine
// voltage calibration
// eol machine set low voltage  - 9V
// eol machine read low volatge
// eol machine set high voltage  - 16V
// eol machine read high volatge
// eol machine do calculation

void RunEOLService_VoltageCalibration()
{
	unsigned char  routinetype = au8TXData[1];
	unsigned int routineoption = au8TXData[4]<<8|au8TXData[5];
	
	if(routinetype==0x03)
	{
				
		// save voltage to au8TXData;
		au8TXData[4] = (unsigned char)((guiVoltage_nocalibration>>8)&0x00ff);
		au8TXData[5] = (unsigned char)(guiVoltage_nocalibration&0x00ff);
		
		ld_send_message_preparing(6,au8TXData);
		tDiagState = LD_SEND_RESPONSE;		
	}		
	else
	{
		vAPPLDIAGSendNegativeResponse(APPLDIAG_UDS_NRC_ConditionsNotCorrect);
	}	
}

unsigned char ucarrs[2]= {0,0};
void RunEOLService4_PhasesCurrentTest(void)
{
	unsigned char routinetype   = au8TXData[1];
	unsigned char routineselect = au8TXData[4]; // UVW
	unsigned char routineduty   = au8TXData[5]; // duty config. 0~255->0%~100%
	
	if((guiControlSpeed!=0)||(guiActualSpeed!=0))
	{
		routinetype = 0x00; // if the motor is running, skip this eol service.
	}
	
	gEOLTRoutinues.ids   = PHASECURTest;
	gEOLTRoutinues.steps = routinetype;
	
	switch(routinetype)
	{		
		case 0x00: 
			// open low-3-phase mosfets
			// BDRV_Set_Bridge(l1,h1,l2,h2,l3,h3)
			vAPPLDIAGSendNegativeResponse(APPLDIAG_UDS_NRC_ConditionsNotCorrect);
			break;
			
		case 0x01: // start			
			gEOLTRoutinues.uireturndata              = 0;	
			
			gEOLTRoutinues.Paramters.ucparameters[0] = routineselect;
			gEOLTRoutinues.Paramters.ucparameters[1] = routineduty;	
		
			ld_send_message_preparing(APPLDIAG_UDS_POSITIVE_RESPONSE_DATALENGTH+1,au8TXData);
			tDiagState = LD_SEND_RESPONSE;
			break;
		case 0x02: // stop 
			// current measurement
			// closed low-3-phase mosfets
		
			ld_send_message_preparing(APPLDIAG_UDS_POSITIVE_RESPONSE_DATALENGTH+1,au8TXData);
			tDiagState = LD_SEND_RESPONSE;
			break;		
		case 0x03: // read data
		  // save current to au8TXData;
			gEOLTRoutinues.uireturndata = guiEOLTCurrentFilteredValue;
			au8TXData[4] = (unsigned char)((gEOLTRoutinues.uireturndata>>8)&0x00ff);
			au8TXData[5] = (unsigned char)(gEOLTRoutinues.uireturndata&0x00ff);
			
			// au8TXData must read before sending.
			ucarrs[0] = au8TXData[4];
			ucarrs[1] = au8TXData[5];						
		
			ld_send_message_preparing(6,au8TXData);
			tDiagState = LD_SEND_RESPONSE;		
			break;
		default: 
			vAPPLDIAGSendNegativeResponse(APPLDIAG_UDS_NRC_ConditionsNotCorrect);
			break;		
	}		
}

void RunEOLService5_KL15Check(void)
{
	unsigned char  routinetype = au8TXData[1];
	//unsigned int routineoption = au8TXData[4]<<8|au8TXData[5];
	
	if((guiControlSpeed!=0)||(guiActualSpeed!=0))
	{
		routinetype = 0x00; // if the motor is running, skip this eol service.
	}
			
	gEOLTRoutinues.ids = KL15Check;
	gEOLTRoutinues.steps = routinetype;
	
	switch(routinetype)
	{		
		case 0x00: 
			vAPPLDIAGSendNegativeResponse(APPLDIAG_UDS_NRC_ConditionsNotCorrect);
			break;
		
		case 0x01: // start			
			gEOLTRoutinues.Paramters.uiparameters = 0;
			gEOLTRoutinues.uireturndata = 0;
		
			ld_send_message_preparing(APPLDIAG_UDS_POSITIVE_RESPONSE_DATALENGTH+1,au8TXData);
			tDiagState = LD_SEND_RESPONSE;
			break;
		case 0x02: // stop 
			ld_send_message_preparing(APPLDIAG_UDS_POSITIVE_RESPONSE_DATALENGTH+1,au8TXData);
			tDiagState = LD_SEND_RESPONSE;
			break;		
		case 0x03: // read data
		  // save kl15 signal detected data to au8TXData;
			gEOLTRoutinues.uireturndata = guiKL15CheckCntr;
			au8TXData[4] = (unsigned char)((gEOLTRoutinues.uireturndata>>8)&0x00ff);
			au8TXData[5] = (unsigned char)(gEOLTRoutinues.uireturndata&0x00ff);
		
			ld_send_message_preparing(6,au8TXData);
			tDiagState = LD_SEND_RESPONSE;		
			break;
		default: 
			vAPPLDIAGSendNegativeResponse(APPLDIAG_UDS_NRC_ConditionsNotCorrect);
			break;		
	}		
}

void RunEOLService6_EnterToBoot(void)
{
	unsigned char  routinetype = au8TXData[1];
	unsigned int routineoption = au8TXData[4]<<8|au8TXData[5];
	
	if(routinetype==0x00)
	{
		gucBootloaderFlag = FLAG_SET;
				
		// save voltage to au8TXData;
		au8TXData[4] = 0x11;
		au8TXData[5] = 0x22;
		
		ld_send_message_preparing(6,au8TXData);
		tDiagState = LD_SEND_RESPONSE;		
	}		
	else
	{
		vAPPLDIAGSendNegativeResponse(APPLDIAG_UDS_NRC_ConditionsNotCorrect);
	}	
		
}

static void vAPPLDIAGReadFromROM(unsigned int addressdefined, unsigned char datalength)
{
	uint8_t i;
	unsigned char datapointarr1[16]={0,0,0,0,0,0};	
	getdatafromflash_1(datapointarr1, addressdefined/16, datalength);

	au8TXData[APPLDIAG_UDS_RESPONSE_OFFSET] = APPLDIAG_UDS_RESP_ReadDataByIdentifier;
	au8TXData[APPLDIAG_UDS_DATA_OFFSET+0]=(addressdefined>>8)&0x000000ff;
	au8TXData[APPLDIAG_UDS_DATA_OFFSET+1]=   (addressdefined)&0x000000ff;
	
	for(i=0;i<SW_READ_ARR_LENGTH;i++)
	{
		au8TXData[i+APPLDIAG_UDS_DATA_OFFSET+2] = datapointarr1[i];
	}
	ld_send_message_preparing(APPLDIAG_MAKE_UDS_DATA_LENGTH(SW_READ_ARR_LENGTH+2),au8TXData);
	tDiagState = LD_SEND_RESPONSE;
}

static void vAPPLDIAGWriteToROM(unsigned int addressdefined, unsigned char datalength)
{
		unsigned char temparr[16]={0};
		unsigned char i = 0;
				
		for(i=0;i<16;i++)
		{
			temparr[i] = au8TXData[3+i];
		}
	
		flashoperation_1(temparr, addressdefined/16, datalength);
		
		au8TXData[APPLDIAG_UDS_RESPONSE_OFFSET] = APPLDIAG_UDS_RESP_WriteDataByIdentifier;
		ld_send_message_preparing(APPLDIAG_UDS_POSITIVE_RESPONSE_DATALENGTH,au8TXData);
		tDiagState = LD_SEND_RESPONSE;
}

unsigned int uiaddress=0;
void vAPPLDIAGAnpassung1Read(void)
{
	uiaddress = (au8RXData[3]<<8)|au8RXData[4];
	vAPPLDIAGReadFromROM(uiaddress, SW_READ_ARR_LENGTH);
}

/** @brief This function just sends a negative answer to an UDS request
 * @param u8NRC The NRC (negative response code) to send
 */
static void vAPPLDIAGSendNegativeResponse(uint8_t u8NRC)
{
	APPLDIAG_CONVERT_REQUEST_TO_NEG_RESPONSE_WITH_NRC(u8NRC);
	ld_send_message_preparing(APPLDIAG_UDS_NEG_RESP_LENGTH,au8TXData);
	tDiagState = LD_SEND_RESPONSE;
}


//If the request is sent to broadcast NAD and datalength or password is wrong, no answer is sent and data access is not granted
//If the request is sent to broadcast NAD and password is correct, data access is granted, but no answer is sent for the first request
//If the request is sent to broadcast NAD and password is correct and data access was granted already, a positive answer is sent
//If the request is sent to "normal" NAD and datalength is wrong, NRC 0x13 is sent and data access is not granted
//If the request is sent to "normal" NAD and password is wrong, NRC 0x31 is sent and data access is not granted
//If the request is sent to "normal" NAD and password is correct, data access is granted and a NRC 0x31 is sent for the first request
//If the request is sent to "normal" NAD and password is correct and data acess was granted already, a positive answer is sent
static void vAPPLDIAGEvalOpenECU(void)
{
	// get NAD
	g_lin_diag_mreq.frame.NAD = getnad();
	
	if(u16RXLength != APPLDIAG_MAKE_UDS_DATA_LENGTH(APPLDIAG_OPEN_ECU_DATALENGTH))
	{
		/* broadcast NAD an ECU not open for data access, send no answer */
		if((g_lin_diag_mreq.frame.NAD == APPLDIAG_BROADCAST_NAD) && (APPLDIAG_VICKPRODMODEACTIVE != u16VICKProdMode))
		{
			tDiagState = LD_INIT;
		}
		else
		{
			tActiveService = LD_IncorrectLength;
		}
	}
	else
	{
		/* if broadcast NAD do not answer. If "normal" NAD send RDIDNotSupported */
		if(g_lin_diag_mreq.frame.NAD != APPLDIAG_BROADCAST_NAD)
		{
			tActiveService = LD_RDIDNotSupported;
		}
		else
		{
			tDiagState = LD_INIT;
		}

		if(	(au8TXData[APPLDIAG_UDS_DATA_OFFSET]   == 'A') &&
				(au8TXData[APPLDIAG_UDS_DATA_OFFSET+1] == 'B') &&
				(au8TXData[APPLDIAG_UDS_DATA_OFFSET+2] == 'C')
		)
		{
			if(APPLDIAG_VICKPRODMODEACTIVE == u16VICKProdMode)
			{
				au8TXData[APPLDIAG_UDS_RESPONSE_OFFSET] = APPLDIAG_UDS_RESP_WriteDataByIdentifier;
				ld_send_message_preparing(APPLDIAG_UDS_POSITIVE_RESPONSE_DATALENGTH,au8TXData);
				tDiagState = LD_SEND_RESPONSE;
			}
			else
			{
				/* tActiveService and tDiagState is set already */
				u16VICKProdMode = APPLDIAG_VICKPRODMODEACTIVE;
			}
		}
	}

}

static void vVICKDataDump(void)
{
	
}


unsigned char EOL_Receivedflag = 0;
//unsigned char EOL_SID;
unsigned char EOL_controltype;
unsigned char EOL_routineID[2];
unsigned char EOL_controloption[2];

				
static void tAPPLDIAGEvaluateRequest(void)
{
	unsigned char u8APPLDiagFRD = 0;
	uint8_t i;
	const word_t * ptService;
	word_t u16Service;

	// get NAD
	g_lin_diag_mreq.frame.NAD = getnad();
	
	u16RXLength = u16ReceivedDataLength;
	do
	{
		u16ReceivedDataLength--;
		au8TXData[u16ReceivedDataLength] = au8RXData[u16ReceivedDataLength];
	}
	while(u16ReceivedDataLength>0);

	if(au8TXData[APPLDIAG_UDS_RESPONSE_OFFSET] == APPLDIAG_UDS_SID_ReadDataByIdentifier)
	{
		/* check if broadcast NAD is valid. Only valid, if VICK production mode is active */
		/* if "normal service" is requested with NAD 0x7F and ECU is open, then service is executed */
		//u16VICKProdMode = 0x55AA;
		if((g_lin_diag_mreq.frame.NAD == APPLDIAG_BROADCAST_NAD) && (APPLDIAG_VICKPRODMODEACTIVE != u16VICKProdMode))
		{
			/* send no answer */
			tDiagState = LD_INIT;
		}
		/* check for correct length */
		else if((u16RXLength != APPLDIAG_UDS_RDBI_Length)&&(u16RXLength != APPLDIAG_UDS_RDBI_Length_With2Params))
		{
			tActiveService = LD_IncorrectLength;
			tDiagState = LD_PROCESS_REQUEST;
		}
		else
		{
			
			ptService = au16APPLDIAGServices0x22[u8APPLDiagFRD];
			

			i = 0;

			u16Service.bytes.highbyte = au8TXData[APPLDIAG_UDS_RDID_HIGHBYTE_OFFSET];
			u16Service.bytes.lowbyte = au8TXData[APPLDIAG_UDS_RDID_LOWBYTE_OFFSET];

			while((ptService->word != u16Service.word) && (i < (uint8_t)NoOfAPPLDIAGService0x22Position))
			{
				ptService++;
				i++;
			}
			/* if service not found in table or internal Service is requested and production mode is not active -> send RDID not supported */
			if((i >= (uint8_t)NoOfAPPLDIAGService0x22Position) ||
					((APPLDIAG_VICKPRODMODEACTIVE != u16VICKProdMode) && (i >= (uint8_t)tAPPLDIAGService0x22StartinternalServices)))
			{

				tActiveService =  LD_RDIDNotSupported;
			}
			else
			{
				tActiveService = atAPPLDIAGService0x22DiagState[i];
			}

			tDiagState = LD_PROCESS_REQUEST;
		}

	}
	else if(au8TXData[APPLDIAG_UDS_RESPONSE_OFFSET] == APPLDIAG_UDS_SID_WriteDataByIdentifier)
	{
		ptService = au16APPLDIAGServices0x2E[u8APPLDiagFRD];


		i = 0;

		u16Service.bytes.highbyte = au8TXData[APPLDIAG_UDS_RDID_HIGHBYTE_OFFSET];
		u16Service.bytes.lowbyte = au8TXData[APPLDIAG_UDS_RDID_LOWBYTE_OFFSET];

		while((ptService->word != u16Service.word) && (i < (uint8_t)NoOfAPPLDIAGService0x2EPosition))
		{
			ptService++;
			i++;
		}

		/* first, set tDiagState to process request. Checks if service can be executed follow. If not, tDiagState is set to LD_INIT */
		tDiagState = LD_PROCESS_REQUEST;

		if(i >= (uint8_t)NoOfAPPLDIAGService0x2EPosition)
		{
			/* service not found in table */

			/* if broadcast NAD do not answer */
			if(g_lin_diag_mreq.frame.NAD == APPLDIAG_BROADCAST_NAD)
			{
				tDiagState = LD_INIT;
			}
			else
			{
				tActiveService =  LD_RDIDNotSupported;
			}
		}
		else
		{
			//u16VICKProdMode = 0x55AA;
			
			tActiveService = atAPPLDIAGService0x2EDiagState[i];
			/* if service is open ECU then do it all the time */
			if(tActiveService == LD_VICKProdOpenECU)
			{

			}
			/* if broadcast NAD and production mode not open, do not send an answer */
			else if ((g_lin_diag_mreq.frame.NAD == APPLDIAG_BROADCAST_NAD) && (APPLDIAG_VICKPRODMODEACTIVE != u16VICKProdMode))
			{
				tDiagState = LD_INIT;
			}
			/* if not broadcast NAD and and production mode not open and an internal service is requested -> send RDID not supported */
			else if ((APPLDIAG_VICKPRODMODEACTIVE != u16VICKProdMode) && (i >= (uint8_t)tAPPLDIAGService0x2EStartinternalServices))
			{
				tActiveService =  LD_RDIDNotSupported;
			}
			else
			{

			}
			/* else service the request. tDiagState is set already! */
		}
	}
	else if(au8TXData[APPLDIAG_UDS_RESPONSE_OFFSET] == APPLDIAG_UDS_SID_RoutinesControlByIdentifier)
	{
		//u16VICKProdMode = 0x55AA;
		if((g_lin_diag_mreq.frame.NAD == APPLDIAG_BROADCAST_NAD) && (APPLDIAG_VICKPRODMODEACTIVE != u16VICKProdMode))
		{
			/* send no answer */
			tDiagState = LD_INIT;
		}
		/* check for correct length */
		else if(u16RXLength != APPLDIAG_UDS_ROUTINES_CONTROL_Length)
		{
			tActiveService = LD_IncorrectLength;
			tDiagState = LD_PROCESS_REQUEST;
		}
		else
		{
			
			ptService = au16APPLDIAGServices0x31[u8APPLDiagFRD];
			

			i = 0;

			u16Service.bytes.highbyte = au8TXData[APPLDIAG_UDS_RDID_HIGHBYTE_OFFSET+1];
			u16Service.bytes.lowbyte = au8TXData[APPLDIAG_UDS_RDID_LOWBYTE_OFFSET+1];

			while((ptService->word != u16Service.word) && (i < (uint8_t)NoOfAPPLDIAGService0x31Position))
			{
				ptService++;
				i++;
			}
			/* if service not found in table or internal Service is requested and production mode is not active -> send RDID not supported */
			if((i >= (uint8_t)NoOfAPPLDIAGService0x31Position) ||
					((APPLDIAG_VICKPRODMODEACTIVE != u16VICKProdMode) && (i >= (uint8_t)tAPPLDIAGService0x31StartinternalServices)))
			{

				tActiveService =  LD_RDIDNotSupported;
			}
			else
			{
				tActiveService = atAPPLDIAGService0x31DiagState[i];				
			}

			tDiagState = LD_PROCESS_REQUEST;
		}
		
	}
	else
	{
		/* SID not supported. Do not answer if broadcast NAD */
		if(g_lin_diag_mreq.frame.NAD == APPLDIAG_BROADCAST_NAD)
		{
			tDiagState = LD_INIT;
		}
		else
		{
			tActiveService = LD_SIDNotSupported;
			tDiagState = LD_PROCESS_REQUEST;
		}
	}


}
/**
 * @brief Diagnosis Statemachine
 * @details This function is being called every 10ms in main loop
 * @pre LIN driver initialized
 */

void eolstartingcheck()
{
	if(gucLINEOLServiceReceivedFlag ==FLAG_SET)
	{
		if(guiLINEOLServiceCounter)
		{
			guiLINEOLServiceCounter--;
		}
		else
		{
			gucLINEOLServiceReceivedFlag = FLAG_RESET;
			u16VICKProdMode = INIT; // clear pwd after no uds service.
		}
	}	
}

unsigned char gucEOLTFirstSkipFlag = FLAG_RESET;
void lineolindication(void)
{
	if(gucEOLTFirstSkipFlag == FLAG_RESET)
	{
		gucEOLTFirstSkipFlag = FLAG_SET;
	}
	else
	{
		guiLINEOLServiceCounter         = 400;// 4 s;
		gucLINEOLServiceReceivedFlag    = FLAG_SET;
		gucLINSignalReceivedFlag        = FLAG_SET;
	}
}

#include "lin_lin21tl_api.h"
unsigned char diagServiceFlag_1[6] =
{
	 DIAGSRV_READ_DATA_BY_IDENTIFIER_ORDER,
	 DIAGSRV_WRITE_DATA_BY_IDENTIFIER_ORDER,
	 DIAGSRV_ROUTINECONTROL_ORDER,
	 //DIAGSRV_SESSION_CONTROL_ORDER,
	 //DIAGSRV_IO_CONTROL_BY_IDENTIFIER_ORDER,
	 //DIAGSRV_FAULT_MEMORY_READ_ORDER,   
	 //DIAGSRV_FAULT_MEMORY_CLEAR_ORDER          
};


unsigned char ucudsreceivedflag = FLAG_RESET;
unsigned char receiveddata = 0;
unsigned char diagnosticindex = 0;
void vAPPLLinDiag(void)
{
	const uint8_t * ptSystemname;
	static uint8_t u8WETEEPResetState = 0;
	static word_t tCurrentRDID;
	uint8_t i;

	eolstartingcheck();	
		
#ifdef USEWCETMEASUREMENT
	u8CurrentPath = ((tDiagState & 3) << 6) | ((tActiveService + 1) & 63);
#endif
	switch(tDiagState)
	{
	case LD_INIT:
		/* wait until all RAMBuffers are initialized */
		//if(tEEMAreAllRAMBuffersInitialized() == EEMAllRAMBuffersInitialized)
		{
//			/* wait for a diagnosis request */
//			u16ReceivedDataLength = APPLDIAG_MAX_REQ_LENGTH;
//			ld_receive_message  (&u16ReceivedDataLength, au8RXData);
			diag_clear_flag(diagServiceFlag_1[diagnosticindex]);
			tDiagState = LD_WAIT_FOR_REQUEST;
		}
		break;

	case LD_WAIT_FOR_REQUEST:	
		
		for (diagnosticindex = 0; diagnosticindex < 6; diagnosticindex++)
		{
			receiveddata = diag_get_flag(diagServiceFlag_1[diagnosticindex]);			
			if (receiveddata!=0)
			{
				ucudsreceivedflag = FLAG_SET;
				
				break;
			}	
		}	  
		
		
		if (ucudsreceivedflag==FLAG_SET)
		{
			ucudsreceivedflag = FLAG_RESET;
			lineolindication();
			
			u16ReceivedDataLength = APPLDIAG_MAX_REQ_LENGTH;
			ld_receive_message  (&u16ReceivedDataLength, au8RXData);
			tAPPLDIAGEvaluateRequest();
		}
		else
		{
			tDiagState = LD_INIT;
		}
		break;

	case LD_PROCESS_REQUEST:


//		if (LD_COMPLETED == ld_rx_status())
//		{		
//			lineolindication();
//			
//			tAPPLDIAGEvaluateRequest();
//			u16ReceivedDataLength = APPLDIAG_MAX_REQ_LENGTH;
//			ld_receive_message  (&u16ReceivedDataLength, au8RXData);
//			break;
//		}

		
		/* process the request */
		switch(tActiveService)
		{

		/* which service was requested? */
		case LD_ProdReadSWID:
			vAPPLDIAGReadFromROM(FLASH_ADDRESS_SWID, SW_READ_ARR_LENGTH);
			break;

		case LD_ProdReadPCBANumber:
			vAPPLDIAGReadFromROM(FLASH_ADDRESS_PARTNUMBER_PCBA, SW_READ_ARR_LENGTH);
			break;

		case LD_ProdReadMotorNumber:
			vAPPLDIAGReadFromROM(FLASH_ADDRESS_PARTNUMBER_MOTOR, SW_READ_ARR_LENGTH);
			break;

		case LD_ProdReadProductNumber:
			vAPPLDIAGReadFromROM(FLASH_ADDRESS_PARTNUMBER_PRODUCT, SW_READ_ARR_LENGTH);
			break;

		case LD_ProdReadCalibration:
			vAPPLDIAGReadFromROM(FLASH_ADDRESS_CALCULATION_START, SW_READ_ARR_LENGTH);
			break;

		case LD_WETProdReadHWVersion:
			//
			break;

		case LD_VWSlaveHardwareVersionNum:
			//vAPPLDIAGReadFromROM(FLASH_ADDRESS_PARTNUMBER_PCBA, SW_READ_ARR_LENGTH);
			break;

		case LD_WETProdReadSerialNumber:
			//vAPPLDIAGReadFromEEDirect(EEMWETSerialNumberAdress, EEMWETSerialNumberDataLength);
			break;

		case LD_VWSlaveSerialNumber:
			//vAPPLDIAGReadFromRAM(au8APPLDIAGSerialNumber, EEMWETSerialNumberDataLength);
			break;

		case LD_VWSlaveSystemName:
//			/* Rev. 1.11 replaced u8PINCODINGCodingStoredInEE with u8APPLDiagFRD */
//			if(0 == l_bool_rd_Verbauposition_LLR())
//			{
//				/* front row. Use au8SystemNames[0..7] */
//				ptSystemname = acu8SystemNames[u8APPLDiagFRD];
//			}
//			else
//			{
//				/* rear row. Use au8SystemNames[8..15] */
//				ptSystemname = acu8SystemNames[u8APPLDiagFRD|0x08];
//			}
//			vAPPLDIAGReadFromROM(ptSystemname, APPLDIAG_SLAVESYSTEMNAME_DATALENGTH);
			break;

		case LD_WETProdWriteSerialNumber:
//			vAPPLDIAGWriteEEM(EEMHandleWETSerialNumber, EEMWETSerialNumberDataLength);
//			if(LD_IncorrectLength != tActiveService)
//			{
//				tActiveService = LD_WETProdWriteSerialNumber2;
//			}
			break;

		case LD_WETProdWriteSerialNumber2:
//			for(i = 0; i < EEMWETSerialNumberDataLength; i++)
//			{
//				au8APPLDIAGSerialNumber[i] = au8TXData[APPLDIAG_UDS_DATA_OFFSET+i];
//			}
//			tActiveService = LD_WaitEEPROM;
//			u8EETimeout++;
			break;

		case LD_ProdWritePCBANumber:
			vAPPLDIAGWriteToROM(FLASH_ADDRESS_PARTNUMBER_PCBA, SW_WRITE_ARR_LENGTH);
			break;

		case LD_ProdWriteMotorNumber:
			vAPPLDIAGWriteToROM(FLASH_ADDRESS_PARTNUMBER_MOTOR, SW_WRITE_ARR_LENGTH);
			break;

		case LD_ProdWriteProductNumber:
			vAPPLDIAGWriteToROM(FLASH_ADDRESS_PARTNUMBER_PRODUCT, SW_WRITE_ARR_LENGTH);
			break;

		case LD_ProdWriteCalibration:
			vAPPLDIAGWriteToROM(FLASH_ADDRESS_CALCULATION_START, SW_WRITE_ARR_LENGTH);
			break;

		case LD_VICKProdOpenECU:
			vAPPLDIAGEvalOpenECU();
			break;

		case LD_WETReadTemperature:
//			au8TXData[APPLDIAG_UDS_RESPONSE_OFFSET] = APPLDIAG_UDS_RESP_ReadDataByIdentifier;
//			au8TXData[APPLDIAG_UDS_DATA_OFFSET] = (uint8_t)nRealTemp;
//			ld_send_message(APPLDIAG_MAKE_UDS_DATA_LENGTH(APPLDIAG_WET_READ_TEMPERATURE_DATALENGTH),au8TXData);
//			tDiagState = LD_SEND_RESPONSE;

			break;

		case LD_VICKDataDump:
			if(u16RXLength != APPLDIAG_MAKE_UDS_DATA_LENGTH(APPLDIAG_KSE_DATA_DUMP_LENGTH))
			{
				tActiveService = LD_IncorrectLength;
				break;
			}
			vVICKDataDump();
			break;

		case LD_Messwerte1:
			//vAPPLDIAGMesswerte1();
			break;

		case LD_Anpassung1:
			//vAPPLDIAGAnpassung1Write();
			break;

		case LD_Anpassung1Read:
			vAPPLDIAGAnpassung1Read();
			break;

		case LD_AnpassungZuruecksetzen1Read:
			//vAPPLDIAGAnpassungReset1Read();
			break;

		case LD_AnpassungZuruecksetzen1:
			//vAPPLDIAGAnpassungReset1Write();
			break;

		case LD_AnpassungCommandWrite:
//			tAPPLDIAGCurrentHandle = EEMHandleAnpassung1;
//			vEEMWrite(tAPPLDIAGCurrentHandle, (const uint8_t *)ptAnpassung1->bytes);	/*lint !e926 */

//			u8EETimeout++;
//			tActiveService = LD_WaitEEPROM;
			break;

		case LD_WETReadErrorCounter:
//			au8TXData[APPLDIAG_UDS_RESPONSE_OFFSET] = APPLDIAG_UDS_RESP_ReadDataByIdentifier;
//			vEEMRead(EEMHandleSTKOVF, 	&au8TXData[APPLDIAG_UDS_DATA_OFFSET]);
//			vEEMRead(EEMHandleSTKUNF,  	&au8TXData[APPLDIAG_UDS_DATA_OFFSET+1]);
//			vEEMRead(EEMHandleWDReset, 	&au8TXData[APPLDIAG_UDS_DATA_OFFSET+2]);
//			vEEMRead(EEMHandleBOR, 		&au8TXData[APPLDIAG_UDS_DATA_OFFSET+3]);
//			vEEMRead(EEMHandleROMDefect,&au8TXData[APPLDIAG_UDS_DATA_OFFSET+4]);
//			vEEMRead(EEMHandleRAMDefect,&au8TXData[APPLDIAG_UDS_DATA_OFFSET+5]);
//			vEEMRead(EEMHandleEEDefect, &au8TXData[APPLDIAG_UDS_DATA_OFFSET+6]);

//			ld_send_message(APPLDIAG_MAKE_UDS_DATA_LENGTH(APPLDIAG_WET_READ_ERROR_COUNTER_DATALENGTH),au8TXData);
//			tDiagState = LD_SEND_RESPONSE;

			break;

		case LD_WaitEEPROM:
//			tCurrentRDID.bytes.highbyte = au8TXData[APPLDIAG_UDS_RDID_HIGHBYTE_OFFSET];
//			tCurrentRDID.bytes.lowbyte = au8TXData[APPLDIAG_UDS_RDID_LOWBYTE_OFFSET];

//			u8EETimeout++;
//			if(EEMDirtyStateDirty == tEEMIsHandleDirty(tAPPLDIAGCurrentHandle))
//			{
//				if(u8EETimeout > APPLDIAG_TTimeout_LIN)
//				{
//					APPLDIAG_CONVERT_REQUEST_TO_NEG_RESPONSE_WITH_NRC(APPLDIAG_UDS_NRC_ResponsePendig);
//					ld_send_message(APPLDIAG_UDS_NEG_RESP_LENGTH,au8TXData);
//					tActiveService = LD_SendResponsePending;
//				}
//			}
//			else
//			{
//				au8TXData[APPLDIAG_UDS_RESPONSE_OFFSET] = APPLDIAG_UDS_RESP_WriteDataByIdentifier;
//				ld_send_message(APPLDIAG_UDS_POSITIVE_RESPONSE_DATALENGTH,au8TXData);
//				tDiagState = LD_SEND_RESPONSE;
//			}
			break;

		case LD_SendResponsePending:
//			if(ld_tx_status() == LD_IN_PROGRESS)
//			{

//			}
//			else if(ld_tx_status() == LD_COMPLETED)
//			{
//				u8EETimeout = 1;
//				tActiveService = LD_WaitEEPROMSecondTime;
//			}
//			else
//			{
//				tDiagState = LD_INIT;
//			}
			break;

		case LD_WaitEEPROMSecondTime:
			break;
		
		//-------------------
		// EOL related items, locate in EOLRoutines.c;
		case LD_EOLNULL:
			break;
		case LD_EOLService1:
			//test
			//vAPPLDIAGSendNegativeResponse(APPLDIAG_UDS_NRC_ConditionsNotCorrect);
			RunEOLService_TemperatureCalibration();
			break;
		case LD_EOLService2:
			RunEOLService_CurrentCalibration();
			break;
		case LD_EOLService3:
			RunEOLService_VoltageCalibration();
			break;
		case LD_EOLService4:
			RunEOLService4_PhasesCurrentTest();
			break;
		case LD_EOLService5:
			RunEOLService5_KL15Check();
			break;
		case LD_EOLService6:
			RunEOLService6_EnterToBoot();
			break;
		case LD_EOLService7:
			//RunEOLService7();
			break;
		case LD_EOLService8:
			//RunEOLService8();
			break;		
		// EOL end
		//-------------------

		case LD_SIDNotSupported:
			vAPPLDIAGSendNegativeResponse(APPLDIAG_UDS_NRC_SIDNotSupported);
			break;

		case LD_IncorrectLength:
			vAPPLDIAGSendNegativeResponse(APPLDIAG_UDS_NRC_InCorrectMessageLenght);
			break;

		case LD_ConditionsNotCorrect:
			vAPPLDIAGSendNegativeResponse(APPLDIAG_UDS_NRC_ConditionsNotCorrect);
			break;

		case LD_RDIDNotSupported:
		case LD_None:
		case LD_RequestOutOfRange:
		default:
			tActiveService = LD_RDIDNotSupported;

			vAPPLDIAGSendNegativeResponse(APPLDIAG_UDS_NRC_RequestOutOfRange);
			break;

		}
		break;

		case LD_SEND_RESPONSE:			
			ld_send_message(uipresendlength, au8TXData);
			tDiagState = LD_INIT;

		default:
			//HARD_ASSERT(CLEAR, ASSERT_APPLDIAG_ApplLinDiagDefault, (uint8_t)tDiagState);
			tDiagState = LD_INIT;
			break;
	}

	return;

}


//#ifdef MODULETEST
//#include "../../moduletests/mt_appl_diag.c"
//#endif

#define APPLLIN_BUSTIMEOUT				(4)
#define APPLLLIN_BUSTIMEOUTCALLCYCLE	(100)

#define APPLLIN_CHECKTRAFFIC		(0x000F)
static lin_word_status_str tLINStatusWord;// = {{0}};	/*lint !e708 */
static uint16_t u16Timeout = 0;

unsigned char vAPPLLinCheckSleep(void)
{
	tLINStatusWord.word = l_ifc_read_status(LIN_NXP);

	if(SET == tLINStatusWord.bit.gotosleep)
	{
		//vAPPLLinGotoSleep();
		//gucLINGotoSleepFlag = FLAG_SET;
		return FLAG_SET;
		
	}
//	else if(0 != (tLINStatusWord.reg & APPLLIN_CHECKTRAFFIC))
//	{
//		u16Timeout = 0;
//	}
//	else
//	{
//		u16Timeout++;
//		if(u16Timeout > (APPLLIN_BUSTIMEOUT * APPLLLIN_BUSTIMEOUTCALLCYCLE))
//		{
//			/* prevent overrun */
//			u16Timeout = (APPLLIN_BUSTIMEOUT * APPLLLIN_BUSTIMEOUTCALLCYCLE);
//			/* execute goto sleep command */
//#ifndef NOSLEEP
//			//vAPPLLinGotoSleep();
//			global_FailureMode.bit.startsleep = 1;
//#else
//#warning Sleep function disable!
//#endif
//		}
//	}

	return FLAG_RESET;
}

