#include "Common.h"
#include "InternalDiagnostic.h"

#include "BSW.h"
InternalDiagnosticStructure gInternalDiagnosticFlags;

static unsigned char sucramromcheckedflag = INIT;
void romramcheck(void)
{		
//	static unsigned int suidelaycounter    = INIT;
//	static unsigned int suinoerrorcounter  = INIT;
//	static unsigned int suiramerrorcounter = INIT;
//	static unsigned int suiromerrorcounter = INIT;
//	unsigned char ucROMError = INIT;
//	unsigned char ucRAMError = INIT;
//	
//	if(sucramromcheckedflag== INIT)
//	{	
//		suidelaycounter++;
//		if(suidelaycounter<100)
//		{
//			return;		
//		}
//		suidelaycounter = INIT;
//	
//
//		// ram and rom check based on uC hardware.
//		ucROMError = BSW_GetRomCheckError();	
//		if(ucROMError != INIT)
//		{
//			suiramerrorcounter++;
//			if(suiromerrorcounter>=3)
//			{
//				suiromerrorcounter = INIT;
//			  gInternalDiagnosticFlags.bits.ROMRAM = FLAG_SET;
//				
//				sucramromcheckedflag = INITed;
//			}		
//			
//			return;
//		}
//		
//		ucRAMError = BSW_GetRamCheckError();
//		if (ucRAMError == 1u)
//		{
//			gInternalDiagnosticFlags.bits.ROMRAM = FLAG_SET;
//			sucramromcheckedflag = INITed;
//			
//			return;
//		}
//		
//		// no error delay
//		suinoerrorcounter++;
//		if(suinoerrorcounter>10)// 10 sec check time
//		{
//			suinoerrorcounter = 0;
//			gInternalDiagnosticFlags.bits.ROMRAM = FLAG_RESET;
//			
//			sucramromcheckedflag = INITed;
//		}			
//	}
}

unsigned char gucResetResourceRecording = INIT;

static unsigned char sucpoweronflag_pmureset = FLAG_RESET;
void resetsourcecheck(void)
{
//	uint8 sts;	
//	
//	if(sucpoweronflag_pmureset==FLAG_RESET)
//	{	
//		sucpoweronflag_pmureset = FLAG_SET;
//		sts = BSW_GetResetStatus();		
//		
//		gucResetResourceRecording = sts;
//		
//		if (sts & BSW_SYSTEMRESET_STA_FAILED_MASK)
//		{
//			gInternalDiagnosticFlags.bits.RESET = FLAG_SET;
//		}		
//	}
}


#include "DataLog.h"
void InternalDiagnostic_Main(void)
{	
	unsigned char ucinternallerrorarr[16] = {0};	
	
	romramcheck();
	resetsourcecheck();
}
