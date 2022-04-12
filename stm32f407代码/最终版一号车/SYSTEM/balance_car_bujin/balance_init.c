#include "balance_init.h"



void balance_init_tim8(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//使能PORTF时钟	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTF时钟	

  GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8); 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_9;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;        //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //初始化PF9
	
	TIM_TimeBaseStructure.TIM_Prescaler=12;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=65535;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);//初始化定时器14
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle; //选择定时器模式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_CounterMode_Up; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
  TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Disable);//失能TIMx在CCR1上的预装载寄存器
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Disable);//失能TIMx在CCR2上的预装载寄存器
  TIM_Cmd(TIM8, ENABLE);                            //使能TIM4
  TIM_ITConfig(TIM8, TIM_IT_CC2|TIM_IT_CC4 , ENABLE);
	TIM_ARRPreloadConfig(TIM8,ENABLE);//ARPE使能
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
  NVIC_InitStructure.NVIC_IRQChannel = TIM8_CC_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
//	//初始化TIM14 Channel1 PWM模式	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低

//  TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
//  TIM_OC4Init(TIM8, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1


//  TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
//	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器

//  TIM_ARRPreloadConfig(TIM8,ENABLE);//ARPE使能
//	TIM_CtrlPWMOutputs(TIM8, ENABLE);
//	TIM_Cmd(TIM8, ENABLE);  //使能TIM14
//	TIM_SetCompare2(TIM8,0);
//	TIM_SetCompare4(TIM8,0);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_8;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;        //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //初始化PF9
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PF9
	PBout(10)=1;
	PBout(11)=1;
}

void TIM8_CC_IRQHandler(void)
{
	 float Capture1,Capture2;
   if(TIM_GetITStatus(TIM8,TIM_IT_CC2)!=RESET)
	 {
	  TIM_ClearITPendingBit(TIM8, TIM_IT_CC2 );//清除TIMx的中断待处理位
    Capture1 = TIM_GetCapture2(TIM8);
    TIM_SetCompare2(TIM8, Capture1 + Final_Moto1 );//设置TIMx自动重装载寄存器值
	 }
	 if(TIM_GetITStatus(TIM8,TIM_IT_CC4)!=RESET)
	 {
	  TIM_ClearITPendingBit(TIM8, TIM_IT_CC4 );//清除TIMx的中断待处理位
    Capture2 = TIM_GetCapture4(TIM8);
    TIM_SetCompare4(TIM8, Capture2 + Final_Moto2 );//拿示波器加计算，至少要加184*2才能保证13khz 最大先用120000试下
		 //越大电机频率越低，电机转的越慢
	 }
}
