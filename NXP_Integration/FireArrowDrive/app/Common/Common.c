#include "Common.h"


unsigned char gucDebugEnable           = KONGDISABLE;
unsigned char gucDebug_PINEnableStatus = PINSTATUS_LOW;
unsigned int guiDebug_Temperature      = INIT+50+25;// 25 deg-C



typeS32 guiDebug_CurrentLimit              = INIT;
typeS32 guiDebug_CurrentLimitbyVoltage     = INIT;
typeS32 guiDebug_CurrentLimitbyTemperature = INIT;
typeS32 guiDebug_PowerLimit                = INIT;

unsigned  int guiDebug_ErrorVCP                 = INIT;
unsigned  int guiDebug_ErrorOC                  = INIT;
unsigned  int guiDebug_SpeedDeviationCntr       = INIT;
