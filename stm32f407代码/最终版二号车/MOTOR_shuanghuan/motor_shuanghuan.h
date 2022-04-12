#ifndef motor_shuanghaun__h__
#define motor_shuanghaun__h__
#include "sys.h"
extern int m_exp_val;
extern int m_enc_val;
extern int m_pwm_out;
extern int enc_sum;
extern float test;
extern int zjbl;
extern struct PID_wz m_speed;
extern struct PID_wz m_position;
void motor_init(u32 arr,u32 psc);
void motor_pid_init(void);
float PID_WZ_M_TEST(float pid_now,float pid_anti);
float PID_ZL_M_TEST(float pid_now,float pid_anti);
void PWM_REA_OUT(int a);
#endif


