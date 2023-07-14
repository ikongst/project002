#include "BSW.h"
#include "Common.h"


TASKIDs taskid;
unsigned char gucTaskCheckedFlag[TASK_MAX];
unsigned long gulTaskTimersStart[TASK_MAX];
unsigned long gulTaskTimersStop[TASK_MAX];
unsigned long gulTaskExecution_us[TASK_MAX];
unsigned long gulTaskExecutionMax_us[TASK_MAX];

static unsigned int gucAnalysisTimerOverflowFlagCounter = INIT;
static unsigned int guiSystemTicketCounter_65536us       = INIT;

unsigned long ultotallyexecutiontimer = INIT;
unsigned long ultotallyexecutionload = INIT;

#if DEBUG_TASKANALYSIS ==1
void ANALYSIS_TIMERSTART(TASKIDs taskidtemp)
{
	gucTaskCheckedFlag[taskidtemp]    = FLAG_RESET;
	gulTaskTimersStart[taskidtemp]    = TASKANALYSIS_GETTIMER_CNTR()+0xFFFF*gucAnalysisTimerOverflowFlagCounter;
}

void ANALYSIS_TIMERSTOP(TASKIDs taskidtemp)
{
	gulTaskTimersStop[taskidtemp]     = TASKANALYSIS_GETTIMER_CNTR()+0xFFFF*gucAnalysisTimerOverflowFlagCounter;	
	gucTaskCheckedFlag[taskidtemp]    = FLAG_SET;
}

void TaskAnalysis_Overflow_INT(void)
{
	gucAnalysisTimerOverflowFlagCounter++;
	guiSystemTicketCounter_65536us++;
}

void TaskAnalysis_Main(void)
{
	unsigned char sucperiodreachflag = INIT;
	static unsigned char suctaskids =INIT;
	unsigned long ultimertemp =  0;
	
	unsigned char uci = INIT;
	
	if(guiSystemTicketCounter_65536us>305)
	{
		guiSystemTicketCounter_65536us = INIT;
		sucperiodreachflag             = FLAG_SET;
		
		ultotallyexecutionload         = ultotallyexecutiontimer/20000000;// 20s period.
		ultotallyexecutiontimer        = INIT;
		
		gucAnalysisTimerOverflowFlagCounter = INIT;
	}
	
	for(uci=INIT; uci<TASK_MAX; uci++)
	{
		if(sucperiodreachflag==FLAG_SET)
		{
			gulTaskExecutionMax_us[uci] = INIT;
		}			
		
		if(gucTaskCheckedFlag[uci]==FLAG_SET)
		{
			gucTaskCheckedFlag[uci] = FLAG_RESET;			
			
			ultimertemp = gulTaskTimersStop[uci] - gulTaskTimersStart[uci]; // system ticket decreasing			
			ultimertemp = ultimertemp; //1 dig = 1 uS
			
			gulTaskExecution_us[uci] = ultimertemp;		
				
			if(ultimertemp>gulTaskExecutionMax_us[uci])
			{
				gulTaskExecutionMax_us[uci] = ultimertemp;
			}			
			
			ultotallyexecutiontimer += gulTaskExecution_us[uci];			
		}		
	}	
	sucperiodreachflag = FLAG_RESET;
}
#else
	void ANALYSIS_TIMERSTART(TASKIDs taskidtemp) 
	{
		
	}
	void ANALYSIS_TIMERSTOP(TASKIDs taskidtemp)
	{
		
	}
	void TaskAnalysis_Main(void)  
	{
		
	}
#endif
