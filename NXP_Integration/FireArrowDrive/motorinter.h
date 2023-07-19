#ifndef __INTERFACE_MOTORDRIVE_H__
#define __INTERFACE_MOTORDRIVE_H__

#include "motor_structure.h"
#include "state_machine.h"


 void MotorDrive_Start(void);
 void MotorDrive_Stop(void);
 void MotorDrive_Regulation(unsigned int uispeedvalue,unsigned char direct);

extern unsigned char Runcommand,directemp;           //Command state: 1=run  0=stop; direct state:0=prev  1=invt;
extern signed int  SpeedIN;                        //speed value input

extern unsigned int MotorDrive_uiVoltage;            //bus voltage measure
extern unsigned char MotorDrive_uiCurrent;           //bus current (raw)
extern signed int MotorDrive_uiTemperature;        //MCU temperature
extern signed int MotorDrive_uiTemperatureNTC_Digital;     //PCB temperature

extern unsigned int MotorDrive_uiTargetSpeed;        //required speed output
extern unsigned int MotorDrive_uiActualSpeed;        //actual speed output

extern unsigned int MotorDrive_MotorStatus;          //running state of motor

//extern driveStates_t *Addr_State;         //handler of state
//extern pmsmDrive_t *Addr_Foc;             //handler of control

#endif


