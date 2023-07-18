#include "appl_diag_nxp.h"

//Request start
                /* package single frame */
                /* ____________________________________________ */
                /* | NAD | PCI | SID | D1 | D2 | D3 | D4 | D5 | */
                /* |_____|_____|_____|____|____|____|____|____| */

                /* package first frame */
                /* ____________________________________________ */
                /* | NAD | PCI | LEN |SID | D1 | D2 | D3 | D4 | */
                /* |_____|_____|_____|____|____|____|____|____| */

                /* package consecutive frame */
                /* ___________________________________________ */
                /* | NAD | PCI | D1 | D2 | D3 | D4 | D5 | D6 | */
                /* |_____|_____|____|____|____|____|____|____| */                                                                      
// Request end
// Response start
                /* package single frame */
                /* ____________________________________________ */
                /* | NAD | PCI | RSID| D1 | D2 | D3 | D4 | D5 | */
                /* |_____|_____|_____|____|____|____|____|____| */

                /* package first frame */
                /* ____________________________________________ */
                /* | NAD | PCI | LEN |RSID| D1 | D2 | D3 | D4 | */
                /* |_____|_____|_____|____|____|____|____|____| */

                /* package consecutive frame */
                /* ___________________________________________ */
                /* | NAD | PCI | D1 | D2 | D3 | D4 | D5 | D6 | */
                /* |_____|_____|____|____|____|____|____|____| */
// Response end

#define PDU_REQUEST_RESPONSE_NAD                0
#define PDU_REQUEST_RESPONSE_PCI                1
#define PDU_REQUEST_RESPONSE_SIGLE_SID_RSID     2
#define PDU_REQUEST_RESPONSE_MUILT_LENGTH       2
#define PDU_REQUEST_RESPONSE_MUILT_SID_RSID     3

#define PDU_REQUEST_USERID_0                    4
#define PDU_REQUEST_USERID_1                    5


typedef enum
{
	SlaveElectrinicNum,
	SlaveMotorNum,
	SlaveModuleNum,
	SlaveCalibration,
	SlaveFeedbackDTC,
	SlaveSWVersion,
	NoOfAPPLDIAGService0x22Position
} APPLDIAGService0x22PositionType;
static unsigned int APPLDIAGServices0x22[NoOfAPPLDIAGService0x22Position]=
{
		0xFD01,
		0xFD02,
		0xFD0B,
		0xFD03,
		0xFD08,
		0xFD0D,
};

typedef enum
{
	SlaveElectrinicNum_w,
	SlaveMotorNum_w,
	SlaveModuleNum_w,
	SlaveCalibration_w,
	SlaveOpenEcu,
	NoOfAPPLDIAGService0x2EPosition
} APPLDIAGService0x2EPositionType;
static unsigned int APPLDIAGServices0x2E[NoOfAPPLDIAGService0x2EPosition]=
{
		0xFD03,
		0xFD04,
		0xFD05,
		0xFD06,
		0xFD07,				
};


