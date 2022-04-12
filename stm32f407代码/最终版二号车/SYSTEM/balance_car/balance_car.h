#ifndef _balance_car_h__
#define _balance_car_h__
#include "sys.h"

#define machine_zz (7.2)

extern int encoder_left;
extern int encoder_right;
extern int sp_right_rea;
extern int sp_left_rea;

extern s16 bal_pwm_out1;
extern s16 bal_pwm_out2;

extern struct PID_wz bal_zl;
extern struct PID_wz bal_su;

void bal_pid_val_init(void);
float bal_sp_pid(float pid_now,float pid_anti);
float bal_zl_pid(float pid_now,float pid_anti);

int BAL_FILT_RIGHT(int a);
int BAL_FILT_LEFT(int a);

void bal_IO_PWM_init(u32 arr,u32 psc);
void bal_PWM_OUT(s16 pwm1,s16 pwm2);
#endif //_balance_car_h__

