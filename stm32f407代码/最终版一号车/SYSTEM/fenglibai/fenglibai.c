#include "fenglibai.h"

u8 flb_flag=0;



float Amplitude_x=0;
float Amplitude_y=0;
float target_x=0;
float target_y=0;
float mersure_x=0;
float mersure_y=0;

PID_wz x_pid;
PID_wz y_pid;

PID_wz x_axis_wz;
PID_wz x_axis_sp;
PID_wz y_axis_wz;
PID_wz y_axis_sp;
float x_anti_wz=0;
float y_anti_wz=0;
float x_sp_val=0;
float y_sp_val=0;



void flb_pid_init(void)
{
	x_pid.kp=-2;
	x_pid.ki=0;
	x_pid.kd=-0;
	x_pid.itl_lim_up=0;
	x_pid.itl_lim_dn=0;
	x_pid.limit_up=0;
	x_pid.limit_dn=0;
	
	y_pid.kp=x_pid.kp;
	y_pid.ki=0;
	y_pid.kd=x_pid.kd;
	y_pid.itl_lim_up=0;
	y_pid.itl_lim_dn=0;
	y_pid.limit_up=0;
	y_pid.limit_dn=0;
	
//	x_axis_wz.kp=0.06;
//	x_axis_wz.ki=0;
//	x_axis_wz.kd=0.02;
//	x_axis_wz.itl_lim_up=1000;
//	x_axis_wz.itl_lim_dn=-1000;
//	x_axis_wz.limit_up=0.4;
//	x_axis_wz.limit_dn=-0.4;
//	
//	x_axis_sp.kp=1400;
//	x_axis_sp.ki=0;
//	x_axis_sp.kd=700*0.6;
//	x_axis_sp.limit_up=800;
//	x_axis_sp.limit_dn=-800;
//	
//	y_axis_wz.kp=x_axis_wz.kp;
//	y_axis_wz.ki=x_axis_wz.ki;
//	y_axis_wz.kd=x_axis_wz.kd;
//	x_axis_wz.itl_lim_up=x_axis_wz.itl_lim_up;
//	x_axis_wz.itl_lim_dn=x_axis_wz.itl_lim_dn;
//	y_axis_wz.limit_up=x_axis_wz.limit_up;
//	y_axis_wz.limit_dn=x_axis_wz.limit_dn;

//	y_axis_sp.kp=x_axis_sp.kp;
//	y_axis_sp.ki=0;
//	y_axis_sp.kd=x_axis_sp.kd;
//	y_axis_sp.limit_up=800;
//	y_axis_sp.limit_dn=-800;
}

float flb_x_pid(float pid_now,float pid_anti)
{//位置控制器
	x_pid.err =pid_anti-pid_now; // 计算当前误差
	if(0) //开启积分条件
	{x_pid.integral += x_pid.err;      //求出偏差的积分
	if(0)//开启积分限幅
		{if(x_pid.integral >= x_pid.itl_lim_up){x_pid.integral =  x_pid.itl_lim_up;}//积分限幅
		else if(x_pid.integral <= x_pid.itl_lim_dn){x_pid.integral =  x_pid.itl_lim_dn;}}
	}
		else x_pid.integral=0;//不开启积分，积分值为0

	x_pid.dif=x_pid.err-x_pid.err_last;
	x_pid.out = x_pid.kp*x_pid.err + x_pid.ki*x_pid.integral + x_pid.kd*x_pid.dif;   //位置式PID控制器
	x_pid.err_last = x_pid.err;   //保存上一次偏差 

	if(0){//是否输出限幅
	if(x_pid.out >= x_pid.limit_up){x_pid.out =  x_pid.limit_up;}//输出限幅
	else if(x_pid.out <= x_pid.limit_dn){x_pid.out =  x_pid.limit_dn;}}
	return x_pid.out;
}

