#include "sys.h"

long long int system_time=0;
char sss[20];
void JumpToBootloader(void);
int main(void)
{
	/*SYS INIT		NVIC_INIT	SYS--168M	TIM--84M*/
	NVIC_PriorityGroupConfig(2);
	delay_init(168);
	RCC_ClocksTypeDef get_rcc_clock;    //��ȡϵͳʱ��״̬
	RCC_GetClocksFreq(&get_rcc_clock);
	
	OLED_Init();//PE0,PE1
	sprintf(sss,"%d",get_rcc_clock.SYSCLK_Frequency);
	OLED_ShowString(0,0,sss,8);
	
	
	delay_ms(500);//��ֹ��������������������
	
	
	TIM6_INIT(999,83);//ϵͳ��ʼ��ʱ,������ȼ�
	TIM7_INIT(9999,83);
	KEY_Init();//�ӿ�����߶�ȡ��0�����ұ���1  PE2,PE3 PA15
	CAR_KAIGUAN_INIT();
//	__disable_irq();//�ȹر������ж�
//	__enable_irq();//���������ж�
	led_my_407();//PC13
	CAR_Driver_Init();
	PAout(4)=0;
	delay_ms(100);
	PAout(4)=1;
	
	
	
	MOTOR_PID();
	
	//Adc_Init();
	
	//CAR_init();
	
	
	ENCODER_2_INIT();

  ENCODER_3_INIT();
	//ENCODER_1_INIT();
//	bal_pid_val_init();
//	bal_IO_PWM_init(999,83);
	//ENCODER_3_INIT();
	maiche_init();
	


	RGB_EN(YELLOW);
	delay_ms(300);
	RGB_EN(BLUE);
	delay_ms(300);
	
	
	RGB_EN(DARK);
	
	tim8_init(999,83);//PC6,7,8,9  //pwm out
//  flb_pid_init();

	/*USART INITs
	USART1	PA9,PA10	IT-ENABLE(2,2)
	USART2	PA2,PA3		IT-ENABLE(1,1)*/
	usart_1_init(115200);//����������������500000
	//SBUS_Configuration();//USART2,����sbus����
	CAR_UART3_INIT(115200);//PD8,PD9
	CAR_UART4_INIT(115200);//PC10,PC11
	
	CAR_UART5_INIT(115200);
	CAR_UART6_INIT(115200);
	//usart_3_init(115200);
	
	/*
	������
	*/
	u8 tak1=0;
	u8 tak2=0;
	tak1=PEin(2);
	tak2=PEin(3);
	

	
	if(tak1==0&&tak2==0){car_task=1;}
	else if(tak1==1&&tak2==0){car_task=2;}
	else if(tak1==0&&tak2==1){car_task=3;}
	else if(tak1==1&&tak2==1){car_task=4;}
	sprintf(sss,"T-%d",car_task);
	OLED_ShowString(80,0,sss,8);
	if(car_task==1) TASK1_GO();
	else if(car_task==2) TASK2_GO();
	else if(car_task==3) TASK3_GO();
	while(1);
}
