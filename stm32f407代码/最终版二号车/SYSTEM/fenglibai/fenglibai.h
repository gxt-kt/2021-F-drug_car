#ifndef fenglibai_h__
#define fenglibai_h__
#include "sys.h"

#define FLB_T 1440
#define PI 3.14159
#define HEIGHT 785 //MM


extern float Amplitude_x;
extern float Amplitude_y;
extern float target_x;
extern float target_y;
extern float mersure_x;
extern float mersure_y;

extern struct PID_wz x_pid;
extern struct PID_wz y_pid;

float flb_x_pid(float pid_now,float pid_anti);
float flb_y_pid(float pid_now,float pid_anti);

extern u8 flb_flag;
extern float x_anti_wz;
extern float y_anti_wz;
extern float x_sp_val;
extern float y_sp_val;
extern struct PID_wz x_axis_wz;
extern struct PID_wz y_axis_wz;
extern struct PID_wz x_axis_sp;
extern struct PID_wz y_axis_sp;
float x_sp_filter(float a);
float y_sp_filter(float a);
void flb_pid_init(void);
float flb_x_wz_pid(float pid_now,float pid_anti);
float flb_x_sp_pid(float pid_now,float pid_anti);
float flb_y_wz_pid(float pid_now,float pid_anti);
float flb_y_sp_pid(float pid_now,float pid_anti);
void flb_pwm_out(float x_pwm,float y_pwm);
#endif //fenglibai_h__

