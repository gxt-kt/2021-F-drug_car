#ifndef adc_h__
#define adc_h__
#include "sys.h"
extern u8 SR04_VAL;
u16 Get_Adc_Average(u8 ch,u8 times,u8 delay_t);
void  Adc_Init(void);
u16 Get_Adc(u8 ch);
u8 CAR_SR04(void);
#endif //adc_h__

