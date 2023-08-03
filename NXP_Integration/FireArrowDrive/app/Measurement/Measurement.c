#include "Measurement.h"
#include "Common.h"
#include "CustomerInterface.h"
#include "BSW.h"
#include "DataLog.h"
#include "NTC.h"

unsigned int guiVoltage;
unsigned int guiVoltage_Instant;
unsigned int guiVoltage_nocalibration;
unsigned int guiCurrent;
unsigned int guiCurrent_Instant;
unsigned int guiCurrent_nocalibration;
unsigned int guiTemperature;
unsigned int guiTemperature_Instant;
unsigned int guiTemperature_nocalibration;

unsigned int guiTemperatureNTC;

unsigned int Kvoltage =INIT;
unsigned int Bvoltage =INIT;

unsigned int Kcurrent =INIT;
unsigned int Bcurrent =INIT;

unsigned int Ktemp    =INIT;
unsigned int Btemp    =INIT;

static unsigned char datapointarr[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

static unsigned char onlyupdateonetimeflag = INIT;
void calibrationudpate()
{
	if(onlyupdateonetimeflag==INIT)
	{
		onlyupdateonetimeflag = INITed;
		
		getdatafromflash_1(datapointarr, FLASH_ADDRESS_CALCULATION_START/16, SW_READ_ARR_LENGTH);
		
		if((datapointarr[10]==0x55)&&((datapointarr[0]<0x9F)&&(datapointarr[0]>0x5F)))
		{
			Kvoltage = datapointarr[0]; // 127->1, 126/127, 128/127
			Bvoltage = datapointarr[1]; // 127->0, 126->-1*128, 128->+1*128
		}
		else
		{			
			// no valid calibration value
			//-----------------------------------------
			Kvoltage =(1<<FILTER_DEPTH_CALIBRATION); 
			Bvoltage =127;
		}
		
		if((datapointarr[12]==0x55)&&((datapointarr[2]<0x9F)&&(datapointarr[2]>0x5F)))
		{
			Kcurrent = datapointarr[2]; // 127->1, 126/127, 128/127
			Bcurrent = datapointarr[3]; // 127->0, 126->-1*128, 128->+1*128
		}
		else
		{			
//			// no valid calibration value
//			//-----------------------------------------
//			Kcurrent =(1<<FILTER_DEPTH_CALIBRATION);
//			Bcurrent =127;
			
			// default kb value. based on sample status.
#if PAR_ELECTRONICS_SELECTION == ELECTRONICS_PLATFORM_400W
			Kcurrent = 0x70;
			Bcurrent = 0x85;
#elif PAR_ELECTRONICS_SELECTION == ELECTRONICS_PLATFORM_600W
			Kcurrent = 0x71;
			Bcurrent = 0x86;
#endif	
		}	

		if((datapointarr[14]==0x55)&&((datapointarr[5]<0x85)&&(datapointarr[5]>0x79)))
		{
			Ktemp    = datapointarr[4]; // 127->1, 126/127, 128/127
			Btemp    = datapointarr[5]; // 127->0, 126->-1, 128->+1
		}
		else
		{			
			// no valid calibration value
			//-----------------------------------------
			Ktemp    =(1<<FILTER_DEPTH_CALIBRATION);
			Btemp    = 127;
		}	
	}
}

//static signed int suicompensationcurrent     = INIT;
//static signed int suicompensationtemperature = INIT;


unsigned int guiVolatgeDropCompensation_mV    = INIT;
void compensationupdate(void)
{
	unsigned int uitempmV = INIT;
	
	// voltage drop at connector.
	uitempmV = VOLTAGE_DROP_RESISTORS_0_1_mOhm*guiCurrent/10000;
	if(uitempmV>700)
	{
		uitempmV = 700;
	}	
	
	// voltage drop at diodo.
	uitempmV += VOLTAGE_DIODO_COMSUMPTION_mV;
	
	
	guiVolatgeDropCompensation_mV = uitempmV;	
}

static long aveargedcvoltage       = INIT;
static long aveargedccurrent       = INIT;
static long aveargetemperature     = INIT;
static long aveargetemperatureNTC  = INIT;
static long aveargespeedactual     = INIT;

static unsigned char initflagofdatafilter  = INIT;
signed long sitempvalue = INIT;
void Data_filter()
{

	// questent value from motor drive.
	long newdcvoltage	     = getrawvoltage();
	long newdccurrent	     = getrawcurrent();
	long newtemperature    = getrawtemperature();
	long newtemperatureNTC = getNTCDigitals();
	long newspeedactual    = getactualspeed();
	
	long tempvalue		= INIT;

	guiVoltage_Instant = newdcvoltage;
	guiCurrent_Instant = newdccurrent;
	guiTemperature_Instant = newtemperature;	
	
	calibrationudpate();
	compensationupdate();
	
	if(initflagofdatafilter==INIT)
	{	
		initflagofdatafilter = INITed;
		
		aveargedcvoltage	    = newdcvoltage<<FILTER_DEPTH_DCVOLTAGE;
		aveargedccurrent	    = newdccurrent<<FILTER_DEPTH_DCCURRENT;
		aveargetemperature	  = newtemperature<<FILTER_DEPTH_TEMPERATURE;
		aveargetemperatureNTC	= newtemperatureNTC<<FILTER_DEPTH_TEMPERATURE;
		aveargespeedactual	  = newspeedactual<<FILTER_DEPTH_SPEED;
		
	}
	else
	{
		aveargedcvoltage   -= (aveargedcvoltage>>FILTER_DEPTH_DCVOLTAGE);
		aveargedcvoltage   += (newdcvoltage);
		
		aveargedccurrent   -= (aveargedccurrent>>FILTER_DEPTH_DCCURRENT);
		aveargedccurrent   += (newdccurrent);	
				
		aveargetemperature -= (aveargetemperature>>FILTER_DEPTH_TEMPERATURE);
		aveargetemperature += (newtemperature);
		
		aveargetemperatureNTC -= (aveargetemperatureNTC>>FILTER_DEPTH_TEMPERATURE);
		aveargetemperatureNTC += (newtemperatureNTC);
		
		aveargespeedactual -= (aveargespeedactual>>FILTER_DEPTH_SPEED);
		aveargespeedactual += (newspeedactual);
	}		
	
	tempvalue			     = aveargedcvoltage>>FILTER_DEPTH_DCVOLTAGE;
	tempvalue         += guiVolatgeDropCompensation_mV;
	sitempvalue = ((Kvoltage * tempvalue )>>FILTER_DEPTH_CALIBRATION)+ ((((signed int)(Bvoltage-127))*1000)>>FILTER_DEPTH_CALIBRATION);
	if(sitempvalue<INIT)
	{
		sitempvalue = INIT;
	}
	guiVoltage	             = sitempvalue;
	guiVoltage_nocalibration = tempvalue;
	
	tempvalue	  = aveargedccurrent>>FILTER_DEPTH_DCCURRENT;

	//sitempvalue = ((Kcurrent * tempvalue )>>FILTER_DEPTH_CALIBRATION)+ ((signed int)(Bcurrent-127)>>FILTER_DEPTH_CALIBRATION);
	sitempvalue = ((128 * tempvalue )>>FILTER_DEPTH_CALIBRATION)+ ((signed int)(127-127)>>FILTER_DEPTH_CALIBRATION);
	if(sitempvalue<INIT)
	{
		sitempvalue = INIT;
	}
	guiCurrent	             = sitempvalue;
	guiCurrent_nocalibration = tempvalue;	

	tempvalue			  = aveargetemperature>>FILTER_DEPTH_TEMPERATURE;	
	guiTemperature               = tempvalue+(Btemp-127); //Ktemp not used, temp. value use delta.
	guiTemperature_nocalibration = tempvalue;
		
	tempvalue         = aveargetemperatureNTC>>FILTER_DEPTH_TEMPERATURE;
    guiTemperatureNTC = tempvalue;	
	
	tempvalue			 = aveargespeedactual>>FILTER_DEPTH_SPEED; 
	guiActualSpeed = tempvalue;

}

//#include "Emo_RAM.h"
//long lcurrentsum    = 0;
//long lcurrenttemp   = 0;
//long lcurrentfilted = 0;  
//#define FILTER_DEPTH_DCCURRENT_BIG    10
//unsigned int uiDeadtime_compensation = FOC_SVMDEAD/2;
//unsigned int uiDeadtime_minimumduty  = FOC_SVMDEAD/2;
//
//void batterycurrentcalculation(unsigned char ucclearflag)
//{	
//	sint16 Acur = abs(Emo_Svm.t1curarr[1]);
//	sint16 Bcur = abs(Emo_Svm.t2curarr[1]);	
//	sint16 AT   = Emo_Svm.t1timearr[1];	
//	sint16 BT   = Emo_Svm.t2timearr[1];	
//	
//	if((Emo_Svm.t1curarr[1]<0)
//		||(Emo_Svm.t2curarr[1]<0)
//		||(AT<uiDeadtime_compensation)
//		||(BT<uiDeadtime_compensation))
//	{
//		Acur = 0;
//		Bcur = 0;
//		AT   = 0;
//		BT   = 0;
//	}
//	
////	if(AT>=uiDeadtime_compensation)
////	{
////		AT -= uiDeadtime_compensation;
////	}
////	
////	if(BT>=uiDeadtime_compensation)
////	{
////		BT -= uiDeadtime_compensation;
////	}
//	
//	if(ucclearflag==1)
//	{
//		lcurrentsum    = 0;
//		lcurrenttemp   = 0;
//		lcurrentfilted = 0;
//		return;
//	}	
//	
//	lcurrenttemp   = (Acur*AT+Bcur*BT)/CCU6_T12PERIOD;
//	lcurrentsum   -= (lcurrentsum>>FILTER_DEPTH_DCCURRENT_BIG);
//	lcurrentsum   += (lcurrenttemp);	
//		
//	lcurrentfilted = (lcurrentsum)>>FILTER_DEPTH_DCCURRENT_BIG;
//}


void Measurement_Main(void)
{
	Data_filter();

}
