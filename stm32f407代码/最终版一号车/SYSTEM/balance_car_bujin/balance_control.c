#include "balance_control.h"
u8 flag_go=0;
int pwm_left=0;
int pwm_right=0;
int angle_pwm=0;
int velocity_pwm=0;
float angle_kp=120;
float angle_kd=0;
int zj_angle=0;
int ceshi_pwm;
int Final_Moto1=0;
int Final_Moto2=0;
s16 throug=0;
PID_wz balance_pi;

void balance_pid_init(void)
{
	balance_pi.kp=0.6;
	balance_pi.ki=balance_pi.kp/100;
	balance_pi.kd=0;
	balance_pi.itl_lim_up=100000;
	balance_pi.itl_lim_dn=-100000;
	balance_pi.limit_up=1800;//输出限幅
	balance_pi.limit_dn=-1800;
}
int balance_angle(float roll_in,int16_t gyro_in)
{
	return (int)(angle_kp*(roll_in-zj_angle));
}
int balance_velocity(int pwm_o_left,int pwm_o_right)
{
	
	if(rc_flag==1)
	{
		throug=(CH[3]-1000);
	}
	else throug=0;
	
	//balance_pi.err =/*期望速度*/0-(pwm_o_left+pwm_o_right)/2; // 计算当前误差
	if(1) //开启积分条件
	{balance_pi.integral += balance_pi.err+throug;      //求出偏差的积分
	if(1)//开启积分限幅
	{
		if(balance_pi.integral >= balance_pi.itl_lim_up){balance_pi.integral =  balance_pi.itl_lim_up;}//积分限幅
		else if(balance_pi.integral <= balance_pi.itl_lim_dn){balance_pi.integral =  balance_pi.itl_lim_dn;}}
	}
	else balance_pi.integral=0;//不开启积分，积分值为0
	if(flag_go==0) balance_pi.integral=0;//积分分离
	
	
	
	balance_pi.err_last=Mean_Filter(pwm_o_left,pwm_o_right);
	balance_pi.err=balance_pi.err*0.7+balance_pi.err_last*0.3;
	balance_pi.dif=balance_pi.err-balance_pi.err_last;
	balance_pi.out = balance_pi.kp*balance_pi.err + balance_pi.ki*balance_pi.integral + balance_pi.kd*balance_pi.dif;   //位置式PID控制器
	//balance_pi.err_last = balance_pi.err;   //保存上一次偏差 
	
	if(1){//是否输出限幅
	if(balance_pi.out >= balance_pi.limit_up){balance_pi.out =  balance_pi.limit_up;}//输出限幅
	else if(balance_pi.out <= balance_pi.limit_dn){balance_pi.out =  balance_pi.limit_dn;}}
	return (int)balance_pi.out;
}

void balance_pwm_out(int pwm1,int pwm2)
{
	if(flag_go==0)
	{
		PBout(10)=1;
		PBout(11)=1;
		Final_Moto1=65000;
		Final_Moto2=65000;
	}
	else
	{
		PBout(10)=0;
		PBout(11)=0;
		if(pwm1>0) PCout(6)=1;
		else PCout(6)=0;
		if(pwm2>0) PCout(8)=0;
		else PCout(8)=1;
		if(pwm1>2000) pwm1=2000;
		if(pwm1<-2000) pwm1=-2000;
		ceshi_pwm=923076/pwm1;
		if(ceshi_pwm>65000) {ceshi_pwm=65000;PBout(10)=1;PBout(11)=1;}
		if(ceshi_pwm<-65000) {ceshi_pwm=65000;PBout(10)=1;PBout(11)=1;}
		Final_Moto1=my_abs(ceshi_pwm);
		Final_Moto2=my_abs(ceshi_pwm);
	}
}


int my_abs(int a)
{
	return a>0?a:(-a);
}
#define FILTERING_TIMES 10
int Mean_Filter(int moto1,int moto2)
{
  u8 i;
  s32 Sum_Speed = 0; 
	s16 Filter_Speed;
  static  s16 Speed_Buf[FILTERING_TIMES]={0};
  for(i = 1 ; i<FILTERING_TIMES; i++)
  {
    Speed_Buf[i - 1] = Speed_Buf[i];
  }
  Speed_Buf[FILTERING_TIMES - 1] =moto1+moto2;

  for(i = 0 ; i < FILTERING_TIMES; i++)
  {
    Sum_Speed += Speed_Buf[i];
  }
  Filter_Speed = (s16)(Sum_Speed / FILTERING_TIMES);
	return Filter_Speed;
}
