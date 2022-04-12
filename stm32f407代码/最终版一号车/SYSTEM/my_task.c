#include "my_task.h"
char sx[30]={0};

void mask_1000HZ(void)
{
    ;
}
void mask_500HZ(void)
{
    ;
}
void mask_200HZ(void)
{
	
}
void mask_100HZ(void)
{
		if(flag_go==1)
		{
			//CAR_SPEED_SET(200,200);
			CAR_xunji();
		}
		else
		{
			CAR_STOP();
		}
	;
}

void mask_50HZ(void)
{
	;
}
void mask_20HZ(void)
{
	//f(1,40,openmvdata[0],openmvdata[7],openmvdata[9],USART4_RX_BUF[6],USART4_RX_BUF[7],USART4_RX_BUF[8]);
	
}
void mask_10HZ(void)
{
	//f(1,Get_Adc_Average(ADC_Channel_5,10,1));
	//f(1,PDin(8),PDin(9),PDin(10),PDin(11),PDin(12),PDin(13),PDin(14));
//	int aaa=TIM5->CNT-30000;
//	TIM5->CNT = 30000;
//	f(1,flag_go,aaa);
}
void mask_5HZ(void)
{
	
}
void mask_2HZ(void)
{
	MY_LED_407_TOG;
    ;
}

void mask_1HZ(void)
{
	//f(1,1,2);
    ;
}




struct mask
{
    u16 HZ_1000;
    u16 HZ_500;
    u16 HZ_200;
    u16 HZ_100;
    u16 HZ_50;
    u16 HZ_20;
    u16 HZ_10;
    u16 HZ_5;
    u16 HZ_2;
    u16 HZ_1;
}MASK;

void my_task(void)
{
		static long long int system_time_l;
    mask_1000HZ();
    while(system_time==system_time_l)
		{
			//任务空闲实践代码区
			;
		}
		system_time_l=system_time;
	//delay_ms(1);
    MASK.HZ_500++;
    MASK.HZ_200++;
    MASK.HZ_100++;
    MASK.HZ_50++;
    MASK.HZ_20++;
    MASK.HZ_10++;
    MASK.HZ_5++;
    MASK.HZ_2++;
    MASK.HZ_1++;
    if(MASK.HZ_500==2)
    {
        MASK.HZ_500=0;
        mask_500HZ();
    }
    if(MASK.HZ_200==5)
    {
        MASK.HZ_200=0;
        mask_200HZ();
    }
    if(MASK.HZ_100==10)
    {
        MASK.HZ_100=0;
        mask_100HZ();
    }
    if(MASK.HZ_50==20)
    {
        MASK.HZ_50=0;
        mask_50HZ();
    }
    if(MASK.HZ_20==50)
    {
        MASK.HZ_20=0;
        mask_20HZ();
    }
    if(MASK.HZ_10==100)
    {
        MASK.HZ_10=0;
        mask_10HZ();
    }
    if(MASK.HZ_5==200)
    {
        MASK.HZ_5=0;
        mask_5HZ();
    }
    if(MASK.HZ_2==500)
    {
        MASK.HZ_2=0;
        mask_2HZ();
    }
    if(MASK.HZ_1==1000)
    {
        MASK.HZ_1=0;
        mask_1HZ();
    }
}

