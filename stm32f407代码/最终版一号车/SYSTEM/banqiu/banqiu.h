#ifndef banqiu_h__
#define banqiu_h__
#include "sys.h"
void  banqiu_init(u32 arr,u32 psc);
extern s16 pwm_out1;
extern s16 pwm_out2;
extern s16 wucha;
extern s16 x_val;
extern s16 y_val;
extern s16 wucha_y;
extern struct PID_wz banqiu_x;
extern struct PID_wz banqiu_y;
extern struct PID_wz banqiu_su_x;
extern struct PID_wz banqiu_su_y;
void  banqiu_pid_init(void);
float myabs(float a);
void banqiu_control(s16 pid_now_x,s16 pid_anti_x,s16 pid_now_y,s16 pid_anti_y);

#endif //banqiu_h__

