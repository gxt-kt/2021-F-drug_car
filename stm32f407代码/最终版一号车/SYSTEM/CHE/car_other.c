#include "car_other.h"

int SPEED_1=0;
int SPEED_2=0;
void SPEED_GET(void)
{
	SPEED_1=TIM4->CNT-30000;
	TIM4->CNT=30000;
	SPEED_2=30000-TIM5->CNT;
	TIM5->CNT=30000;
}





void CAR_TURN_LEFT(void)
{
	CAR_SPEED_SET(-SPEED,SPEED);
	delay_ms(DELAY_TIME);
}
void CAR_TURN_RIGHT(void)
{
	CAR_SPEED_SET(SPEED,-SPEED);
	delay_ms(DELAY_TIME);
}

 void CAR_SPEED_SET(int left,int right)
{
	if(left>0&&right>0) CAR_back();
	else if(left<0&&right<0) CAR_front();
	else if(left<0&&right>0) CAR_left();
	else if(left>0&&right<0) CAR_right();
	else CAR_STOP();
	
//	TIM_SetCompare1(TIM8,MY_abs(right));
//	TIM_SetCompare2(TIM8,MY_abs(left));
	TIM_SetCompare3(TIM8,MY_abs(left));
	TIM_SetCompare4(TIM8,MY_abs(right));
}

void CAR_front(void)
{
	PEout(7)=1;//ENABLE
	PEout(8)=0;
	PEout(9)=1;
	PEout(10)=1;
	PEout(11)=0;
	PEout(12)=0;
	PEout(13)=1;
	PEout(14)=1;
	PEout(15)=0;
}
void CAR_back(void)
{
	PEout(7)=1;//ENABLE
	PEout(8)=1;
	PEout(9)=0;
	PEout(10)=0;
	PEout(11)=1;
	PEout(12)=1;
	PEout(13)=0;
	PEout(14)=0;
	PEout(15)=1;
}
void CAR_left(void)
{
	PEout(7)=1;//ENABLE
	PEout(8)=0;
	PEout(9)=1;
	PEout(10)=0;
	PEout(11)=1;
	PEout(12)=0;
	PEout(13)=1;
	PEout(14)=0;
	PEout(15)=1;
}
void CAR_right(void)
{
	PEout(7)=1;//ENABLE
	PEout(8)=1;
	PEout(9)=0;
	PEout(10)=1;
	PEout(11)=0;
	PEout(12)=1;
	PEout(13)=0;
	PEout(14)=1;
	PEout(15)=0;
}
int MY_abs(int a)
{
	return a>0?a:(-a);
}
void CAR_STOP(void)
{
	PEout(7)=0;//ENABLE
	PEout(8)=0;
	PEout(9)=0;
	PEout(10)=0;
	PEout(11)=0;
	PEout(12)=0;
	PEout(13)=0;
	PEout(14)=0;
	PEout(15)=0;
	TIM_SetCompare1(TIM8,0);
	TIM_SetCompare2(TIM8,0);
	TIM_SetCompare3(TIM8,0);
	TIM_SetCompare4(TIM8,0);
}
