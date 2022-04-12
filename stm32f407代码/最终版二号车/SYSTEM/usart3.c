#include "usart3.h"
void usart_3_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART1时钟
	
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_USART3); 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_USART3); 
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure); //初始化PA9，PA10

  //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART3, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART3, ENABLE);  //使能串口1 	
	
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启相关中断
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//开启相关中断
}




//u8 USART3_RX_BUF[100]={0};
//void USART3_IRQHandler(void)
//{
//	uint8_t res;
//	uint8_t clear = 0;
//	static uint8_t Rx_Sta = 1;
//	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
//	{
//		res =USART3->DR;
//		USART3_RX_BUF[Rx_Sta++] = res;
//		//USART_SendData(USART1,res);
//		//qt_date_deal(res);
//	}
//	else if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
//	{
//		clear = USART3->SR;
//		clear = USART3->DR;
//		USART3_RX_BUF[0] = Rx_Sta - 1;
//		Rx_Sta = 1;
//		GXT_DATA_DEAL();
//	}
//}


//int16_t gy25_pitch=0;
//int16_t gy25_roll=0;
//int16_t gy25_yaw=0;

//u8 openmv_zsp_0=0;
//s16 openmv_zsp_1=0;
//s16 openmv_zsp_2=0;

//float u3_Roll;
//float u3_Pitch;
//float u3_Yaw;
//s32 u3_geti=0;
//void GXT_DATA_DEAL(void)
//{
//	u8 sum=0;
//	u8 i=23;
//	if(USART3_RX_BUF[0]==33&&USART3_RX_BUF[23]==0x55&&USART3_RX_BUF[24]==0x53)
//	{
//		for(;i<33;i++)
//		{
//			sum+=USART3_RX_BUF[i];
//		}
//		if(sum==USART3_RX_BUF[i])
//		{
//			u3_geti++;
//			u3_Roll = (float) ( (int16_t) (USART3_RX_BUF[26]<<8) | USART3_RX_BUF[25] ) / 32768 * 180+0.55;
//			u3_Pitch = (float) ( (int16_t) (USART3_RX_BUF[28]<<8) | USART3_RX_BUF[27] ) / 32768 * 180-0.6;
//			u3_Yaw = (float) ( (int16_t) (USART3_RX_BUF[30]<<8) | USART3_RX_BUF[29] ) / 32768 * 180;
//			static float flb_roll_last;
//			x_sp_val=x_sp_filter(u3_Roll-flb_roll_last);
//			flb_roll_last=u3_Roll;
//			static float flb_pitch_last;
//			y_sp_val=y_sp_filter(u3_Pitch-flb_pitch_last);
//			flb_pitch_last=u3_Pitch;
//		}
//	}  
////	{
////		u3_Roll=1;
////	}
////	else u3_Roll=0;
//}
////		if(USART3_RX_BUF[1]==0xBB&&USART3_RX_BUF[2]==0xEE&&USART3_RX_BUF[3]==0x11)
////	{
////		if(USART3_RX_BUF[5]==1)
////		{
////			openmv_zsp_0=USART3_RX_BUF[5];
////			if(USART3_RX_BUF[8]==1)
////				openmv_zsp_1=USART3_RX_BUF[9];
////			if(USART3_RX_BUF[8]==0)
////				openmv_zsp_1=-USART3_RX_BUF[9];
//////			openmv_zsp_1+=13;
////			if(USART3_RX_BUF[12]==1)
////				openmv_zsp_2=USART3_RX_BUF[13];
////			if(USART3_RX_BUF[12]==0)
////				openmv_zsp_2=-USART3_RX_BUF[13];
////			//openmv_zsp_2-=13;
////		}
////    else
////		{
////			openmv_zsp_0=0;
////			openmv_zsp_1=0;
////			openmv_zsp_2=0;
////		}
////	}
//	


