#ifndef MOTOR_H__
#define MOTOR_H__
#include "sys.h"

extern struct PID_wz M_SP1;
extern struct PID_wz M_SP2;

float PID_WZ_M1(float pid_now,float pid_anti);
float PID_WZ_M2(float pid_now,float pid_anti);
void MOTOR_ANTI(int sp1,int sp2);
void MOTOR_PID(void);
#endif //MOTOR_H__

