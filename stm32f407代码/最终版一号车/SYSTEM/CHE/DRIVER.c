#include "DRIVER.h"

void CAR_Driver_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
	
	/*************************key************init*******/
//	NVIC_InitTypeDef NVIC_InitStructure;
//	EXTI_InitTypeDef EXTI_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);						 //使能SYSCFG时钟
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource10);
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource11);
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource12);
//	
//	/* 配置EXTI_Line2 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line10|EXTI_Line11|EXTI_Line12;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//中断事件
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//中断线使能
//	EXTI_Init(&EXTI_InitStructure);							//配置
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; //抢占优先级3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;		 //子优先级2
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 //使能外部中断通道
//	NVIC_Init(&NVIC_InitStructure);								 //配置
	
}



void CAR_KAIGUAN_INIT(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void RGB_EN(u8 a)
{
	switch(a)
	{
		case RED:RED_EN;GREEN_DIS;BLUE_DIS;break;
		case WHITE:RED_EN;GREEN_EN;BLUE_EN;break;
		case DARK:RED_DIS;GREEN_DIS;BLUE_DIS;break;
		case GREEN:RED_DIS;GREEN_EN;BLUE_DIS;break;
		case YELLOW:RED_EN;GREEN_EN;BLUE_DIS;break;
		case BLUE:RED_DIS;GREEN_EN;BLUE_DIS;break;
		case PURPLE:RED_EN;GREEN_DIS;BLUE_EN;break;
		case CYAN:RED_DIS;GREEN_EN;BLUE_EN;break;
		default:RED_DIS;GREEN_DIS;BLUE_DIS;
	}
}

