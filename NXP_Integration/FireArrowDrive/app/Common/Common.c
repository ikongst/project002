#include "Common.h"


unsigned char gucDebugEnable           = KONGDISABLE;
unsigned char gucDebug_PINEnableStatus = PINSTATUS_LOW;
unsigned int guiDebug_Temperature      = INIT+50+25;// 25 deg-C



unsigned int guiDebug_CurrentLimit              = INIT;
unsigned int guiDebug_CurrentLimitbyVoltage     = INIT;
unsigned int guiDebug_CurrentLimitbyTemperature = INIT;
unsigned int guiDebug_PowerLimit                = INIT;

unsigned  int guiDebug_ErrorVCP                 = INIT;
unsigned  int guiDebug_ErrorOC                  = INIT;
unsigned  int guiDebug_SpeedDeviationCntr       = INIT;
