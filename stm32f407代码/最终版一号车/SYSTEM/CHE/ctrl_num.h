#ifndef CTRL_NUM_H__
#define CTRL_NUM_H__
#include "sys.h"

extern u8 return_sta;
extern u8 sta_num[];
extern u8 sta_i;
extern u8 car_task;
extern u8 u2_send[];
void U2_DATA_DEAL(void);
void UART2_Send_Str(u8 *s,u8 cnt_s);
#endif //CTRL_NUM_H__

