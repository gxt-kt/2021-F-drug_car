#include "car_ctrl.h"
#include "car_uart2.h"
u8 openmv_num=0;
int detect_num=0;
u8 car_sta=0;
int sr04=0;
int vel;
float Kp_qwq = 0.1;


u8 board;


u8 ss1,ss2,ss3,ss4,ss5;
u8 car_stop=0;
int time_up=0;

int Speed = 33;
int Speed1; //右轮
int Speed2;	//左轮
void CAR_xunji(void)
{
	if(openmvdata[0])
	{
			int error = openmvdata[0] - 160;
			vel = error* Kp_qwq;
			if(vel>10) vel = 0;
			if(vel<-10) vel = -10;
			Speed1 = Speed + vel;
			Speed2 = Speed - vel;
			MOTOR_ANTI(Speed1,Speed2);
		
		//MOTOR_ANTI(0,0);
	}
	else if(openmvdata[0]==0&&black_num>=3)
	{
		if(return_sta==1) {
			delay_ms(200);
		RGB_EN(GREEN);
		CAR_STOP();while(1);
		}
		delay_ms(200);
		RGB_EN(RED);
		CAR_STOP();
		//delay_ms(1000);
		delay_ms(1000);
		while(1)
		{
			if(PAin(5)==1) {delay_ms(500);break;}
			delay_ms(50);
		}
		RGB_EN(DARK);
		MOTOR_ANTI(SD_180,-SD_180);
		delay_ms(ZW_180);
		CAR_STOP();
		if(return_sta==0) return_sta=1;
		else if(return_sta==1) {CAR_STOP();while(1);}
	}
	else
	{
		MOTOR_ANTI(30,30);
	}
}


void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)==1) //溢出中断
	{
		TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  //清除中断标志位
		static int ttt;
		static int ttt_20hz;
		if(ttt>=50){ttt=0;MY_LED_407_TOG;}
		ttt++;
		static u8 a=0;
		if(a==0) SPEED_GET();
		a=!a;
		
		if(ttt_20hz>=5){ttt_20hz=0;
			
		//f(1,Speed1,Speed2,openmvdata[0],openmvdata[7],openmvdata[9],black_num);
			//if(flag_go==0) PEout(7)=0;
		}
		ttt_20hz++;
		
	}
}
