#include "k210it.h"
int aaa,bbb;
int left_max,right_max;
u8 find_val1,find_val2,find_val3,find_val4,find_val5;
int val1_cnt,val2_cnt,val3_cnt,val4_cnt,val5_cnt;
u8 USART6_RX_BUF[100]={0};
void USART6_IRQHandler(void)
{
	uint8_t res;
	uint8_t clear = 0;
	static uint8_t Rx_Sta = 1;
	if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
	{
		res =USART6->DR;
		USART6_RX_BUF[Rx_Sta++] = res;
		//USART_SendData(USART1,res);
	}
	else if(USART_GetITStatus(USART6, USART_IT_IDLE) != RESET)
	{
		clear = USART6->SR;
		clear = USART6->DR;
		USART6_RX_BUF[0] = Rx_Sta - 1;
		Rx_Sta = 1;
		bbb++;
		ZSP_DEAL2();
	}
}



u8 USART5_RX_BUF[100]={0};
void UART5_IRQHandler(void)
{
	uint8_t res;
	uint8_t clear = 0;
	static uint8_t Rx_Sta = 1;
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
	{
		res =UART5->DR;
		USART5_RX_BUF[Rx_Sta++] = res;
		//USART_SendData(USART1,res);
	}
	else if(USART_GetITStatus(UART5, USART_IT_IDLE) != RESET)
	{
		clear = UART5->SR;
		clear = UART5->DR;
		USART5_RX_BUF[0] = Rx_Sta - 1;
		Rx_Sta = 1;
		aaa++;
		ZSP_DEAL1();
	}
}

u8 k210_left[10]={0};
u8 k210_right[10]={0};
u8 count_go=0;
int k210_cnt_l[9]={0};
int k210_cnt_r[9]={0};
void ZSP_DEAL1(void)//左 使用USART5_RX_BUF
{
	static u8 t=0;
	if(USART5_RX_BUF[0]==11&&USART5_RX_BUF[1]==0xAA&&USART5_RX_BUF[2]==0xFF&&USART5_RX_BUF[11]==0xcc)
		{
			k210_left[1]=USART5_RX_BUF[3];
			k210_left[2]=USART5_RX_BUF[4];
			k210_left[3]=USART5_RX_BUF[5];
			k210_left[4]=USART5_RX_BUF[6];
			k210_left[5]=USART5_RX_BUF[7];
			k210_left[6]=USART5_RX_BUF[8];
			k210_left[7]=USART5_RX_BUF[9];
			k210_left[8]=USART5_RX_BUF[10];
			
			if(count_go==1)
			{
				for(t=1;t<=8;t++)
				{
					if(k210_left[1]==1)  k210_cnt_l[1]++;
					if(k210_left[2]==1)  k210_cnt_l[2]++;
					if(k210_left[3]==1)  k210_cnt_l[3]++;
					if(k210_left[4]==1)  k210_cnt_l[4]++;
					if(k210_left[5]==1) 	k210_cnt_l[5]++;
					if(k210_left[6]==1)  k210_cnt_l[6]++;
					if(k210_left[7]==1)  k210_cnt_l[7]++;
					if(k210_left[8]==1) 	k210_cnt_l[8]++;
				}
			}
			else
				for(t=1;t<=8;t++) k210_cnt_l[t]=0;
		}
    else
		{
			for(int i=0;i<10;i++)
			{k210_left[i]=0;}
		}
}

void ZSP_DEAL2(void)//右 使用USART6_RX_BUF 
{
	static u8 t=0;
	if(USART6_RX_BUF[0]==11&&USART6_RX_BUF[1]==0xAA&&USART6_RX_BUF[2]==0xFF&&USART6_RX_BUF[11]==0xcc)
		{
			k210_right[1]=USART6_RX_BUF[3];
			k210_right[2]=USART6_RX_BUF[4];
			k210_right[3]=USART6_RX_BUF[5];
			k210_right[4]=USART6_RX_BUF[6];
			k210_right[5]=USART6_RX_BUF[7];
			k210_right[6]=USART6_RX_BUF[8];
			k210_right[7]=USART6_RX_BUF[9];
			k210_right[8]=USART6_RX_BUF[10];
			
			if(count_go==1)
			{
				for(t=1;t<=8;t++)
				{
					if(k210_right[1]==1)  k210_cnt_r[1]++;
					if(k210_right[2]==1)  k210_cnt_r[2]++;
					if(k210_right[3]==1)  k210_cnt_r[3]++;
					if(k210_right[4]==1)  k210_cnt_r[4]++;
					if(k210_right[5]==1) k210_cnt_r[5]++;
					if(k210_right[6]==1)  k210_cnt_r[6]++;
					if(k210_right[7]==1)  k210_cnt_r[7]++;
					if(k210_right[8]==1) k210_cnt_r[8]++;
				}
			}
			else
				for(t=1;t<=8;t++) k210_cnt_r[t]=0;
		}
    else
		{
			for(int i=0;i<10;i++)
			{k210_right[i]=0;}
		}
}

int find_max(u8 i)
{
	int max_val=0;
	u8 t=0;
	if(i==1)  {for(t=1;t<=8;t++) if(max_val<k210_cnt_l[t]) max_val=t;}
	else if(i==2) { for(t=1;t<=8;t++) if(max_val<k210_cnt_r[t]) max_val=t;}
	return max_val;
}



void find_MAX(u8 a)
{
	int i,max,second_max;
	u8 t1=0,t2=0;
	max = 0;
  second_max=0; 
	if(a==1)
	{
    for(i = 1 ; i <=8 ; i++)  
    {
        if(k210_cnt_l[i] > max)  
        {
            second_max = max;  
            max = k210_cnt_l[i];
            t1=i;
        }
        else
        {
					if(k210_cnt_l[i] > second_max)  
					{
						second_max = k210_cnt_l[i];  
							t2=i;
					}
        }
    }
		find_val1=t1;find_val2=t2;
		val1_cnt=max;val2_cnt=second_max;
	}
		else if(a==2)
	{
    for(i = 1 ; i <=8 ; i++)  
    {
        if(k210_cnt_r[i] > max)  
        {
            second_max = max;  
            max = k210_cnt_r[i];
            t1=i;
        }
        else
        {
					if(k210_cnt_r[i] > second_max)  
					{
						second_max = k210_cnt_r[i];  
							t2=i;
					}
        }
    }
		find_val3=t1;find_val4=t2;
		val3_cnt=max;val4_cnt=second_max;
	}
}