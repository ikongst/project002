#include "NTC.h"
#include "Common.h"

//Program Size: Code=44644 RO-data=10184 RW-data=456 ZI-data=2732  
////Program Size: Code=44644 RO-data=10184 RW-data=456 ZI-data=2732  
const unsigned int Table_NTC[62] = 
{
	// 100~150 table,62 points			
	//deg-C		table index	1000mv/16
	100	,    //	0	102
	101	,    //	1	101
	101	,    //	2	100
	102	,    //	3	99
	102	,    //	4	98
	103	,    //	5	97
	104	,    //	6	96
	104	,    //	7	95
	105	,    //	8	94
	105	,    //	9	93
	106	,    //	10	92
	107	,    //	11	91
	107	,    //	12	90
	108	,    //	13	89
	108	,    //	14	88
	109	,    //	15	87
	110	,    //	16	86
	110	,    //	17	85
	111	,    //	18	84
	112	,    //	19	83
	112	,    //	20	82
	113	,    //	21	81
	114	,    //	22	80
	114	,    //	23	79
	115	,    //	24	78
	116	,    //	25	77
	117	,    //	26	76
	117	,    //	27	75
	118	,    //	28	74
	119	,    //	29	73
	120	,    //	30	72
	120	,    //	31	71
	121	,    //	32	70
	122	,    //	33	69
	123	,    //	34	68
	124	,    //	35	67
	124	,    //	36	66
	125	,    //	37	65
	126	,    //	38	64
	127	,    //	39	63
	128	,    //	40	62
	129	,    //	41	61
	130	,    //	42	60
	130	,    //	43	59
	131	,    //	44	58
	132	,    //	45	57
	133	,    //	46	56
	134	,    //	47	55
	135	,    //	48	54
	136	,    //	49	53
	137	,    //	50	52
	138	,    //	51	51
	140	,    //139	52	50
	141	,    //	53	49
	142	,    //	54	48
	143	,    //	55	47
	144	,    //	56	46
	145	,    //	57	45
	147	,    //146	58	44
	148	,    //	59	43
	149	,    //	60	42
	150	    //	60	41
};

#include "Protection.h"
// return value have +50 offset of deg-C.
unsigned int uicalcuTemp(unsigned int mV_value)
{
  unsigned int tempmV    = mV_value>>4;
	unsigned int tempVlaue = 151;
	if(tempmV<41)
	{
		tempVlaue = 151; // maximum
	}
	else
	{
		if(tempmV>=275) // less than 15 deg-C
		{
			tempVlaue = 0;
		}
		else
		{
			if(tempmV > 102)
			{
				tempVlaue = 99; // minimum
			}
			else
			{
				tempVlaue = Table_NTC[102-tempmV];			
			}
	  }
	}
	
	tempVlaue += TEMP_OFFSET;
  return tempVlaue;
}