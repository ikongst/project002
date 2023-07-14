#ifndef __MEASUREMENT_H__
#define __MEASUREMENT_H__


#define FILTER_DEPTH_DCVOLTAGE              5
#define FILTER_DEPTH_DCCURRENT              3
#define FILTER_DEPTH_TEMPERATURE            3
#define FILTER_DEPTH_SPEED                  3


#define FILTER_DEPTH_CALIBRATION            7


extern unsigned int guiVoltage;
extern unsigned int guiVoltage_Instant;
extern unsigned int guiVoltage_nocalibration;
extern unsigned int guiCurrent;
extern unsigned int guiCurrent_Instant;
extern unsigned int guiCurrent_nocalibration;
extern unsigned int guiTemperature;
extern unsigned int guiTemperature_Instant;
extern unsigned int guiTemperature_nocalibration;

extern unsigned int guiVolatgeDropCompensation_mV;
extern unsigned int guiTemperatureNTC;

extern unsigned int Kcurrent;
extern unsigned int Bcurrent;

extern long lcurrentfilted;
void batterycurrentcalculation(unsigned char ucclearflag);
void Measurement_Main(void);

#endif
