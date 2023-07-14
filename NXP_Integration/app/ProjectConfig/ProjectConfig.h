#ifndef __PROJECTCONFIG_H__
#define __PROJECTCONFIG_H__

//-------------------------------------------------------------------------------
//-- software specific definition                                              --
//-------------------------------------------------------------------------------
#define PAR_BITS_START_SWMATURITY                      30
#define PAR_BITS_START_CUSTOMERINDEX                   24
#define PAR_BITS_START_MOTORTYPE                       20
#define PAR_BITS_START_ELECTYPE                        16
#define PAR_BITS_START_PROJECTID                        8
#define PAR_BITS_START_INTERFACE                        7
#define PAR_BITS_START_SWVERSION                        0

//- SW maturity - 2 bits, max 4
#define SW_MATURITY_T_A                                 (0<<PAR_BITS_START_SWMATURITY)  // test or A sample.     
#define SW_MATURITY_B                                   (1<<PAR_BITS_START_SWMATURITY)       
#define SW_MATURITY_C                                   (2<<PAR_BITS_START_SWMATURITY)       
#define SW_MATURITY_P                                   (3<<PAR_BITS_START_SWMATURITY)       

//- customer index - 6 bits, maximum 64
#define CUSTOMERINDEX_PLATFORM                          (0<<PAR_BITS_START_CUSTOMERINDEX)
#define CUSTOMERINDEX_GWM                               (1<<PAR_BITS_START_CUSTOMERINDEX)
#define CUSTOMERINDEX_GEELY                             (2<<PAR_BITS_START_CUSTOMERINDEX)
#define CUSTOMERINDEX_GAC                               (3<<PAR_BITS_START_CUSTOMERINDEX)
#define CUSTOMERINDEX_MAX                            (0x3F<<PAR_BITS_START_CUSTOMERINDEX) // maximum

//- Motor index    - 4 bits, maximum 15
#define MOTOR_PLATFORM_GEN1                             (1<<PAR_BITS_START_MOTORTYPE)
#define MOTOR_PLATFORM_400W                             (2<<PAR_BITS_START_MOTORTYPE)
#define MOTOR_PLATFORM_600W                             (3<<PAR_BITS_START_MOTORTYPE)
#define MOTOR_PLATFORM_GENNMAX                       (0x0F<<PAR_BITS_START_MOTORTYPE) // maximum

//- electronic platform index - 4 bits,  maximum 15
#define ELECTRONICS_PLATFORM_GEN1                       (1<<PAR_BITS_START_ELECTYPE)
#define ELECTRONICS_PLATFORM_400W                       (2<<PAR_BITS_START_ELECTYPE)
#define ELECTRONICS_PLATFORM_600W                       (3<<PAR_BITS_START_ELECTYPE)
#define ELECTRONICS_NXP_600W                            (4<<PAR_BITS_START_ELECTYPE)
#define ELECTRONICS_PLATFORM_GENNMAX                 (0x0F<<PAR_BITS_START_ELECTYPE) // maximum


//-----------------------------------------------------------------------------------
// below items should be added by user ----------------------------------------------
//- project variants - 8 bits, maximum 255,
// Platform 
#define PLATFORM_ROCKET                                 (1<<PAR_BITS_START_PROJECTID)
#define PLATFORM_PROJECT_MAX                         (0xFF<<PAR_BITS_START_PROJECTID)

// GWM
#define GWM_H6_400W                                     (1<<PAR_BITS_START_PROJECTID)
#define GWM_H6_600W                                     (2<<PAR_BITS_START_PROJECTID)
#define GWM_PROJECT_MAX                              (0xFF<<PAR_BITS_START_PROJECTID)

// Geely
#define GEELY_SC02_600W                                 (1<<PAR_BITS_START_PROJECTID)
#define GEELY_SS11_600W                                 (2<<PAR_BITS_START_PROJECTID)
#define GEELY_PROJECT_MAX                            (0xFF<<PAR_BITS_START_PROJECTID)

// GAC
#define GAC_A20_400W                                    (1<<PAR_BITS_START_PROJECTID)
#define GAC_A02_400W                                    (2<<PAR_BITS_START_PROJECTID)
#define GAC_PROJECT_MAX                              (0xFF<<PAR_BITS_START_PROJECTID)


