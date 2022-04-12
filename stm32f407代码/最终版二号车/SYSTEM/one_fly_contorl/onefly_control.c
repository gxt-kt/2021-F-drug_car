#include "onefly_control.h"

u8 onefly_setup=0;
PID_wz onefly_pid;

void  onefly_pid_init(void)
{    
	onefly_pid.kp=5;
	onefly_pid.ki=5/100;
	onefly_pid.kd=0;
	onefly_pid.out=0;
	onefly_pid.itl_lim_up=5000;
	onefly_pid.itl_lim_dn=-5000;
	onefly_pid.limit_up=800;
	onefly_pid.limit_dn=0;
}

s16 onefly_control(s16 pid_now,s16 pid_anti)
{
	if((pid_now>2500)||(onefly_setup==0))//判断是否已经失控或者还没开始运行
	{
		onefly_setup=0;
		TIM_SetCompare1(TIM8,0);
		return 0;
	}
	
	onefly_pid.err =pid_anti-pid_now; // 计算当前误差
	if(onefly_setup==1) //开启积分条件
	{onefly_pid.integral += onefly_pid.err;      //求出偏差的积分
	if(1)//开启积分限幅
		{if(onefly_pid.integral >= onefly_pid.itl_lim_up){onefly_pid.integral =  onefly_pid.itl_lim_up;}//积分限幅
		else if(onefly_pid.integral <= onefly_pid.itl_lim_dn){onefly_pid.integral =  onefly_pid.itl_lim_dn;}}
	if(1)/*开启积分分离*/{if((onefly_pid.err<=30)&&(onefly_pid.err>=-30))onefly_pid.integral=0;}
	}
		else onefly_pid.integral=0;//不开启积分，积分值为0
	
	onefly_pid.dif=onefly_pid.err-onefly_pid.err_last;
	onefly_pid.out = onefly_pid.kp*onefly_pid.err + onefly_pid.ki*onefly_pid.integral + onefly_pid.kd*onefly_pid.dif;   //位置式PID控制器
	onefly_pid.err_last = onefly_pid.err;   //保存上一次偏差 
	
	if(1){//是否输出限幅
	if(onefly_pid.out >= onefly_pid.limit_up){onefly_pid.out =  onefly_pid.limit_up;}//输出限幅
	else if(onefly_pid.out <= onefly_pid.limit_dn){onefly_pid.out =  onefly_pid.limit_dn;}}
	//return (u16)onefly_pid.out;
	
	//在这里直接输出了
	TIM_SetCompare1(TIM8,(u16)onefly_pid.out);
	return 1;
}
