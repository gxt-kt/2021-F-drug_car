#include "ws2812.h"
//用法示例，先保存到数组，用 ws2812_rgb函数，然后用ws2812_refresh函数发送 
// ws2812_rgb(1, WS_RED);
// ws2812_rgb(2, WS_GREEN);
// ws2812_rgb(3, WS_BLUE);
// ws2812_rgb(4, WS_WHITE);
// ws2812_rgb(5, WS_PURPLE);
// ws2812_rgb(6, WS_YELLO);
// ws2812_rgb(7, WS_DARK);
// ws2812_rgb(8, WS_BLUE);
// ws2812_refresh(8);

void ws2812_init(void)//PE4
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOE,GPIO_Pin_4);
}


u8 ws_data[200]={0};
void ws2812_rgb(u8 ws_i,u8 ws_r,u8 ws_g,u8 ws_b)	
{
	ws_data[(ws_i-1)*3]=ws_g;
	ws_data[(ws_i-1)*3+1]=ws_r;
	ws_data[(ws_i-1)*3+2]=ws_b;
}
void ws2812_rgb_all(u8 ws_i,u8 ws_r,u8 ws_g,u8 ws_b)	
{
	static u8 rgb_wsi;
	for(rgb_wsi=1;rgb_wsi<=ws_i;rgb_wsi++)
	{
		ws_data[(rgb_wsi-1)*3]=ws_g;
		ws_data[(rgb_wsi-1)*3+1]=ws_r;
		ws_data[(rgb_wsi-1)*3+2]=ws_b;
	}
}

void ws2812_refresh(u8 ws_i)
{
	u8 ws_ri=0;
	for(;ws_ri<ws_i*3;ws_ri++)
	{
		if((ws_data[ws_ri]&0x80)==0)	send_0();	else send_1();
		if((ws_data[ws_ri]&0x40)==0)	send_0();	else send_1();
		if((ws_data[ws_ri]&0x20)==0)	send_0();	else send_1();
		if((ws_data[ws_ri]&0x10)==0)	send_0();	else send_1();
		if((ws_data[ws_ri]&0x08)==0)	send_0();	else send_1();
		if((ws_data[ws_ri]&0x04)==0)	send_0();	else send_1();
		if((ws_data[ws_ri]&0x02)==0)	send_0();	else send_1();
		if((ws_data[ws_ri]&0x01)==0)	send_0();	else send_1();
	}
	send_res();
}

void ws2812_reset(u8 ws_set)
{
	for(int i=0;i<200;i++)
	{
		ws_data[i]=ws_set;
	}
}

void delay_250ns(void)
{
	u8 del_t=WS_TIMES;
	while(del_t--)
		__NOP();
}

void send_0(void)
{
	TH;
	delay_250ns();
	TL;
	delay_250ns();
	delay_250ns();
	delay_250ns();
	delay_250ns();
}
void send_1(void)
{
	TH;
	delay_250ns();
	delay_250ns();
	delay_250ns();
	delay_250ns();
	TL;
	delay_250ns();
}
void send_res(void)
{
	TL;
	delay_us(300);
}

