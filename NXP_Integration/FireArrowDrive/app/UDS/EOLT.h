#ifndef __EOLT_H__
#define __EOLT_H__


typedef enum
{
	NA_EOLT=0,
	VOLTAGECalib,
	TEMPCalib,
	CURRENTCalib,
	PHASECURTest,
	READFROMROM,
	WRITETOROM,
	KL15Check,
	EOLTMAXID	
}EOLTItems;

typedef struct
{
	EOLTItems ids;
	unsigned char steps;
	union
	{
		unsigned int uiparameters;
		unsigned char ucparameters[4];
	}Paramters;
	
	unsigned int uireturndata;
}EOLTRoutinueStruct;

extern EOLTRoutinueStruct gEOLTRoutinues;
void EOLT_Main(void);


#endif
