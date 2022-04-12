#include "ctrl_num.h"

u8 return_sta=0;
u8 car_task=0;
u8 sta_num[10]={0};
u8 sta_i=1;

//每次碰到边界记住是做法是转弯还是直走，
/*
回来的时候根据去的数组反方向走


*/

u8 u2_send[20]={0xaa,0xff,0,0,0,0,0,0,0,0,0xcc};

void U2_DATA_DEAL(void)
{
	if(USART2_RX_BUF[0]==11&&USART2_RX_BUF[1]==0XAA&&USART2_RX_BUF[2]==0XFF&&USART2_RX_BUF[11]==0XCC)
	{
		
	}
}

void UART2_Send_Str(u8 *s,u8 cnt_s)//发送字符串 函数   应用指针 方法
{
	u8 i;
	for(i=0;i<cnt_s;i++)
	{
		USART_SendData(USART2,s[i]);
		while( USART_GetFlagStatus(USART2,USART_FLAG_TXE)!= SET);
	}
}

