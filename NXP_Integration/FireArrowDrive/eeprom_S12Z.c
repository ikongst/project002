/**********************************************************************/
/* Project Name:  flash_S12Z.c                                        */
/* Last modified: 07/30/2015                                          */
/* By:            b34874                                              */
/**********************************************************************/
/* Description: Flash routines for microcontroller S12Z               */
/* This software is classified as Engineering Sample Software.        */
/**********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "eeprom_S12Z.h"
#include "derivative.h"      /* derivative-specific definitions */


//==============================================================================
//EEPROM_Erase_Verify_Section
//==============================================================================
unsigned char EEPROM_Erase_Verify_Section(unsigned long int address, unsigned int number_of_words)
{
  //check if address is aligned (global address [2:0] = 000)
  if((address & 0x00000001) != 0)
    return MISALIGNED_ADDRESS; 
  
  while(FSTAT_CCIF == 0){};   //wait if command in progress
  FSTAT = 0x30;             //clear ACCERR and PVIOL
  
  FCCOBIX = 0x02;    //we will write command up to FCCOB2
  FCCOB0HI = 0x10;
  FCCOB0LO = ((address & 0x00FF0000)>>16);
  
  FCCOB1 = (address & 0x0000FFFF);
  
  FCCOB2 = number_of_words;
  
  FSTAT_CCIF = 1;         //launch command
  while(FSTAT_CCIF == 0){}; //wait for done
  
  if((FSTAT & (FSTAT_ACCERR_MASK | FSTAT_FPVIOL_MASK)) != 0)
    return ACCESS_ERROR;
  
  //check if phrases are erased and return result
  if(FSTAT_MGSTAT != 0)
    return NON_ERASED;
  else
    return ERASED;
}


//==============================================================================
//EEPROM_Program
//==============================================================================
unsigned char EEPROM_Program(unsigned long int address, unsigned int *ptr, unsigned int number_of_words)
{
  unsigned char i;
  
  //check if address is aligned (global address [2:0] != 000)
  if((address & 0x00000001) != 0)
    return MISALIGNED_ADDRESS; 
  
  //check if the phrase is erased    
  if((EEPROM_Erase_Verify_Section(address, 1)) == NON_ERASED)
    return NON_ERASED;  
    
  while(FSTAT_CCIF == 0){};   //wait if command in progress
  FSTAT = 0x30;             //clear ACCERR and PVIOL    
  
  FCCOBIX = number_of_words + 1;    //how many words we will write
  FCCOB0HI = 0x11;
  FCCOB0LO = ((address & 0x00FF0000)>>16);
  
  FCCOB1 = (address & 0x0000FFFF);
  
  FCCOB2 = ptr[0];
  if (number_of_words>1) FCCOB3 = ptr[1];
  if (number_of_words>2) FCCOB4 = ptr[2];
  if (number_of_words>3) FCCOB5 = ptr[3];
       
  FSTAT_CCIF = 1;         //launch command
  while(FSTAT_CCIF == 0){}; //wait for done
  
  if((FSTAT & (FSTAT_ACCERR_MASK | FSTAT_FPVIOL_MASK)) != 0)
    return ACCESS_ERROR;
  else    
    return OK;
}


//==============================================================================
//EEPROM_Erase_Sector
//==============================================================================
unsigned char EEPROM_Erase_Sector(unsigned long int address)
{
  //size of sector is 512B
  
  //check if address is aligned (global address [2:0] != 000)  
  if((address & 0x00000001) != 0)
    return MISALIGNED_ADDRESS; 
    
  while(FSTAT_CCIF == 0){};   //wait if command in progress
  FSTAT = 0x30;             //clear ACCERR and PVIOL
  
  FCCOBIX = 0x01;    //we will write command up to FCCOB1
  FCCOB0HI = 0x12;
  FCCOB0LO = ((address & 0x00FF0000)>>16);
   
  FCCOB1 = (address & 0x0000FFFF);
  
  FSTAT_CCIF = 1;         //launch command
  while(FSTAT_CCIF == 0){}; //wait for done
  
  if((FSTAT & (FSTAT_ACCERR_MASK | FSTAT_FPVIOL_MASK)) != 0)
    return ACCESS_ERROR;
  else    
    return OK;
}

//==============================================================================
//EEPROM_Read_Byte
//==============================================================================
unsigned char EEPROM_Read_Byte(unsigned long int address)
{
  unsigned char data8;
  data8 = *(unsigned char *)address;
  return data8;
}

//==============================================================================
//EEPROM_Read_Word
//==============================================================================
unsigned int EEPROM_Read_Word(unsigned long int address)
{
  unsigned int data16;
  data16 = *(unsigned int *)address;
  return data16;
}

//==============================================================================
//EEPROM_Init
//==============================================================================
void EEPROM_Init(unsigned char fdiv)
{
  while(FSTAT_CCIF == 0){};   //wait if command in progress  
  FCLKDIV = fdiv;             //osc = ? MHz
}
