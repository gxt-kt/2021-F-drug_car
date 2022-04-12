#ifndef pid_h__
#define pid_h__
#include "sys.h"



typedef struct PID_zl{
    float err;                //定义偏差值
    float err_last;            //定义上一个偏差值
		float err_pre;            //定义上上个偏差
		float dif;								//定义微分值
		float dif_two;								//定义二次微分值
    float kp,ki,kd;            //定义比例、积分、微分系数
    float out;          
		float limit_up;
		float limit_dn;
}PID_zl;
typedef struct PID_wz{
		float now;                //定义当前值
    float anti;            //定义期望值
    float err;                //定义偏差值
    float err_last;            //定义上一个偏差值
		float dif;								//定义微分值
    float kp,ki,kd;            //定义比例、积分、微分系数
    float integral;            //定义积分值
    float out;          //定义电压值（控制执行器的变量）
		float itl_lim_up;//积分限幅
		float itl_lim_dn;
		float limit_up;//输出限幅
		float limit_dn;
}PID_wz;
extern struct PID_zl zl_text;
extern struct PID_wz wz_text;

void  pid_Init(void);
float PID_WZ_TEST(float pid_now,float pid_anti);
float PID_ZL_TEST(float pid_now,float pid_anti);
#endif //pid_h__

