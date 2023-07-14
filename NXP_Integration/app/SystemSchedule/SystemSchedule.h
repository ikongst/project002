#ifndef __SYSTEMSCHEDULE_H__
#define __SYSTEMSCHEDULE_H__

#include "Common.h"

// this funtion should be implement at 1ms ISR.
void SetFlag_1MS(void);

// call this funtion to implement all the tasks of CoolFan system.
void SystemSchedule_Init(void);
void SystemSchedule_Main(void);

#endif