//- project sw version - 8 bits, maximum 127, bit-7 means LIN or PWM interface;
//- interface matrix bit 7
#define CUSTOMERINTERFACE_LIN                           (0<<PAR_BITS_START_INTERFACE)
#define CUSTOMERINTERFACE_PWM                           (1<<PAR_BITS_START_INTERFACE)

// sw version bits [6:0]
//#define SWVERSION_000                                   (0<<PAR_BITS_START_SWVERSION)
#define SWVERSION_001                                   (1<<PAR_BITS_START_SWVERSION)
#define SWVERSION_002                                   (2<<PAR_BITS_START_SWVERSION)
#define SWVERSION_003                                   (3<<PAR_BITS_START_SWVERSION)
#define SWVERSION_004                                   (4<<PAR_BITS_START_SWVERSION)
#define SWVERSION_005                                   (5<<PAR_BITS_START_SWVERSION)
#define SWVERSION_006                                   (6<<PAR_BITS_START_SWVERSION)
#define SWVERSION_007                                   (7<<PAR_BITS_START_SWVERSION)
#define SWVERSION_008                                   (8<<PAR_BITS_START_SWVERSION)
#define SWVERSION_009                                   (9<<PAR_BITS_START_SWVERSION)
#define SWVERSION_010                                   (10<<PAR_BITS_START_SWVERSION)
#define SWVERSION_011                                   (11<<PAR_BITS_START_SWVERSION)
#define SWVERSION_012                                   (12<<PAR_BITS_START_SWVERSION)
#define SWVERSION_013                                   (13<<PAR_BITS_START_SWVERSION)
#define SWVERSION_014                                   (14<<PAR_BITS_START_SWVERSION)
#define SWVERSION_015                                   (15<<PAR_BITS_START_SWVERSION)
#define SWVERSION_MAX                                (0x7F<<PAR_BITS_START_SWVERSION)


// Project Coding Definition.
//---------------------------------------------------------------------------
//bits  [ 31,30      29~~~~24,       23~~~~20, 19~16,     15~~~~8,   7,      6~~~~0]
//      [ T/A/B/C  customer index, motor,electronics,   projects,  LIN/PWM, version]
//---------------------------------------------------------------------------
//- project list, as examples.
#define PROJECTCODE_ROCKET_400W_PWM_001           ((SW_MATURITY_T_A)+(CUSTOMERINDEX_PLATFORM)+(MOTOR_PLATFORM_GEN1)+(ELECTRONICS_PLATFORM_GEN1)+(PLATFORM_ROCKET)+(CUSTOMERINTERFACE_PWM)+(SWVERSION_001)) // the highest bit of last byte means interface.
// SWID: 0x00110181
#define PROJECTCODE_GWM_H6_400W_PWM_001           ((SW_MATURITY_T_A)+(CUSTOMERINDEX_GWM)+(MOTOR_PLATFORM_GEN1)+(ELECTRONICS_PLATFORM_GEN1)+(GWM_H6_400W)+(CUSTOMERINTERFACE_PWM)+(SWVERSION_001)) // the highest bit of last byte means interface.
// SWID: 0x01110181
#define PROJECTCODE_GWM_H6_600W_PWM_001           ((SW_MATURITY_T_A)+(CUSTOMERINDEX_GWM)+(MOTOR_PLATFORM_600W)+(ELECTRONICS_PLATFORM_600W)+(GWM_H6_600W)+(CUSTOMERINTERFACE_PWM)+(SWVERSION_001)) // the highest bit of last byte means interface.
// SWID: 0x01110281
#define PROJECTCODE_GEELY_SC02_600W_PWM_001       ((SW_MATURITY_T_A)+(CUSTOMERINDEX_GEELY)+(MOTOR_PLATFORM_600W)+(ELECTRONICS_PLATFORM_600W)+(GEELY_SC02_600W)+(CUSTOMERINTERFACE_PWM)+(SWVERSION_001)) // the highest bit of last byte means interface.
// SWID: 0x02110181
#define PROJECTCODE_GEELY_SS11_600W_PWM_001       ((SW_MATURITY_T_A)+(CUSTOMERINDEX_GEELY)+(MOTOR_PLATFORM_600W)+(ELECTRONICS_PLATFORM_600W)+(GEELY_SS11_600W)+(CUSTOMERINTERFACE_PWM)+(SWVERSION_001)) // the highest bit of last byte means interface.
// SWID: 0x02110281
#define PROJECTCODE_GAC_A20_400W_PWM_001          ((SW_MATURITY_T_A)+(CUSTOMERINDEX_GAC)+(MOTOR_PLATFORM_GEN1)+(ELECTRONICS_PLATFORM_GEN1)+(GAC_A20_400W)+(CUSTOMERINTERFACE_PWM)+(SWVERSION_001)) // the highest bit of last byte means interface.
// SWID: 0x03110181
#define PROJECTCODE_GAC_A02_400W_LIN_001          ((SW_MATURITY_T_A)+(CUSTOMERINDEX_GAC)+(MOTOR_PLATFORM_GEN1)+(ELECTRONICS_PLATFORM_GEN1)+(GAC_A02_400W)+(CUSTOMERINTERFACE_LIN)+(SWVERSION_001)) // the highest bit of last byte means interface.
// SWID: 0x03110201

