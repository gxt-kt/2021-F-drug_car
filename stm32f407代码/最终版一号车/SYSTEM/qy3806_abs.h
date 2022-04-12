#ifndef qy3806_abs_h__
#define qy3806_abs_h__
#include "sys.h"


#define SPI1_CS_OFF PBout(6)=0;
#define SPI1_CS_ON PBout(6)=1;

extern u8 qy_state;
extern u8 qy_crc8;
extern u16 qy_readdata;

void QY3806_init(void);
void delay_us_rj(u16 time);
uint8_t SSIReadAngle(uint8_t *state,uint8_t *CRC8, uint16_t* ReadRegData);
int Even_parity(int value, int n_bit);
u8 QY3806_Send_Data(u8 TxData);


#endif //qy3806_abs_h__


