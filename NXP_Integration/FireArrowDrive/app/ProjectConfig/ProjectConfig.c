#include "ProjectConfig.h"
#include "SystemParam.h"
#include "MotorParam.h"
#include "ElectronicParam.h"
#include "PlatformParam.h"

typeU32 guiInformation_SWIdentifier = SW_SWID_PROJECT;
typeU32 guiInformation_Customer     = PAR_CUSTOMERINDEX_SELECTION;
typeU32 guiInformation_Motor        = PAR_MOTOR_SELECTION;
typeU32 guiInformation_Electronic   = PAR_ELECTRONICS_SELECTION;
typeU32 guiInformation_Project      = PAR_PROJECTS_SELECTION;
typeU32 guiInformation_Interface    = PAR_CUSTOMERINTERFACE_SELECTION;
typeU32 guiInformation_version      = PAR_SW_VERSION;


////#include "tle_variants.h"
//#if defined(TLE9877QXA40)
//	#define SWIDStart       ".ARM.__at_0x1100F00C"
//#elif defined(TLE9879QXA40)
//	#define SWIDStart       ".ARM.__at_0x1101F00C"
//#endif
//const unsigned int p_SWVersionID __attribute__((section(SWIDStart), used)) = (unsigned int)SW_SWID_PROJECT;
const unsigned long sversionid_str @0xFEFF00 = SW_SWID_PROJECT;

// LIN feeddback3
#if SW_SWID_PROJECT == 0x81220184
// SWID: 0x81220184 
// 0x01 -> initial version.

unsigned char gucswversion_internal      = 0x01;

#elif SW_SWID_PROJECT == 0x81330284
// SWID: 0x81330284 
// 0x01 -> initial version.

unsigned char gucswversion_internal      = 0x01;

#elif SW_SWID_PROJECT == 0x41350281
// SWID: 0x41350281 
// 0x01 -> initial version.

unsigned char gucswversion_internal      = 0x01;


#else

unsigned char gucswversion_internal      = 0xFF;

#endif