float flb_y_pid(float pid_now,float pid_anti)
{//位置控制器
	y_pid.err =pid_anti-pid_now; // 计算当前误差
	if(0) //开启积分条件
	{y_pid.integral += y_pid.err;      //求出偏差的积分
	if(0)//开启积分限幅
		{if(y_pid.integral >= y_pid.itl_lim_up){y_pid.integral =  y_pid.itl_lim_up;}//积分限幅
		else if(y_pid.integral <= y_pid.itl_lim_dn){y_pid.integral =  y_pid.itl_lim_dn;}}
	}
		else y_pid.integral=0;//不开启积分，积分值为0

	y_pid.dif=y_pid.err-y_pid.err_last;
	y_pid.out = y_pid.kp*y_pid.err + y_pid.ki*y_pid.integral + y_pid.kd*y_pid.dif;   //位置式PID控制器
	y_pid.err_last = y_pid.err;   //保存上一次偏差 

	if(0){//是否输出限幅
	if(y_pid.out >= y_pid.limit_up){y_pid.out =  y_pid.limit_up;}//输出限幅
	else if(y_pid.out <= y_pid.limit_dn){y_pid.out =  y_pid.limit_dn;}}
	return y_pid.out;
}


float flb_x_wz_pid(float pid_now,float pid_anti)
{//位置控制器
	x_axis_wz.err =pid_anti-pid_now; // 计算当前误差
	if(0) //开启积分条件
	{x_axis_wz.integral += x_axis_wz.err;      //求出偏差的积分
	if(0)//开启积分限幅
		{if(x_axis_wz.integral >= x_axis_wz.itl_lim_up){x_axis_wz.integral =  x_axis_wz.itl_lim_up;}//积分限幅
		else if(x_axis_wz.integral <= x_axis_wz.itl_lim_dn){x_axis_wz.integral =  x_axis_wz.itl_lim_dn;}}
	}
		else x_axis_wz.integral=0;//不开启积分，积分值为0

	x_axis_wz.dif=x_axis_wz.err-x_axis_wz.err_last;
	x_axis_wz.out = x_axis_wz.kp*x_axis_wz.err + x_axis_wz.ki*x_axis_wz.integral + x_axis_wz.kd*x_axis_wz.dif;   //位置式PID控制器
	x_axis_wz.err_last = x_axis_wz.err;   //保存上一次偏差 

	if(1){//是否输出限幅
	if(x_axis_wz.out >= x_axis_wz.limit_up){x_axis_wz.out =  x_axis_wz.limit_up;}//输出限幅
	else if(x_axis_wz.out <= x_axis_wz.limit_dn){x_axis_wz.out =  x_axis_wz.limit_dn;}}
	return x_axis_wz.out;
}


float flb_x_sp_pid(float pid_now,float pid_anti)
{//速度控制器
	x_axis_sp.err =pid_anti-pid_now; // 计算当前误差
	if(0) //开启积分条件
	{x_axis_sp.integral += x_axis_sp.err;      //求出偏差的积分
	if(0)//开启积分限幅
		{if(x_axis_sp.integral >= x_axis_sp.itl_lim_up){x_axis_sp.integral =  x_axis_sp.itl_lim_up;}//积分限幅
		else if(x_axis_sp.integral <= x_axis_sp.itl_lim_dn){x_axis_sp.integral =  x_axis_sp.itl_lim_dn;}}
	}
		else x_axis_sp.integral=0;//不开启积分，积分值为0

	x_axis_sp.dif=x_axis_sp.err-x_axis_sp.err_last;
	x_axis_sp.out = x_axis_sp.kp*x_axis_sp.err + x_axis_sp.ki*x_axis_sp.integral + x_axis_sp.kd*x_axis_sp.dif;   //位置式PID控制器
	x_axis_sp.err_last = x_axis_sp.err;   //保存上一次偏差 

	if(1){//是否输出限幅
	if(x_axis_sp.out >= x_axis_sp.limit_up){x_axis_sp.out =  x_axis_sp.limit_up;}//输出限幅
	else if(x_axis_sp.out <= x_axis_sp.limit_dn){x_axis_sp.out =  x_axis_sp.limit_dn;}}
	return x_axis_sp.out;
}


float flb_y_wz_pid(float pid_now,float pid_anti)
{//位置控制器
	y_axis_wz.err =pid_anti-pid_now; // 计算当前误差
	if(0) //开启积分条件
	{y_axis_wz.integral += y_axis_wz.err;      //求出偏差的积分
	if(0)//开启积分限幅
		{if(y_axis_wz.integral >= y_axis_wz.itl_lim_up){y_axis_wz.integral =  y_axis_wz.itl_lim_up;}//积分限幅
		else if(y_axis_wz.integral <= y_axis_wz.itl_lim_dn){y_axis_wz.integral =  y_axis_wz.itl_lim_dn;}}
	}
		else y_axis_wz.integral=0;//不开启积分，积分值为0

	y_axis_wz.dif=y_axis_wz.err-y_axis_wz.err_last;
	y_axis_wz.out = y_axis_wz.kp*y_axis_wz.err + y_axis_wz.ki*y_axis_wz.integral + y_axis_wz.kd*y_axis_wz.dif;   //位置式PID控制器
	y_axis_wz.err_last = y_axis_wz.err;   //保存上一次偏差 

	if(1){//是否输出限幅
	if(y_axis_wz.out >= y_axis_wz.limit_up){y_axis_wz.out =  y_axis_wz.limit_up;}//输出限幅
	else if(y_axis_wz.out <= y_axis_wz.limit_dn){y_axis_wz.out =  y_axis_wz.limit_dn;}}
	return y_axis_wz.out;
}

