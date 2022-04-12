#include "pid.h"

PID_wz wz_text;
PID_zl zl_text;


void  pid_Init(void)
{    
	wz_text.kp=0.5;
	wz_text.ki=0.01;
	wz_text.kd=0;
	zl_text.kp=0;
	zl_text.ki=0.001;
	zl_text.kd=0;
}

// 位置式PID控制
float PID_WZ_TEST(float pid_now,float pid_anti)
{
    wz_text.err =pid_anti-pid_now; // 计算当前误差
    if(1) //开启积分条件
		{wz_text.integral += wz_text.err;      //求出偏差的积分
		if(0)//开启积分限幅
			{if(wz_text.integral >= wz_text.itl_lim_up){wz_text.integral =  wz_text.itl_lim_up;}//积分限幅
			else if(wz_text.integral <= wz_text.itl_lim_dn){wz_text.integral =  wz_text.itl_lim_dn;}}
		}
			else wz_text.integral=0;//不开启积分，积分值为0
		
		wz_text.dif=wz_text.err-wz_text.err_last;
    wz_text.out = wz_text.kp*wz_text.err + wz_text.ki*wz_text.integral + wz_text.kd*wz_text.dif;   //位置式PID控制器
    wz_text.err_last = wz_text.err;   //保存上一次偏差 
		
		if(0){//是否输出限幅
    if(wz_text.out >= wz_text.limit_up){wz_text.out =  wz_text.limit_up;}//输出限幅
		else if(wz_text.out <= wz_text.limit_dn){wz_text.out =  wz_text.limit_dn;}}
		return wz_text.out;
}


// 增量式PID控制
float PID_ZL_TEST(float pid_now,float pid_anti)
{
    zl_text.err =pid_anti-pid_now; // 计算当前误差
		zl_text.dif=zl_text.err-zl_text.err_last;//计算微分
		zl_text.dif_two=zl_text.err-2*zl_text.err_last+zl_text.err_pre;//计算微分
    zl_text.out = zl_text.kp*zl_text.dif + zl_text.ki*zl_text.err + zl_text.kd*zl_text.dif_two;   //位置式PID控制器
    zl_text.err_pre = zl_text.err_last;   //保存上一次偏差 
		zl_text.err_last = zl_text.err;   //保存上一次偏差 
		if(0){//是否输出限幅
    if(zl_text.out >= zl_text.limit_up){zl_text.out =  zl_text.limit_up;}//输出限幅
		else if(zl_text.out <= zl_text.limit_dn){zl_text.out =  zl_text.limit_dn;}}
		return zl_text.out;
}
