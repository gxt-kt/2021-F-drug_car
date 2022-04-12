#ifndef car_uart2_h_
#define car_uart2_h_
#include "sys.h"
extern u8 black_num;
extern u8 zuo1,you1;
extern int openmvdata[10];
extern u8 USART3_RX_BUF[];
extern u8 USART4_RX_BUF[];
void GXT_DATA_DEAL(void);
void detect_board(void);
#endif //car_uart1_h_

