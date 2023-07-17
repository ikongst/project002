/*
 * kongst_types.h
 *
 *  Created on: Jun 26, 2023
 *      Author: kongyun
 */

#ifndef __KSE_TYPES_H
#define __KSE_TYPES_H

/******************************************************************************
 * INCLUDES
 *****************************************************************************/

/******************************************************************************
 * DEFINES
 *****************************************************************************/

/** @defgroup CDTParser These defines are necessary to satisfy the Eclipse CDT parser */
/** @addtogroup CDTParser
 * @{
 */
#ifndef __CDT_PARSER__
/** for CDT parser */
#define __str1(x) #x
/** for CDT parser */
#define __str(x) __str1(x)
/** for CDT parser */
#define concat1(x,y) x##y
/** for CDT parser */
#define concat(x,y) concat1(x,y)
/** for CDT parser */
#ifndef  MODULETEST
#define _at(n) concat(@,n)
#else
#define _at(n)
#endif
#else
/** for CDT parser */
#define _at(n)
#endif
/** @}
 *
 */

/** to set a bit or check if bit is set */
#define SET 			(1)
/** to reset a bit or check if bit is reset */
#define CLEAR 			(0)


/** helper macro */
#define ATPASTE3( a, b, c)                        TPASTE3( a, b, c)
/** helper macro */
#define TPASTE3( a, b, c)                         a##b##c
/** helper macro */
#define STRINGZ(x)                                #x
/** helper macro */
#define ASTRINZ(x)								  STRINGZ(x)



/******************************************************************************
 * TYPEDEFS
 *****************************************************************************/

/** 8-bit unsigned type */
typedef unsigned char   uint8_t;
/** 8-bit signed  type */
typedef   signed char    int8_t;
/** 16-bit unsigned  type */
typedef unsigned short uint16_t;
/** 16-bit signed  type */
typedef   signed short  int16_t;
/** 32-bit unsigned  type */
typedef unsigned int  uint32_t;
/** 32-bit signed  type */
typedef   signed int   int32_t;

/** helper typedef to access a word (16bit) */
typedef union
{
	uint16_t word;			/**< 16bit direct access */
	struct
	{
		uint8_t lowbyte;	/**< lowbyte */
		uint8_t highbyte;	/**< highbyte */
	} bytes;				/**< byte access */
	uint8_t byte[2];		/**< byte access */
} word_t;

#endif  /* __KSE_TYPES_H */
