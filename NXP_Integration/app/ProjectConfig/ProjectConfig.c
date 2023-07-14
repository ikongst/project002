#include "ProjectConfig.h"
#include "SystemParam.h"
#include "MotorParam.h"
#include "ElectronicParam.h"
#include "PlatformParam.h"

unsigned int guiInformation_SWIdentifier = SW_SWID_PROJECT;
unsigned int guiInformation_Customer     = PAR_CUSTOMERINDEX_SELECTION;
unsigned int guiInformation_Motor        = PAR_MOTOR_SELECTION;
unsigned int guiInformation_Electronic   = PAR_ELECTRONICS_SELECTION;
unsigned int guiInformation_Project      = PAR_PROJECTS_SELECTION;
unsigned int guiInformation_Interface    = PAR_CUSTOMERINTERFACE_SELECTION;
unsigned int guiInformation_version      = PAR_SW_VERSION;


////#include "tle_variants.h"
//#if defined(TLE9877QXA40)
//	#define SWIDStart       ".ARM.__at_0x1100F00C"
//#elif defined(TLE9879QXA40)
//	#define SWIDStart       ".ARM.__at_0x1101F00C"
//#endif
//const unsigned int p_SWVersionID __attribute__((section(SWIDStart), used)) = (unsigned int)SW_SWID_PROJECT;


// LIN feeddback3
#if SW_SWID_PROJECT == 0x81220184
// SWID: 0x81220184 
// 0x01 -> initial version.

unsigned char gucswversion_internal      = 0x01;

#elif SW_SWID_PROJECT == 0x81330284
// SWID: 0x81330284 
// 0x01 -> initial version.

unsigned char gucswversion_internal      = 0x01;

#else

unsigned char gucswversion_internal      = 0xFF;

#endif




