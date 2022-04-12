#ifndef usart3_h__
#define usart3_h__
#include "sys.h"


extern u8 openmv_zsp_0;
extern s16 openmv_zsp_1;
extern s16 openmv_zsp_2;
extern s32 u3_geti;

extern int16_t gy25_pitch;
extern int16_t gy25_roll;
extern int16_t gy25_yaw;

extern float u3_Roll;
extern float u3_Pitch;
extern float u3_Yaw;
//extern float roll,pitch,yaw;
//extern float GYRO_ROLL,GYRO_PITCH,GYRO_YAW;

//void qt_date_deal(u8 data);
void usart_3_init(u32 bound);
//void GXT_DATA_DEAL(void);
//void USART3_IMU_DATA(void);
#endif //usart3_h__