////		if(USART3_RX_BUF[0]==11&&USART3_RX_BUF[1]==0x55&&USART3_RX_BUF[2]==0x55)
////	{
////		
////		u8 u3_sum=0;
////		u8 i;
////		for (i=1;i<11;i++)
////		{
////			u3_sum+=USART3_RX_BUF[i];
////		}
////		if(USART3_RX_BUF[i]==u3_sum)
////		{
////			u3_Roll = (float) ( (int16_t) (USART3_RX_BUF[6]<<8) | USART3_RX_BUF[5] ) / 32768 * 180+0.5-machine_zz;
////			u3_Pitch = (float) ( (int16_t) (USART3_RX_BUF[8]<<8) | USART3_RX_BUF[7] ) / 32768 * 180;
////			u3_Yaw = (float) ( (int16_t) (USART3_RX_BUF[10]<<8) | USART3_RX_BUF[9] ) / 32768 * 180;
////			static float flb_roll_last;
////			x_sp_val=x_sp_filter(u3_Roll-flb_roll_last);
////			flb_roll_last=u3_Roll;
////			static float flb_pitch_last;
////			y_sp_val=y_sp_filter(u3_Pitch-flb_pitch_last);
////			flb_pitch_last=u3_Pitch;
////		}
////	}
////		if(USART3_RX_BUF[0]==11&&USART3_RX_BUF[1]==0x55&&USART3_RX_BUF[2]==0x53)
////	{
////		u8 u3_sum=0;
////		u8 i;
//////		for (i=1;i<11;i++)
//////		{
//////			u3_sum+=USART3_RX_BUF[i];
//////		}
//////		if(USART3_RX_BUF[i]==u3_sum)
//////		{
////			u3_Roll = (float) ( (int16_t) (USART3_RX_BUF[4]<<8) | USART3_RX_BUF[3] ) / 32768 * 180;
////			u3_Pitch = (float) ( (int16_t) (USART3_RX_BUF[6]<<8) | USART3_RX_BUF[5] ) / 32768 * 180;
////			u3_Yaw = (float) ( (int16_t) (USART3_RX_BUF[8]<<8) | USART3_RX_BUF[7] ) / 32768 * 180;
////			static float flb_roll_last;
////			x_sp_val=x_sp_filter(u3_Roll-flb_roll_last);
////			flb_roll_last=u3_Roll;
////			static float flb_pitch_last;
////			y_sp_val=y_sp_filter(u3_Pitch-flb_pitch_last);
////			flb_pitch_last=u3_Pitch;
//////		}
////	}
//#define u3_rec_num 11
//u8 u3_rec_array[u3_rec_num];
//void qt_date_deal(u8 data)
//{ 
//	static u8 i=0;
//	static u8 u3_rx_sta;
//	u8 sc=0;
//	u8 ac=0;
//	if(u3_rx_sta==0)
//	{
//		if(data==0x55) {u3_rx_sta=1;u3_rec_array[0]=0x55;}
//		else
//		{u3_rx_sta=0;}
//	}
//	else if(u3_rx_sta==1)
//	{
//		if(data==0x53) {u3_rx_sta=2;u3_rec_array[1]=0x53;i=2;}
//		else
//		{u3_rx_sta=0;}
//	}
//	else if(u3_rx_sta==2)
//	{
//		if(i<(u3_rec_num-1))
//		{u3_rec_array[i++]=data;if(i>=u3_rec_num-1) u3_rx_sta=3;}
//	}
//	else if(u3_rx_sta==3)
//	{
//		/*u3_rec_array[]
//		*/
//		for(i=0;i<u3_rec_num;i++)
//		{ sc+=u3_rec_array[i];} //和校验
//		
//		 if(sc==u3_rec_array[i])
//		{	
//			u3_rx_sta=0;
//			i=0;
//			
//			/*处理-begin*/
//			u3_Roll =((short)(USART3_RX_BUF[3]<<8| USART3_RX_BUF[2]))/32768.0*180;
//			u3_Pitch = ((USART3_RX_BUF[5]<<8) | USART3_RX_BUF[4] ) / 32768 * 180;
//			u3_Yaw =((USART3_RX_BUF[7]<<8) | USART3_RX_BUF[6] ) / 32768 * 180;
//			static float flb_roll_last;
//			x_sp_val=x_sp_filter(u3_Roll-flb_roll_last);
//			flb_roll_last=u3_Roll;
//			static float flb_pitch_last;
//			y_sp_val=y_sp_filter(u3_Pitch-flb_pitch_last);
//			flb_pitch_last=u3_Pitch;

//			/*处理-end*/
//		}
//		else{u3_rx_sta=0;
//			 i=0;
//		    }
//		
//	}
//	else
//	{
//		i=0;
//		u3_rx_sta=0;
//	}
//}