//static void tAPPLDIAGEvaluateRequest(void)
//{
//	unsigned char u8APPLDiagFRD = 0;
//	uint8_t i;
//	const word_t * ptService;
//	word_t u16Service;
//
//	// get NAD
//	g_lin_diag_mreq.frame.NAD = getnad();
//	
//	u16RXLength = u16ReceivedDataLength;
//	do
//	{
//		u16ReceivedDataLength--;
//		au8TXData[u16ReceivedDataLength] = au8RXData[u16ReceivedDataLength];
//	}
//	while(u16ReceivedDataLength>0);
//
//	if(au8TXData[APPLDIAG_UDS_RESPONSE_OFFSET] == APPLDIAG_UDS_SID_ReadDataByIdentifier)
//	{
//		/* check if broadcast NAD is valid. Only valid, if VICK production mode is active */
//		/* if "normal service" is requested with NAD 0x7F and ECU is open, then service is executed */
//		//u16VICKProdMode = 0x55AA;
//		if((g_lin_diag_mreq.frame.NAD == APPLDIAG_BROADCAST_NAD) && (APPLDIAG_VICKPRODMODEACTIVE != u16VICKProdMode))
//		{
//			/* send no answer */
//			tDiagState = LD_INIT;
//		}
//		/* check for correct length */
//		else if((u16RXLength != APPLDIAG_UDS_RDBI_Length)&&(u16RXLength != APPLDIAG_UDS_RDBI_Length_With2Params))
//		{
//			tActiveService = LD_IncorrectLength;
//			tDiagState = LD_PROCESS_REQUEST;
//		}
//		else
//		{
//			
//			ptService = au16APPLDIAGServices0x22[u8APPLDiagFRD];
//			
//
//			i = 0;
//
//			u16Service.bytes.highbyte = au8TXData[APPLDIAG_UDS_RDID_HIGHBYTE_OFFSET];
//			u16Service.bytes.lowbyte = au8TXData[APPLDIAG_UDS_RDID_LOWBYTE_OFFSET];
//
//			while((ptService->word != u16Service.word) && (i < (uint8_t)NoOfAPPLDIAGService0x22Position))
//			{
//				ptService++;
//				i++;
//			}
//			/* if service not found in table or internal Service is requested and production mode is not active -> send RDID not supported */
//			if((i >= (uint8_t)NoOfAPPLDIAGService0x22Position) ||
//					((APPLDIAG_VICKPRODMODEACTIVE != u16VICKProdMode) && (i >= (uint8_t)tAPPLDIAGService0x22StartinternalServices)))
//			{
//
//				tActiveService =  LD_RDIDNotSupported;
//			}
//			else
//			{
//				tActiveService = atAPPLDIAGService0x22DiagState[i];
//			}
//
//			tDiagState = LD_PROCESS_REQUEST;
//		}
//
//	}
//	else if(au8TXData[APPLDIAG_UDS_RESPONSE_OFFSET] == APPLDIAG_UDS_SID_WriteDataByIdentifier)
//	{
//		ptService = au16APPLDIAGServices0x2E[u8APPLDiagFRD];
//
//
//		i = 0;
//
//		u16Service.bytes.highbyte = au8TXData[APPLDIAG_UDS_RDID_HIGHBYTE_OFFSET];
//		u16Service.bytes.lowbyte = au8TXData[APPLDIAG_UDS_RDID_LOWBYTE_OFFSET];
//
//		while((ptService->word != u16Service.word) && (i < (uint8_t)NoOfAPPLDIAGService0x2EPosition))
//		{
//			ptService++;
//			i++;
//		}
//
//		/* first, set tDiagState to process request. Checks if service can be executed follow. If not, tDiagState is set to LD_INIT */
//		tDiagState = LD_PROCESS_REQUEST;
//
//		if(i >= (uint8_t)NoOfAPPLDIAGService0x2EPosition)
//		{
//			/* service not found in table */
//
//			/* if broadcast NAD do not answer */
//			if(g_lin_diag_mreq.frame.NAD == APPLDIAG_BROADCAST_NAD)
//			{
//				tDiagState = LD_INIT;
//			}
//			else
//			{
//				tActiveService =  LD_RDIDNotSupported;
//			}
//		}
//		else
//		{
//			//u16VICKProdMode = 0x55AA;
//			
//			tActiveService = atAPPLDIAGService0x2EDiagState[i];
//			/* if service is open ECU then do it all the time */
//			if(tActiveService == LD_VICKProdOpenECU)
//			{
//
//			}
//			/* if broadcast NAD and production mode not open, do not send an answer */
//			else if ((g_lin_diag_mreq.frame.NAD == APPLDIAG_BROADCAST_NAD) && (APPLDIAG_VICKPRODMODEACTIVE != u16VICKProdMode))
//			{
//				tDiagState = LD_INIT;
//			}
//			/* if not broadcast NAD and and production mode not open and an internal service is requested -> send RDID not supported */
//			else if ((APPLDIAG_VICKPRODMODEACTIVE != u16VICKProdMode) && (i >= (uint8_t)tAPPLDIAGService0x2EStartinternalServices))
//			{
//				tActiveService =  LD_RDIDNotSupported;
//			}
//			else
//			{
//
//			}
//			/* else service the request. tDiagState is set already! */
//		}
//	}
//	else if(au8TXData[APPLDIAG_UDS_RESPONSE_OFFSET] == APPLDIAG_UDS_SID_RoutinesControlByIdentifier)
//	{
//		//u16VICKProdMode = 0x55AA;
//		if((g_lin_diag_mreq.frame.NAD == APPLDIAG_BROADCAST_NAD) && (APPLDIAG_VICKPRODMODEACTIVE != u16VICKProdMode))
//		{
//			/* send no answer */
//			tDiagState = LD_INIT;
//		}
//		/* check for correct length */
//		else if(u16RXLength != APPLDIAG_UDS_ROUTINES_CONTROL_Length)
//		{
//			tActiveService = LD_IncorrectLength;
//			tDiagState = LD_PROCESS_REQUEST;
//		}
//		else
//		{
//			
//			ptService = au16APPLDIAGServices0x31[u8APPLDiagFRD];
//			
//
//			i = 0;
//
//			u16Service.bytes.highbyte = au8TXData[APPLDIAG_UDS_RDID_HIGHBYTE_OFFSET+1];
//			u16Service.bytes.lowbyte = au8TXData[APPLDIAG_UDS_RDID_LOWBYTE_OFFSET+1];
//
//			while((ptService->word != u16Service.word) && (i < (uint8_t)NoOfAPPLDIAGService0x31Position))
//			{
//				ptService++;
//				i++;
//			}
//			/* if service not found in table or internal Service is requested and production mode is not active -> send RDID not supported */
//			if((i >= (uint8_t)NoOfAPPLDIAGService0x31Position) ||
//					((APPLDIAG_VICKPRODMODEACTIVE != u16VICKProdMode) && (i >= (uint8_t)tAPPLDIAGService0x31StartinternalServices)))
//			{
//
//				tActiveService =  LD_RDIDNotSupported;
//			}
//			else
//			{
//				tActiveService = atAPPLDIAGService0x31DiagState[i];				
//			}
//
//			tDiagState = LD_PROCESS_REQUEST;
//		}
//		
//	}
//	else
//	{
//		/* SID not supported. Do not answer if broadcast NAD */
//		if(g_lin_diag_mreq.frame.NAD == APPLDIAG_BROADCAST_NAD)
//		{
//			tDiagState = LD_INIT;
//		}
//		else
//		{
//			tActiveService = LD_SIDNotSupported;
//			tDiagState = LD_PROCESS_REQUEST;
//		}
//	}
//
//
//}

void dataanalysis_0x2E(unsigned char ucdatalength, unsigned char *ucData)
{
	unsigned char ucsid    = ucData[PDU_REQUEST_RESPONSE_MUILT_SID_RSID];
	unsigned int  ucuserid = (ucData[PDU_REQUEST_USERID_0]<<8)|ucData[PDU_REQUEST_USERID_0];
	
	
//	tAPPLDIAGEvaluateRequest();
//	switch(ucuserid)
//	{
//	case APPLDIAGServices0x2E[]: 
//	
//	
//	}
}

void dataanalysis_0x22(unsigned char ucdatalength, unsigned char *ucData)
{
	
}
