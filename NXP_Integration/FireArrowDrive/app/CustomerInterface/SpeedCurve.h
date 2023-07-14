#ifndef __SPEEDCURVE_H__
#define __SPEEDCURVE_H__

#include "CustomerInterface.h"

#define PAR_SYSTEM_SPEED_MAX_RPM           SYSTEMPARAM_SPEED_MAX_rpm  // rpm
#define PAR_SYSTEM_SPEED_NOMINAL_RPM       SYSTEMPARAM_SPEED_RATE_rpm // rpm
#define PAR_SYSTEM_SPEED_MIN_RPM           SYSTEMPARAM_SPEED_MIN_rpm  // rpm

#define PAR_SYSTEM_PWMDUTY_INDEX_MIN       SYSTEMPARAM_SPEEDCURVE_MAX_dig // 8/128
#define PAR_SYSTEM_PWMDUTY_INDEX_MAX       SYSTEMPARAM_SPEEDCURVE_MIN_dig // 112/128


#define SPEEDCURVETABLE_TYPE_DEFAULT        DEF_INTERFACE_DEFAULT // internal table, LIN
#define SPEEDCURVETABLE_TYPE_CUSTOMER       SYSTEMPARAM_INTERFACE // customer table, PWM or LIN

#define SPEEDCURVETABLE_LENGTH              128
#define SPEEDCURVETABLE_MAXID               127
#define SPEEDCURVETABLE_MINID                 0

extern const unsigned int SPEEDCURVETABLE_CUSTOMER[SPEEDCURVETABLE_LENGTH];
unsigned int GetSpeedByDigital(unsigned char speeddigital, unsigned char uctableselect);




#endif

