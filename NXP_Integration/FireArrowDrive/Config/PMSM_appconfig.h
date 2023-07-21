/**********************************************************************/
// File Name: {FM_project_loc}/PMSM_appconfig.h 
//
// Date:  18. April, 2023
//
// Automatically generated file by MCAT
// - static configuration of the PMSM FOC application
/**********************************************************************/

#ifndef __PMSM_APPCONFIG_H
#define __PMSM_APPCONFIG_H


//Motor Parameters                      
//----------------------------------------------------------------------
//Pole-pair number                      = 6 [-]
//Stator resistance                     = 0.01 [Ohms]
//Direct axis inductance                = 0.0000325 [H]
//Quadrature axis inductance            = 0.0000325 [H]
//Back-EMF constant                     = 0.0027136 [V.sec/rad]
//Drive inertia                         = 0.5e-4 [kg.m2]
//Nominal current                       = 50 [A]
//Nominal speed                         = 2500 [rpm]

#define MOTOR_PP_GAIN                   FRAC16(0.75)
#define MOTOR_PP_SHIFT                  (3)

//Application scales                    
//----------------------------------------------------------------------
#define I_MAX                           (120.0F)
#define U_DCB_MAX                       (25.0F)
#define N_MAX                           (3000.0F)
#define WEL_MAX                         (1884.96F)
#define E_MAX                           (14.4F)

//Application Fault Triggers            
//----------------------------------------------------------------------
#define U_DCB_TRIP                      FRAC16(0.6400000000)
#define U_DCB_UNDERVOLTAGE              FRAC16(0.3200000000)
#define U_DCB_OVERVOLTAGE               FRAC16(0.6800000000)
#define I_PH_OVER                       FRAC16(0.8333333333)
#define TEMP_OVER                       FRAC16(0.1704897706)

//DC Bus voltage IIR1 filter constants  
//----------------------------------------------------------------------
//Cut-off frequency                     = 100 [Hz]
//Sample time                           = 0.0001 [sec]
//----------------------------------------------------------------------
#define UDCB_IIR_B0                     FRAC16(0.0038073785)
#define UDCB_IIR_B1                     FRAC16(0.0038073785)
#define UDCB_IIR_A1                     FRAC16(-0.1173852430)
//Mechanical Alignment                  
#define ALIGN_VOLTAGE                   FRAC16(0.1500000000)
#define ALIGN_DURATION                  (20000)

//Current Loop Control                  
//----------------------------------------------------------------------
//Loop Bandwidth                        = 150 [Hz]
//Loop Attenuation                      = 1.1 [-]
//Loop sample time                      = 0.0001 [sec]
//----------------------------------------------------------------------
//Current Controller Output Limit       
#define CLOOP_LIMIT                     FRAC16(0.8000000000)
//D-axis Controller - Recurrent type    
#define D_NSHIFT                        (0)
#define D_CC1SC                         FRAC16(0.2823868419)
#define D_CC2SC                         FRAC16(-0.2685299173)
//Q-axis Controller - Recurrent type    
#define Q_NSHIFT                        (0)
#define Q_CC1SC                         FRAC16(0.2823868419)
#define Q_CC2SC                         FRAC16(-0.2685299173)

//Speed Loop Control                    
//----------------------------------------------------------------------
//Loop Bandwidth                        = 1 [Hz]
//Loop Attenuation                      = 0.8 [-]
//Loop sample time                      = 0.001 [sec]
//----------------------------------------------------------------------
//Speed Controller - Parallel type      
#define SPEED_PI_PROP_GAIN              FRAC16(0.6842013450)
#define SPEED_PI_PROP_SHIFT             (1)
#define SPEED_PI_INTEG_GAIN             FRAC16(0.6878342141)
#define SPEED_PI_INTEG_SHIFT            (-8)
#define SPEED_LOOP_HIGH_LIMIT           FRAC16(0.8333333333)
#define SPEED_LOOP_LOW_LIMIT            FRAC16(-0.8333333333)

#define SPEED_RAMP_UP                   FRAC32(0.000083)  //0.000083
#define SPEED_RAMP_DOWN                 FRAC32(0.000033)  //0.000033

#define SPEED_LOOP_CNTR                 (10)

#define POSPE_SPEED_FILTER_MA_NPOINT    (4)

//Sensorless DQ BEMF Observer and Tracking Observer
//----------------------------------------------------------------------
//Loop Bandwidth                        = 200 [Hz]
//Loop Attenuation                      = 1 [-]
//Loop sample time                      = 0.0001 [sec]
//----------------------------------------------------------------------
//DQ Bemf - plant coefficients          
#define I_GAIN                          FRAC16(0.9696969697)
#define U_GAIN                          FRAC16(0.3156565657)
#define E_GAIN                          FRAC16(0.1818181818)
#define WI_GAIN                         FRAC16(0.0928197829)
#define BEMF_SHIFT                      (0)

//DQ Bemf - PI controller parameters    
#define BEMF_DQ_CC1_GAIN                FRAC16(0.6187292178)
#define BEMF_DQ_CC2_GAIN                FRAC16(-0.5759609321)
#define BEMF_DQ_NSHIFT                  (0)

//Tracking Observer - PI controller parameters
#define TO_CC1SC                        FRAC16(0.2677755959)
#define TO_CC2SC                        FRAC16(-0.2662951552)
#define TO_NSHIFT                       (0)
//Tracking Observer - Integrator        
#define TO_THETA_GAIN                   FRAC16(0.0300000000)
#define TO_THETA_SHIFT                  (0)

//Observer speed output filter          

//Open loop start-up                    
#define OL_START_RAMP_INC               FRAC32(0.000025)
#define OL_START_I                      FRAC16(0.1250000000)
#define MERG_SPEED_1_TRH                FRAC16(0.0266666667)
#define MERG_SPEED_2_TRH                FRAC16(0.0500000000)

//Control Structure Module - Scalar Control
//----------------------------------------------------------------------
#define SCALAR_VHZ_FACTOR_GAIN          FRAC16(0.7140000000)
#define SCALAR_VHZ_FACTOR_SHIFT         (0)
#define SCALAR_INTEG_GAIN               FRAC16(0.03)
#define SCALAR_INTEG_SHIFT              (0)
#define SCALAR_RAMP_UP                  FRAC16(0.0000100000)
#define SCALAR_RAMP_DOWN                FRAC16(0.0000100000)

//FreeMASTER Scale Variables            
//----------------------------------------------------------------------
//Note: Scaled at input = 1000          
//----------------------------------------------------------------------
#define FM_I_SCALE                      (120000)
#define FM_U_SCALE                      (20000)
#define FM_U_DCB_SCALE                  (25000)
#define FM_SPEED_RAD_EL_SCALE           (1884956)
#define FM_SPEED_RPM_MEC_SCALE          (3000000)
#define FM_POSITION_DEG_SCALE           (180000)

#endif

//End of generated file                 
/**********************************************************************/
