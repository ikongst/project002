#include "EOLT.h"
#include "Common.h"
#include "UDS.h"


EOLTRoutinueStruct gEOLTRoutinues;

#define DELAY_EOLTPOWERED_10ms          20 // 200ms
static unsigned int suib6poweredflag    = FLAG_RESET;
static unsigned int suib6poweredcounter = INIT;

void currentcalibration(void)
{
		switch(gEOLTRoutinues.steps)
		{
			case 0x00:
				break;
			case 0x01:
				b6bridgeoperation(B6_CALIBRATION, 0);
				
				suib6poweredflag = FLAG_SET;
				break;
			case 0x02:
				b6bridgeoperation(B6_CLOSE, 0);
			
				suib6poweredflag = FLAG_RESET;
				break;
			case 0x03:				
				gEOLTRoutinues.uireturndata = guiEOLTCurrentFilteredValue;
				break;
			default:
				break;
		}
}

void phasecurrenttest(void)
{
	switch(gEOLTRoutinues.steps)
	{
		case 0x00:
			break;
		case 0x01:
			switch(gEOLTRoutinues.Paramters.ucparameters[0])
			{
				case 0x01: // U pahse test
					b6bridgeoperation(B6_PHASE_U, gEOLTRoutinues.Paramters.ucparameters[1]);	
				
				  suib6poweredflag = FLAG_SET;
					break;
				case 0x02:					
					b6bridgeoperation(B6_PHASE_V, gEOLTRoutinues.Paramters.ucparameters[1]);	
				
					suib6poweredflag = FLAG_SET;
					break;
				case 0x03:					
					b6bridgeoperation(B6_PHASE_W, gEOLTRoutinues.Paramters.ucparameters[1]);
				
					suib6poweredflag = FLAG_SET;
					break;
				default:
						// do nothing.
					break;
			}		
			break;
		case 0x02:
			b6bridgeoperation(B6_CLOSE, 0);
		
			suib6poweredflag = FLAG_RESET;
			break;
		case 0x03:			
			gEOLTRoutinues.uireturndata = guiEOLTCurrentFilteredValue;
			break;
		default:
			break;
	}
}

void KL15Test(void)
{
	switch(gEOLTRoutinues.steps)
	{
		case 0x00:
			break;
		case 0x01: // start
			guiKL15CheckCntr = INIT;
			break;
		case 0x02: // stop		
			break;
		case 0x03: // feedback
		  gEOLTRoutinues.uireturndata = guiKL15CheckCntr;
			break;
		default:
			break;
	}	
}

void EOLT_Main(void)
{	
	if(suib6poweredflag == FLAG_SET)
	{
		suib6poweredcounter++;
		if(suib6poweredcounter>DELAY_EOLTPOWERED_10ms)
		{		
			suib6poweredflag = FLAG_RESET;
			
			b6bridgeoperation(B6_CLOSE, 0);
			suib6poweredcounter = INIT;	
		}
	}
	else
	{
		suib6poweredcounter = 0;
	}
	
	switch(gEOLTRoutinues.ids)
	{
		case CURRENTCalib:
			currentcalibration();
			break;
		case PHASECURTest:
			phasecurrenttest();
			break;
		case KL15Check:
			KL15Test();
			break;
		default:
			break;		
	}
	gEOLTRoutinues.ids   = NA_EOLT;
	gEOLTRoutinues.steps = INIT;

}