/********************************************************************
// Project:     GWM B30 600W
// Time:        2023-06-25
// Description: PV sample, use the PV sample for this SW release.
// SW ID:       0x41340281  
*********************************************************************/
#define PROJECTCODE_GWM_H6_600W_PWM_NXP           ((SW_MATURITY_B)+(CUSTOMERINDEX_GWM)+(MOTOR_PLATFORM_600W)+(ELECTRONICS_NXP_600W)+(GWM_H6_600W)+(CUSTOMERINTERFACE_PWM)+(SWVERSION_001)) // the highest bit of last byte means interface.
/********************************************************************/






//- Project Selection
#define SW_VARIANT_PROJECT_SELECTION         PROJECTCODE_GWM_H6_600W_PWM_NXP







//------------------------------------------------------------------------------------
// below can not be modified.
//------------------------------------------------------------------------------------
#define getSWMaturity()                      (SW_VARIANT_PROJECT_SELECTION&0xC0000000)
#define getCustomerIndex()                   (SW_VARIANT_PROJECT_SELECTION&0x3f000000)
#define getMotorType()                       (SW_VARIANT_PROJECT_SELECTION&0x00f00000)
#define getElecType()                        (SW_VARIANT_PROJECT_SELECTION&0x000f0000)
#define getProjectID()                       (SW_VARIANT_PROJECT_SELECTION&0x0000ff00)
#define getInterfaceType()                   (SW_VARIANT_PROJECT_SELECTION&0x00000080)
#define getSWVersion()                       (SW_VARIANT_PROJECT_SELECTION&0x0000007f)

////- get project definition
#define PAR_SWMATURITY_SELECTION             getSWMaturity()
#define PAR_CUSTOMERINDEX_SELECTION          getCustomerIndex()
#define PAR_MOTOR_SELECTION                  getMotorType()
#define PAR_ELECTRONICS_SELECTION            getElecType()
#define PAR_PROJECTS_SELECTION               getProjectID()
#define PAR_CUSTOMERINTERFACE_SELECTION      getInterfaceType()
#define PAR_SW_VERSION                       getSWVersion()

#define SW_SWID_PROJECT                      SW_VARIANT_PROJECT_SELECTION
#define SWVersionDataLength                  (4)
//-------------------------------------------------------------------------------

#if PAR_CUSTOMERINTERFACE_SELECTION==CUSTOMERINTERFACE_LIN
	#if PAR_CUSTOMERINDEX_SELECTION == CUSTOMERINDEX_GAC
		#define LIN_PROTOCOL_SELECTION     CUSTOMERINDEX_GAC
	#else
		#warning with no LIN protocol selected!!!
	#endif
#else
	#define LIN_PROTOCOL_SELECTION     CUSTOMERINDEX_PLATFORM
#endif

extern unsigned int guiInformation_SWIdentifier;

extern unsigned char gucswversion_internal;

#endif

