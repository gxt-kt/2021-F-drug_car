#include "balance_car.h"

int encoder_left;
int encoder_right;
int sp_right_rea;
int sp_left_rea;
s16 bal_pwm_out1;
s16 bal_pwm_out2;
PID_wz bal_su;//速度
PID_wz bal_zl;//直立

void bal_pid_val_init(void)
{
	bal_su.kp=-0.05;
	bal_su.ki=bal_su.kp/100;
	bal_su.kd=0;
	bal_su.limit_up=800;
	bal_su.limit_dn=-800;
	bal_su.itl_lim_up=300000;
	bal_su.itl_lim_dn=-300000;
	
	
	bal_zl.kp=-36;
	bal_zl.ki=0;
	bal_zl.kd=-0.7;
	bal_zl.limit_up=800;
	bal_zl.limit_dn=-800;
}

float bal_sp_pid(float pid_now,float pid_anti)//直立
{
	bal_su.err =pid_anti-pid_now; // 计算当前误差
	if(1) //开启积分条件
	{bal_su.integral += bal_su.err;      //求出偏差的积分
	if(1)//开启积分限幅
		{if(bal_su.integral >= bal_su.itl_lim_up){bal_su.integral =  bal_su.itl_lim_up;}//积分限幅
		else if(bal_su.integral <= bal_su.itl_lim_dn){bal_su.integral =  bal_su.itl_lim_dn;}}
	}
		else bal_su.integral=0;//不开启积分，积分值为0
	
	bal_su.dif=bal_su.err-bal_su.err_last;
	bal_su.out = bal_su.kp*bal_su.err + bal_su.ki*bal_su.integral + bal_su.kd*bal_su.dif;   //位置式PID控制器
	bal_su.err_last = bal_su.err;   //保存上一次偏差 
	
	if(1){//是否输出限幅
	if(bal_su.out >= bal_su.limit_up){bal_su.out =  bal_su.limit_up;}//输出限幅
	else if(bal_su.out <= bal_su.limit_dn){bal_su.out =  bal_su.limit_dn;}}
	return bal_su.out;
}


float bal_zl_pid(float pid_now,float pid_anti)//直立
{
	bal_zl.err =pid_anti-pid_now; // 计算当前误差
	if(0) //开启积分条件
	{bal_zl.integral += bal_zl.err;      //求出偏差的积分
	if(0)//开启积分限幅
		{if(bal_zl.integral >= bal_zl.itl_lim_up){bal_zl.integral =  bal_zl.itl_lim_up;}//积分限幅
		else if(bal_zl.integral <= bal_zl.itl_lim_dn){bal_zl.integral =  bal_zl.itl_lim_dn;}}
	}
		else bal_zl.integral=0;//不开启积分，积分值为0
	
	bal_zl.dif=bal_zl.err-bal_zl.err_last;
	bal_zl.out = bal_zl.kp*bal_zl.err + bal_zl.ki*bal_zl.integral + bal_zl.kd*bal_zl.dif;   //位置式PID控制器
	bal_zl.err_last = bal_zl.err;   //保存上一次偏差 
	
	if(1){//是否输出限幅
	if(bal_zl.out >= bal_zl.limit_up){bal_zl.out =  bal_zl.limit_up;}//输出限幅
	else if(bal_zl.out <= bal_zl.limit_dn){bal_zl.out =  bal_zl.limit_dn;}}
//	bal_pwm_out1=bal_zl.out;
//	bal_pwm_out2=bal_zl.out;
	return bal_zl.out;
}


#define bal_fil_t 3
int gbal_sp_left[bal_fil_t];//定义滤波数组
int BAL_FILT_LEFT(int a)
{
	int i=0;
	float sum=0;
	for(;i<bal_fil_t-1;i++)
	{
		gbal_sp_left[i]=gbal_sp_left[i+1];
	}
	gbal_sp_left[i]=a;
	for(i=0;i<bal_fil_t;i++)
	{
		sum+=gbal_sp_left[i];
	}
	return (int)(sum/bal_fil_t);
}
int gbal_sp_right[bal_fil_t];//定义滤波数组
int BAL_FILT_RIGHT(int a)
{
	int i=0;
	float sum=0;
	for(;i<bal_fil_t-1;i++)
	{
		gbal_sp_right[i]=gbal_sp_right[i+1];
	}
	gbal_sp_right[i]=a;
	for(i=0;i<bal_fil_t;i++)
	{
		sum+=gbal_sp_right[i];
	}
	return (int)(sum/bal_fil_t);
}

void bal_IO_PWM_init(u32 arr,u32 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//使能PORTF时钟	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//使能PORTF时钟	

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;           
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
    GPIO_Init(GPIOE,&GPIO_InitStructure);              //初始化PF9
		PEout(7)=0;
	PEout(12)=0;
	PEout(13)=0;
	PEout(14)=0;
	PEout(15)=0;
	
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8); 
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8); 

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;           
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;        //上拉
    GPIO_Init(GPIOC,&GPIO_InitStructure);              //初始化PF9

    TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);//初始化定时器14

    	//初始化TIM14 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
//	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
//    TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
    TIM_OC3Init(TIM8, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
    TIM_OC4Init(TIM8, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1

//    TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
//    TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
    TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器

  	TIM_ARRPreloadConfig(TIM8,ENABLE);//ARPE使能
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
	TIM_Cmd(TIM8, ENABLE);  //使能TIM14

	TIM_SetCompare3(TIM8,0);
	TIM_SetCompare4(TIM8,0);
//    NVIC_InitStructure.NVIC_IRQChannel = TIM8_CC_IRQn ;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级0
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//    NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}

void bal_PWM_OUT(s16 pwm1,s16 pwm2)
{
	if(pwm1>800) pwm1=800;
	if(pwm1<-800) pwm1=-800;
	if(pwm2>800) pwm2=800;
	if(pwm2<-800) pwm2=-800;
	if(pwm1>0) 
	{
		PEout(12)=0;PEout(13)=1;//前
	}
	else{PEout(12)=1;PEout(13)=0;}
	if(pwm2>0) {PEout(14)=1;PEout(15)=0;}
	else{PEout(14)=0;PEout(15)=1;}
	TIM_SetCompare3(TIM8,GXT_abs(pwm1));
	TIM_SetCompare4(TIM8,GXT_abs(pwm2));
}





