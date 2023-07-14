#ifndef __NTC_H__
#define __NTC_H__

// return value have +50 offset of deg-C.
// 0+50            -> below 0
// 99+50           -> < 100
// 100+50 ~ 150+50 -> 100~150
// >150            -> 151
unsigned int uicalcuTemp(unsigned int mV_value);

#endif
