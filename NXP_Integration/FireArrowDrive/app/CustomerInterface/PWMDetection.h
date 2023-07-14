#ifndef __PWMDETECTION_H__
#define __PWMDETECTION_H__

extern unsigned int guiPWMDetection_Duty;
extern unsigned int guiPWMDetection_Freq;
extern unsigned char gucPWMDetection_TriggerFlag;

void PWMDetection_Init(void);
void PWMDetection_Main(void);
void PWMDetection_INT(void);
void PWM_overflow_INT(void);

#endif

