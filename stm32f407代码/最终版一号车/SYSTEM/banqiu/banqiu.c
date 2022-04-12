#include "banqiu.h"
#define duty_min (900)
#define duty_max (2100)
#define duty_midx (1600)
#define duty_midy (1450)
s16 pwm_out1=duty_midy;
s16 pwm_out2=duty_midx;
s16 x_val=0;
s16 y_val=0;
s16 wucha=0;
s16 wucha_y=0;
s16 gxt_su[10]={0};
s16 gxt_su_y[10]={0};
PID_wz banqiu_x;
PID_wz banqiu_su_x;
PID_wz banqiu_su_y;
PID_wz banqiu_y;

float myabs(float a)
{	
	return a>0?a:(-a);
}
void banqiu_pid_init(void)
{    
	banqiu_x.kp=-0.05;
	banqiu_x.ki=0;
	banqiu_x.kd=-0.015;
	banqiu_x.limit_up=600;
	banqiu_x.limit_dn=-600;
	banqiu_x.itl_lim_up=10000;
	banqiu_x.itl_lim_dn=-10000; 
	banqiu_y.kp=banqiu_x.kp;
	banqiu_y.ki=banqiu_x.ki;
	banqiu_y.kd=banqiu_x.kd;
	banqiu_y.limit_up=600;
	banqiu_y.limit_dn=-600;
	banqiu_y.itl_lim_up=10000;
	banqiu_y.itl_lim_dn=-10000;
	
	
	banqiu_su_x.kp=50;
	banqiu_su_x.ki=0;
	banqiu_su_x.kd=12;
	banqiu_su_y.kp=banqiu_su_x.kp;
	banqiu_su_y.ki=0;
	banqiu_su_y.kd=banqiu_su_x.kd;
	
	
	
}
void banqiu_control(s16 pid_now_x,s16 pid_anti_x,s16 pid_now_y,s16 pid_anti_y)//50hz
{
	static int i;
	static int sum_y;
	static int sum;
	s16 banqiu_su_x_fake;
	s16 banqiu_su_y_fake;
	banqiu_x.err =pid_anti_x-pid_now_x; // ���㵱ǰ���
	if(1) //������������
	{banqiu_x.integral += banqiu_x.err;      //���ƫ��Ļ���
	if(1)//���������޷�
		{if(banqiu_x.integral >= banqiu_x.itl_lim_up){banqiu_x.integral =  banqiu_x.itl_lim_up;}//�����޷�
		else if(banqiu_x.integral <= banqiu_x.itl_lim_dn){banqiu_x.integral =  banqiu_x.itl_lim_dn;}}
	}
		else banqiu_x.integral=0;//���������֣�����ֵΪ0
	if(myabs(banqiu_x.err)<10)
	{	
		banqiu_x.integral=0;
	}
	banqiu_x.dif=banqiu_x.err-banqiu_x.err_last;
	banqiu_x.out = banqiu_x.kp*banqiu_x.err + banqiu_x.ki*banqiu_x.integral + banqiu_x.kd*banqiu_x.dif;   //λ��ʽPID������
	banqiu_x.err_last = banqiu_x.err;   //������һ��ƫ�� 
	
	if(0){//�Ƿ�����޷�
	if(banqiu_x.out >= banqiu_x.limit_up){banqiu_x.out =  banqiu_x.limit_up;}//����޷�
	else if(banqiu_x.out <= banqiu_x.limit_dn){banqiu_x.out =  banqiu_x.limit_dn;}}
	/***************************************************************************/
	/***************************************************************************/
	/***************************************************************************/
	banqiu_su_x_fake =banqiu_x.dif;
	for(i=0;i<4;i++)
	{
		gxt_su[i]=gxt_su[i+1];
	}
	gxt_su[4]=banqiu_su_x_fake;
	sum=0;
	for(i=0;i<5;i++)
	{
		sum+=gxt_su[i];
	}
	wucha=(int)(sum/5);
	banqiu_su_x.err=banqiu_x.out-wucha;
	if(0) //������������
	{banqiu_su_x.integral += banqiu_su_x.err;      //���ƫ��Ļ���
	if(0)//���������޷�
		{if(banqiu_su_x.integral >= banqiu_su_x.itl_lim_up){banqiu_su_x.integral =  banqiu_su_x.itl_lim_up;}//�����޷�
		else if(banqiu_su_x.integral <= banqiu_su_x.itl_lim_dn){banqiu_su_x.integral =  banqiu_su_x.itl_lim_dn;}}
	}
		else banqiu_su_x.integral=0;//���������֣�����ֵΪ0
	
	banqiu_su_x.dif=banqiu_su_x.err-banqiu_su_x.err_last;
	banqiu_su_x.out = banqiu_su_x.kp*banqiu_su_x.err + banqiu_su_x.ki*banqiu_su_x.integral + banqiu_su_x.kd*banqiu_su_x.dif;   //λ��ʽPID������
	banqiu_su_x.err_last = banqiu_su_x.err;   //������һ��ƫ�� 
	
	if(0){//�Ƿ�����޷�
	if(banqiu_su_x.out >= banqiu_su_x.limit_up){banqiu_su_x.out =  banqiu_su_x.limit_up;}//����޷�
	else if(banqiu_su_x.out <= banqiu_su_x.limit_dn){banqiu_su_x.out =  banqiu_su_x.limit_dn;}}
	/***************************************************************************/
	/***************************************************************************/
	/***************************************************************************/
	/***************************************************************************/
	/***************************************************************************/
	/***************************************************************************/
	banqiu_y.err =pid_anti_y-pid_now_y; // ���㵱ǰ���
	if(1) //������������
	{banqiu_y.integral += banqiu_y.err;      //���ƫ��Ļ���
	if(1)//���������޷�
		{if(banqiu_y.integral >= banqiu_y.itl_lim_up){banqiu_y.integral =  banqiu_y.itl_lim_up;}//�����޷�
		else if(banqiu_y.integral <= banqiu_y.itl_lim_dn){banqiu_y.integral =  banqiu_y.itl_lim_dn;}}
	}
		else banqiu_y.integral=0;//���������֣�����ֵΪ0
	if(myabs(banqiu_y.err)<10)
	{
		banqiu_x.integral=0;
	}
	banqiu_y.dif=banqiu_y.err-banqiu_y.err_last;
	banqiu_y.out = banqiu_y.kp*banqiu_y.err + banqiu_y.ki*banqiu_y.integral + banqiu_y.kd*banqiu_y.dif;   //λ��ʽPID������
	banqiu_y.err_last = banqiu_y.err;   //������һ��ƫ�� 
	
	if(0){//�Ƿ�����޷�
	if(banqiu_y.out >= banqiu_y.limit_up){banqiu_y.out =  banqiu_y.limit_up;}//����޷�
	else if(banqiu_y.out <= banqiu_y.limit_dn){banqiu_y.out =  banqiu_y.limit_dn;}}
	
	/***************************************************************************/
	/***************************************************************************/
	/***************************************************************************/
	
	banqiu_su_y_fake =banqiu_y.dif;
	for(i=0;i<4;i++)
	{
		gxt_su_y[i]=gxt_su_y[i+1];
	}
	gxt_su_y[4]=banqiu_su_y_fake;
	sum_y=0;
	for(i=0;i<5;i++)
	{
		sum_y+=gxt_su_y[i];
	}
	wucha_y=(int)(sum_y/5);
	banqiu_su_y.err=banqiu_y.out-wucha_y;
	if(0) //������������
	{banqiu_su_y.integral += banqiu_su_y.err;      //���ƫ��Ļ���
	if(0)//���������޷�
		{if(banqiu_su_y.integral >= banqiu_su_y.itl_lim_up){banqiu_su_y.integral =  banqiu_su_y.itl_lim_up;}//�����޷�
		else if(banqiu_su_y.integral <= banqiu_su_y.itl_lim_dn){banqiu_su_y.integral =  banqiu_su_y.itl_lim_dn;}}
	}
		else banqiu_su_y.integral=0;//���������֣�����ֵΪ0
	
	banqiu_su_y.dif=banqiu_su_y.err-banqiu_su_y.err_last;
	banqiu_su_y.out = banqiu_su_y.kp*banqiu_su_y.err + banqiu_su_y.ki*banqiu_su_y.integral + banqiu_su_y.kd*banqiu_su_y.dif;   //λ��ʽPID������
	banqiu_su_y.err_last = banqiu_su_y.err;   //������һ��ƫ�� 
	
	if(0){//�Ƿ�����޷�
	if(banqiu_su_y.out >= banqiu_su_y.limit_up){banqiu_su_y.out =  banqiu_su_y.limit_up;}//����޷�
	else if(banqiu_su_y.out <= banqiu_su_y.limit_dn){banqiu_su_y.out =  banqiu_su_y.limit_dn;}}
	/***************************************************************************/
	/***************************************************************************/
	/***************************************************************************/
	pwm_out1=duty_midy+(int)banqiu_su_y.out;
	pwm_out2=duty_midx+(int)banqiu_su_x.out;
	if(pwm_out1>duty_max) pwm_out1=duty_max;
	if(pwm_out1<duty_min) pwm_out1=duty_min;
	if(pwm_out2>duty_max) pwm_out2=duty_max;
	if(pwm_out2<duty_min) pwm_out2=duty_min;
	TIM_SetCompare1(TIM8,pwm_out1);
	TIM_SetCompare2(TIM8,pwm_out2);
}



void  banqiu_init(u32 arr,u32 psc)
{    
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//ʹ��PORTFʱ��	
	
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;        //����
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //��ʼ��PF9
	
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
	
	//��ʼ��TIM14 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
  TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
  TIM_OC3Init(TIM8, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
  TIM_OC4Init(TIM8, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

  TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
  TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
  TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���

  TIM_ARRPreloadConfig(TIM8,ENABLE);//ARPEʹ��
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
	TIM_Cmd(TIM8, ENABLE);  //ʹ��TIM14
	TIM_SetCompare1(TIM8,duty_midy);
	TIM_SetCompare2(TIM8,duty_midx);
	TIM_SetCompare3(TIM8,1500);
	TIM_SetCompare4(TIM8,1500);
}	


