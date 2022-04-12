#ifndef car_h__
#define car_h__
#include "sys.h"
extern u8 ss1,ss2,ss3,ss4,ss5;
extern u8 car_stop;
extern int Speed1;
extern int Speed2;
extern u8 board;
extern u8 car_sta;
extern int time_up;
extern int detect_num;
extern int vel;
extern float Kp_qwq;
extern int Speed;
#define SPEED 500
#define DELAY_TIME 500
void CAR_xunji(void);
#endif //car_h__

