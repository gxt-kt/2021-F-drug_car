#ifndef sbus_usart2_hh
#define sbus_usart2_hh
#include "sys.h"

extern uint8_t USART2_RX_BUF[];
extern uint16_t CH[];
extern u8 rc_flag;

void SBUS_Configuration(void);
void Sbus_Data_Count(uint8_t *buf);


#endif //sbus_usart2_hh

