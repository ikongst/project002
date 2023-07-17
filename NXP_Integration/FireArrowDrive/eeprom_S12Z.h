/**********************************************************************/
/*                                                                    */
/* Project Name:  flash_S12Z.h                                        */
/* Last modified: 07/30/2015                                          */
/* By:            b34874                                              */
/*                                                                    */
/*                                                                    */
/**********************************************************************/
/*                                                                    */
/* Description: Flash routines for microcontroller S12G               */
/*                                                                    */
/*                                                                    */
/* Documentation: MC9S12ZVLRMV1_Rev1_04.pdf                               */
/*                                                                    */
/*                                                                    */
/* This software is classified as Engineering Sample Software.        */
/*                                                                    */
/**********************************************************************/
/*                                                                    */
/* Services performed by FREESCALE in this matter are performed AS IS */
/* and without any warranty. CUSTOMER retains the final decision      */
/* relative to the total design and functionality of the end product. */ 
/* FREESCALE neither guarantees nor will be held liable by CUSTOMER   */
/* for the success of this project. FREESCALE DISCLAIMS ALL           */
/* WARRANTIES, EXPRESSED, IMPLIED OR STATUTORY INCLUDING, BUT NOT     */
/* LIMITED TO, IMPLIED WARRANTY OF MERCHANTABILITY OR  FITNESS FOR A  */
/* PARTICULAR PURPOSE ON ANY HARDWARE, SOFTWARE ORE ADVISE SUPPLIED   */
/* TO THE PROJECT BY FREESCALE, AND OR NAY PRODUCT RESULTING FROM     */
/* FREESCALE SERVICES . IN NO EVENT SHALL FREESCALE BE LIABLE FOR     */
/* INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT. */
/*                                                                    */
/* CUSTOMER agrees to hold FREESCALE harmless against any and all     */
/* claims demands or actions by anyone on account of any damage, or   */
/* injury, whether commercial, contractual, or tortuous, rising       */
/* directly or indirectly as a result of the advise or assistance     */
/* supplied CUSTOMER in connection with product, services or goods    */
/* supplied under this Agreement.                                     */
/*                                                                    */
/**********************************************************************/

#ifndef _EEPROM_12Z_H
#define _EEPROM_12Z_H

/* Please Select derivative */
#define _S12ZVL      /*for S12ZVL32*/

/* Error codes */
#define OK          0
#define ERASED      1
#define NON_ERASED  2
#define MISALIGNED_ADDRESS  3
#define ACCESS_ERROR        4

extern unsigned char EEPROM_Erase_Verify_Section(unsigned long int address, unsigned int number_of_words);
extern unsigned char EEPROM_Program(unsigned long int address, unsigned int *ptr, unsigned int number_of_words);
extern unsigned char EEPROM_Erase_Sector(unsigned long int address);
extern unsigned char EEPROM_Read_Byte(unsigned long int address);
extern unsigned int EEPROM_Read_Word(unsigned long int address);
extern void EEPROM_Init(unsigned char fdiv);
#endif

