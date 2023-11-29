#include "Common_LIB.h"
#include "BSW.h"

unsigned int guiEOLTCurrentFilteredValue  = INIT;
unsigned int suifitercounter = INIT;
unsigned long ulaverageeolcurrent = INIT;


// EOLT
#define FOC_R_SHUNT    0.00050
#define FOC_CSA_HIGH   10
#define DEF_NEWGAIN (5*2/(FOC_R_SHUNT*FOC_CSA_HIGH))
#define DEF_CURRENTCALIBRATION_FACTOR    (4*100*DEF_NEWGAIN)

	unsigned int uitempvalue = INIT;
void eolcurrentfilter(unsigned int uicurrenttmp, signed short uioffsetcurrent)
{
	static unsigned long sulaveargedeolcurrent = INIT;
	
	unsigned int uicurrentcalculated = INIT;
	
	if(uicurrenttmp>uioffsetcurrent)
	{
		uicurrentcalculated = uicurrenttmp-uioffsetcurrent;
	}
	else
	{
		uicurrentcalculated = INIT;
	}
	
	// maximum 3000(150ms / 50us)
	suifitercounter++;		
	if((suifitercounter>1500)&&(suifitercounter<=1756))
	{		
		sulaveargedeolcurrent += uicurrentcalculated;
	}
	else
	{	
		if(suifitercounter>=1756)
		{
			ulaverageeolcurrent         = sulaveargedeolcurrent;
			uitempvalue  = (sulaveargedeolcurrent>>8);	
			
			guiEOLTCurrentFilteredValue = (long)(uitempvalue*(long)DEF_CURRENTCALIBRATION_FACTOR)/32767;
			
			
			sulaveargedeolcurrent = INIT;
			suifitercounter       = INIT;
		}	
	}
}

unsigned int guicurrenttest = INIT;

unsigned int tempvaluearr[6] = {0};

void b6bridgeoperation(B6PERATIONID operationid, unsigned int uiparamters1)
{	
	static unsigned int suitesttimer       = INIT;
  static unsigned int suicurrentaveraged = INIT;
	unsigned int uiValueInput              = INIT;
	unsigned int uii = INIT;	
	
	switch(operationid)
	{
		case B6_PHASE_U:
			//        U       V      W
			//   up   1(%)    0      0
			// down   0       1      1
		  //  CCU62OUT   CCU62  CCU61OUT   CCU61   CCU60OUT   CCU60
			//     1         0       1         0         0         1
			Emo_PWM_test(30,uiparamters1,0,0,0x29); //001						
			suifitercounter = INIT;

			tempvaluearr[0]=PMFVAL0;
			tempvaluearr[1]=PMFVAL1;
			tempvaluearr[2]=PMFVAL2;
			tempvaluearr[3]=PMFVAL3;
			tempvaluearr[4]=PMFVAL4;
			tempvaluearr[5]=PMFVAL5;
			break;
		
		case B6_PHASE_V:
			//        U       V      W
			//   up   0       1(%)   0
			// down   1       0      1
		  //  CCU62OUT   CCU62  CCU61OUT   CCU61   CCU60OUT   CCU60
			//     1         0       0         1         1         0
			Emo_PWM_test(30,0,uiparamters1,0,0x26); //010
			suifitercounter = INIT;

			tempvaluearr[0]=PMFVAL0;
			tempvaluearr[1]=PMFVAL1;
			tempvaluearr[2]=PMFVAL2;
			tempvaluearr[3]=PMFVAL3;
			tempvaluearr[4]=PMFVAL4;
			tempvaluearr[5]=PMFVAL5;
			break;
		
		case B6_PHASE_W:
			//        U       V      W
			//   up   0       0      1(%)  
			// down   1       1      0
		  //  CCU62OUT   CCU62  CCU61OUT   CCU61   CCU60OUT   CCU60
			//     0         1       1         0         1         0
			Emo_PWM_test(30,0,0,uiparamters1,0x1A); //100
			suifitercounter = INIT;

			tempvaluearr[0]=PMFVAL0;
			tempvaluearr[1]=PMFVAL1;
			tempvaluearr[2]=PMFVAL2;
			tempvaluearr[3]=PMFVAL3;
			tempvaluearr[4]=PMFVAL4;
			tempvaluearr[5]=PMFVAL5;
			break;
		
		case B6_CALIBRATION:
			//        U       V      W
			//   up   0       0      0(%)  
			// down   1       1      1
		  //  CCU62OUT   CCU62  CCU61OUT   CCU61   CCU60OUT   CCU60
			//     1         0       1         0         1         0
			Emo_PWM_test(30,0,0,0,0x2A); //000	
			suifitercounter = INIT;
			break;
			
		case B6_CLOSE:
			BDRV_Set_Bridge(Ch_Off, Ch_Off, Ch_Off, Ch_Off, Ch_Off, Ch_Off);
			Set_Bridge_DutyCycle(0, 0, 0);
			break;
		default: 
			break;
	}
}

unsigned int guiKL15CheckCntr = INIT;


unsigned char getnad(void)
{
	return lin_tl_rx_queue.tl_pdu[lin_tl_rx_queue.queue_header][0];//;
}
