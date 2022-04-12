#ifndef k210_it_h__
#define k210_it_h__
#include "sys.h"
extern int aaa,bbb;
extern u8 k210_left[];
extern u8 k210_right[];
extern int k210_cnt_l[];
extern int k210_cnt_r[];
extern u8 count_go;
extern int left_max,right_max;
extern u8 find_val1,find_val2,find_val3,find_val4,find_val5;
extern int val1_cnt,val2_cnt,val3_cnt,val4_cnt,val5_cnt;
void ZSP_DEAL1(void);
void ZSP_DEAL2(void);


int find_max(u8 i);
void find_MAX(u8 a);
extern u8 USART5_RX_BUF[];
extern u8 USART6_RX_BUF[];
#endif //k210_it_h__