float flb_y_sp_pid(float pid_now,float pid_anti)
{
	y_axis_sp.err =pid_anti-pid_now; // 计算当前误差
	if(0) //开启积分条件
	{y_axis_sp.integral += y_axis_sp.err;      //求出偏差的积分
	if(0)//开启积分限幅
		{if(y_axis_sp.integral >= y_axis_sp.itl_lim_up){y_axis_sp.integral =  y_axis_sp.itl_lim_up;}//积分限幅
		else if(y_axis_sp.integral <= y_axis_sp.itl_lim_dn){y_axis_sp.integral =  y_axis_sp.itl_lim_dn;}}
	}
		else y_axis_sp.integral=0;//不开启积分，积分值为0

	y_axis_sp.dif=y_axis_sp.err-y_axis_sp.err_last;
	y_axis_sp.out = y_axis_sp.kp*y_axis_sp.err + y_axis_sp.ki*y_axis_sp.integral + y_axis_sp.kd*y_axis_sp.dif;   //位置式PID控制器
	y_axis_sp.err_last = y_axis_sp.err;   //保存上一次偏差 

	if(1){//是否输出限幅
	if(y_axis_sp.out >= y_axis_sp.limit_up){y_axis_sp.out =  y_axis_sp.limit_up;}//输出限幅
	else if(y_axis_sp.out <= y_axis_sp.limit_dn){y_axis_sp.out =  y_axis_sp.limit_dn;}}
	return y_axis_sp.out;
}
#define flb_sp_filter 10
float x_sp_farr[flb_sp_filter]={0};
float x_sp_filter(float a)
{
	int i=0;
	float sum=0;
	for(;i<flb_sp_filter-1;i++)
	{
		x_sp_farr[i]=x_sp_farr[i+1];
	}
	x_sp_farr[i]=a;
	for(i=0;i<flb_sp_filter;i++)
	{
		sum+=x_sp_farr[i];
	}
	return (float)(sum/flb_sp_filter);
}
float y_sp_farr[flb_sp_filter]={0};
float y_sp_filter(float a)
{
	int i=0;
	float sum=0;
	for(;i<flb_sp_filter-1;i++)
	{
		y_sp_farr[i]=y_sp_farr[i+1];
	}
	y_sp_farr[i]=a;
	for(i=0;i<flb_sp_filter;i++)
	{
		sum+=y_sp_farr[i];
	}
	return (float)(sum/flb_sp_filter);
}
void flb_pwm_out(float x_pwm,float y_pwm)
{
	if(x_pwm>1000) x_pwm=1000;
	if(x_pwm<-1000) x_pwm=-1000;
	if(y_pwm>1000) y_pwm=1000;
	if(y_pwm<-1000) y_pwm=-1000;
	
//	TIM_SetCompare1(TIM8,0);//you
//		TIM_SetCompare2(TIM8,0);//zuo
//		TIM_SetCompare3(TIM8,0);//hou
//		TIM_SetCompare4(TIM8,0);//qian
	if(x_pwm>0)
	{
		TIM_SetCompare1(TIM8,GXT_abs((int)x_pwm));//左
		TIM_SetCompare2(TIM8,0);//右
	}
	else
	{
		TIM_SetCompare1(TIM8,0);//左
		TIM_SetCompare2(TIM8,GXT_abs((int)x_pwm));//前
	}
	if(y_pwm>0)
	{
		TIM_SetCompare3(TIM8,0);//后
		TIM_SetCompare4(TIM8,GXT_abs((int)y_pwm));//前
	}
	else
	{
		TIM_SetCompare3(TIM8,GXT_abs((int)y_pwm));//后
		TIM_SetCompare4(TIM8,0);//前
	}
}
