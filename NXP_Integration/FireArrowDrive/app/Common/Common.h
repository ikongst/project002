#ifndef __COMMON_H__
#define __COMMON_H__

#define KONGTRUE       1
#define KONGFALSE      0

#define INIT    KONGFALSE
#define INITed  KONGTRUE
#define INIT_ulongmax    0xffffffff
#define INIT_uimax       0xffff
#define INIT_ucmax       0xff


#define ERROR   KONGTRUE
#define NOERROR KONGFALSE

#define FLAG_SET    1
#define FLAG_RESET  0

#define PULLDOWN_ENABLE    0
#define PULLDOWN_RELEASE   1

#define PINSTATUS_LOW      0x00
#define PINSTATUS_HIGH     0x01

#define HIGHLOW_LOW        0x00
#define HIGHLOW_HIGH       0x64
#define HIGHLOW_NOERROR    0xFF
#define HIGHLOW_INIT       0xFF // init status, no error

#define INVALIDPWM_NOERROR 0x77
#define INVALIDPWM_ERROR   0xFF

#define NOSIGNAL_int     0xffff
#define NOSIGNAL_char      0xff

#define UNCHAR_MAX         0xff


#define KONGENABLE   1
#define KONGDISABLE  0

// variable length definition
//------------------------------------------------------
typedef unsigned char   typeU08;   /**< unsigned 8 bit definition */
typedef unsigned short  typeU16;   /**< unsigned 16 bit definition */
typedef unsigned long   typeU32;   /**< unsigned 32 bit definition */
typedef signed char     typeS08;   /**< signed 8 bit definition */
typedef signed short    typeS16;   /**< signed 16 bit definition */
typedef signed long     typeS32;   /**< signed 32 bit definition */


//------------------------------------------------------

typedef union
{
	unsigned long Failure;
	struct
	{
		unsigned long OV:1;      // over voltage
		unsigned long UV:1;      // under voltage
		unsigned long OC:1;      // over current
 		unsigned long LC:1;      // limit current
		unsigned long LP:1;      // limit power
		unsigned long OT:1;      // over termpaerature error
 		unsigned long LT:1;      // temperature warning
 		unsigned long OL:1;      // overload
 		unsigned long Blocked:1; // blockage protection
 		unsigned long deratingerror:1; // stoped when derating;
 		
		unsigned long EL_GDU:1;  // electroncis error - GDU error
		unsigned long EL_SC:1;   // electroncis error - short circuit
		unsigned long EL_PB:1;   // electroncis error - phases broken
		unsigned long EL_OC:1;   // electroncis error - over current
		unsigned long EL_POWER:1;// electronics error - power supply and VCP, VS error
		unsigned long EL_Curoffset:1;   // electroncis error - current offset
		
		unsigned long LV:1;      // low voltage flag set
		
	}bits;
}FailureFlagStructure;


typedef enum
{
	IErrNA           = 0u,
	IErrROMRAM       = 1u,
	IErrRESET        = 2u,
	IErrVAREF        = 3u,
	IErrMAX          = 4u
} INTERNALERROR;
	
typedef union
{
	unsigned int Failure;
	struct
	{
		unsigned int ROMRAM:1;      // rom and ram check error		
		unsigned int RESET:1;       // reset unormal
		unsigned int VAREF:1;       // v reference volatge error
		
	}bits;
}InternalDiagnosticStructure;

typedef enum
{
	IDEA           = 0u,
	STARTUP        = 1u,
	NORMAL         = 2u,
	STOP           = 3u,
	DERATING       = 4u,
	EOLT           = 5u,
	Reverse        = 6u
} STATEMACHINE;



typedef enum
{
	B6_NA          = 0u,
	B6_CHARGE      = 1u,
	B6_PHASE_U     = 2u,
	B6_PHASE_V     = 3u,
	B6_PHASE_W     = 4u,
	B6_CALIBRATION = 5u,
	B6_CLOSE       = 6u
} B6PERATIONID;
void b6bridgeoperation(B6PERATIONID operationid, unsigned int uiparamters1);
extern unsigned int guiEOLTCurrentFilteredValue;
void eolcurrentfilter(unsigned int uicurrenttmp, unsigned int uioffsetcurrent);
extern unsigned int guiKL15CheckCntr;

unsigned char getnad(void);

typedef enum {
	TASK_NA                 = 0u,
	TASK_Measurement        = 1u,
	TASK_CustomerInterface  = 2u,
	TASK_Protection         = 3u,
	TASK_DataLog            = 4u,
	TASK_Diagnostic         = 5u,
	TASK_UDS                = 6u,
	TASK_MotorOperation     = 7u,
	TASK_PWMLIN             = 8u,
	TASK_reverse            = 9u,
	TASK_1ms                = 10u,
	TASK_ASAP               = 11u,
	TASK_RAMROM             = 12u,
	TASK_test2              = 13u,
	TASK_test3              = 14u,
	TASK_INT_FOC            = 15u,
	TASK_INT_InputDetect    = 16u,
	TASK_INT_Other          = 17u,
	TASK_MAX                = 18u
}TASKIDs;
extern TASKIDs taskid;
 
void TaskAnalysis_Overflow_INT(void); // 1ms interrupt
void ANALYSIS_TIMERSTART(TASKIDs taskidtemp);
void ANALYSIS_TIMERSTOP(TASKIDs taskidtemp);
void TaskAnalysis_Main(void);

// debug usage,
#define DEBUG_TASKANALYSIS               1
extern unsigned char gucDebugEnable;
extern unsigned char gucDebug_PINEnableStatus;
extern unsigned int guiDebug_Temperature;
extern unsigned int guiDebug_PowerLimit;
extern unsigned int guiDebug_CurrentLimit;
extern unsigned int guiDebug_CurrentLimitbyVoltage;
extern unsigned int guiDebug_CurrentLimitbyTemperature;

extern unsigned  int guiDebug_ErrorVCP;
extern unsigned  int guiDebug_ErrorOC;
extern unsigned  int guiDebug_SpeedDeviationCntr;

#endif
