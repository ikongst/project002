#ifndef __MOTOROPERATION_H__
#define __MOTOROPERATION_H__

#include "SystemParam.h"
#include "PlatformParam.h"

// definition of the speed parameters 
#define LIMIT_SPEED_MIN_rpm       SYSTEMPARAM_SPEED_MIN_rpm
#define LIMIT_SPEED_MAX_rpm       SYSTEMPARAM_SPEED_MAX_rpm

#define DELAY_AT_IDEAMODE_10ms              100
#define DELAY_AT_STOPMODE_SHORT_10ms         10 // delay at lower temp.
#define DELAY_AT_STOPMODE_MIDD_10ms        1500-200 // dealy 15 sec at midd temp. 2sec waiting time, 
#define DELAY_AT_STOPMODE_HIGHLONG_10ms    3000-200 // dealy 30 sec at higher temp. 2sec waiting time, 
#define DELAY_AT_ELECTRONICSERROR_10ms      200
#define DELAY_FILTER_BLOCKAGECHECK_10ms    PLATFORM_DELAY_BLOCKAGECHECK_10ms

#include "Common.h"
extern STATEMACHINE gMotorControl;
extern unsigned int guiSpeedSet;
extern unsigned char gucMotorDriveState;
extern unsigned char gucMotorDriveStartupTime;
void MotorOperation_Main(void);


#endif

