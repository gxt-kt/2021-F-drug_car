#include "car_uart2.h"

u8 USART3_RX_BUF[100]={0};
void USART3_IRQHandler(void)
{
	uint8_t res;
	uint8_t clear = 0;
	static uint8_t Rx_Sta = 1;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		res =USART3->DR;
		USART3_RX_BUF[Rx_Sta++] = res;
		//USART_SendData(USART1,res);
	}
	else if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
	{
		clear = USART3->SR;
		clear = USART3->DR;
		USART3_RX_BUF[0] = Rx_Sta - 1;
		Rx_Sta = 1;
		GXT_DATA_DEAL();
	}
}

void GXT_DATA_DEAL(void)
{
	;
}
u8 zuo1,you1;
int openmvdata[10];//中x,中y,北x,北y,南x,南y,东x,东y,西x,西y
u8 black_num;
u8 USART4_RX_BUF[100]={0};
void UART4_IRQHandler(void)
{
	uint8_t res;
	uint8_t clear = 0;
	static uint8_t Rx_Sta = 1;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		res =UART4->DR;
		USART4_RX_BUF[Rx_Sta++] = res;
		//USART_SendData(USART1,res);
	}
	else if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)
	{
		clear = UART4->SR;
		clear = UART4->DR;
		USART4_RX_BUF[0] = Rx_Sta - 1;
		Rx_Sta = 1;

		if(USART4_RX_BUF[0]==11&&USART4_RX_BUF[1]==0xAA&&USART4_RX_BUF[2]==0xFF)
	{
			openmvdata[0] = ((s8)USART4_RX_BUF[3]<<8)|USART4_RX_BUF[4];
			openmvdata[7] = ((s8)USART4_RX_BUF[5]<<8)|USART4_RX_BUF[6];
			openmvdata[9] = ((s8)USART4_RX_BUF[7]<<8)|USART4_RX_BUF[8];
			black_num = USART4_RX_BUF[9];
			if(openmvdata[0]>320||openmvdata[0]<0) openmvdata[0]=160;
		
			if(board==0&&ttt==0)
			{
				if(openmvdata[7]>120) zuo1++;
				else zuo1=0;
				if(zuo1>=8)
					{
				detect_board();}
				}
				if(openmvdata[9]>120) you1++;
				else you1=0;
				if(you1>=8)
					{detect_board();
						
				}
			}else
			{zuo1=0;you1=0;}
		}
}

void detect_board(void)
{
	if(detect_num==1||detect_num==2){board=1;time_up=210;}
	else {board=1;time_up=210;}
}