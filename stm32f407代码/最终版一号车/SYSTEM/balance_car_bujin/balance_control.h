#ifndef balance_control_h
#define balance_control_h
#include "sys.h"


extern u8 flag_go;
extern int pwm_left;
extern int pwm_right;
extern int angle_pwm;
extern int velocity_pwm;
extern float angle_kd;
extern float angle_kp;
extern int ceshi_pwm;
extern int Final_Moto1;
extern int Final_Moto2;
extern int zj_angle;
extern struct PID_wz balance_pi;
int Mean_Filter(int moto1,int moto2);
void balance_pid_init(void);
int balance_angle(float roll_in,int16_t gyro_in);
int balance_velocity(int pwm_o_left,int pwm_o_right);
void balance_pwm_out(int pwm1,int pwm2);
int my_abs(int a);

#endif //balance_control_h

