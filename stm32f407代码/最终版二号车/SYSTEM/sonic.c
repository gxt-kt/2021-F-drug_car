#include "sonic.h"

void TIM5_sonic_init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef  ICInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA0
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA7

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //PA0����λ��ʱ��5
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);
		 
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	

	//��ʼ��TIM5���벶�����
	ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM5, &ICInitStructure);
	ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM5, &ICInitStructure);
	
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//���������ж� ,����CC1IE�����ж�	
	TIM_ITConfig(TIM5,TIM_IT_CC2,ENABLE);
  TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5

  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}

void TIM5_IRQHandler(void)//10usһ���ж�
{
	static u32 tim5_t;
	static s8 tim5_capture1_val;
	static u8 tim5_s_1;
	static u32 tim5_cnt_1;
	static s8 tim5_capture2_val;
	static u8 tim5_s_2;
	static u32 tim5_cnt_2;
	
	if(TIM_GetITStatus(TIM5,TIM_FLAG_Update)==1)
	{
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
		tim5_t++;
		if(tim5_t==100000)
		{
			//LED0_TOG;
			//LED1_TOG;
			tim5_t=0;
			//f(2,0,tim5_cnt_1);
		}
		
		if(tim5_s_1==0) tim5_cnt_1=0;
		else  tim5_cnt_1++;
		if(tim5_s_2==0) tim5_cnt_2=0;
		else  tim5_cnt_2++;
	}
	
	if(TIM_GetITStatus(TIM5,TIM_FLAG_CC1)==1)
	{
		TIM_ClearFlag(TIM5,TIM_FLAG_CC1);
		TIM_ClearITPendingBit(TIM5,TIM_FLAG_CC1);
		if(tim5_s_1==0)//��ʼ����
		{
			LED0_TOG;
			tim5_s_1=1;
			tim5_capture1_val=TIM_GetCapture1(TIM5);
			//f(2,tim5_capture1_val);
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);//����Ϊ�½���
		}
		else//�������
		{
			LED0_TOG;
			tim5_s_1=0;
			tim5_capture1_val=TIM_GetCapture1(TIM5)-tim5_capture1_val;
			f(1,(tim5_cnt_1*10+tim5_capture1_val)*340/10000,tim5_capture1_val);
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);
		}
	}
	
	if(TIM_GetITStatus(TIM5,TIM_FLAG_CC2)==1)
	{
		TIM_ClearFlag(TIM5,TIM_FLAG_CC2);
		if(tim5_s_2==0)//��ʼ����
		{
			//LED0_TOG;
			tim5_s_2=1;
			tim5_capture2_val=TIM_GetCapture2(TIM5);
			TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Falling);//����Ϊ�½���
		}
		else//�������
		{
			//LED0_TOG;
			tim5_s_2=0;
			tim5_capture2_val=TIM_GetCapture2(TIM5)-tim5_capture2_val;
			f(2,(tim5_cnt_2*10+tim5_capture2_val)*340/10000,tim5_capture2_val);
			TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Rising);
		}
	}
}

