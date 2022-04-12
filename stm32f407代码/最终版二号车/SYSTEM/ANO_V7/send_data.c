#include "send_data.h"
/*
GXT
适用于匿名上位机V7版本
函数使用方法，f()
第一个参数是通道值，缺省是1
后面为0~10个目标值，int格式，缺省是0

Send_Quaternion(q0*10000,q1*10000,q2*10000,q3*10000,1);//传输四元数
Send_LP_QY_TEMP(ak8975_data.magX,ak8975_data.magY,ak8975_data.magZ,spl06_data.baro_height/10,spl06_data.temperature*100,1,1);
Send_AX_GY(icm20602_data.accX,icm20602_data.accY,icm20602_data.accZ,icm20602_data.gyroX,icm20602_data.gyroY,icm20602_data.gyroZ,0);

//气压计数据解读 //20ms一次
spl06_data.temperature = user_spl0601_get_temperature();
spl06_data.presure = user_spl0601_get_presure();			 
spl06_data.baro_height = (uint32_t)((102000.0f	- spl06_data.presure) * 78.740f);  //每1mpar平均海拔高度为78.740mm
//磁力计数据解读 //20ms一次
AK8975_Updata(&ak8975_data);


*/


//使用这个函数可以使用默认参数
void var_f(f_args in)
{
u8 chx_out =in.gxt_chx? in.gxt_chx:1;
s32 a_out =in.gxt_a? in.gxt_a:0;
s32 b_out =in.gxt_b? in.gxt_b:0;
s32 c_out =in.gxt_c? in.gxt_c:0;
s32 d_out =in.gxt_d? in.gxt_d:0;
s32 e_out =in.gxt_e? in.gxt_e:0;
s32 f_out =in.gxt_f? in.gxt_f:0;
s32 g_out =in.gxt_g? in.gxt_g:0;
s32 h_out =in.gxt_h? in.gxt_h:0;
s32 i_out =in.gxt_i? in.gxt_i:0;
s32 j_out =in.gxt_j? in.gxt_j:0;
gxt_senddata(chx_out,a_out,b_out,c_out,d_out,e_out,f_out,g_out,h_out,i_out,j_out);
}



u8 gxt_data_to_send[150];
void gxt_senddata(u8 gxt_chx,s32 gxt_a,s32 gxt_b,s32 gxt_c,s32 gxt_d,s32 gxt_e,s32 gxt_f,s32 gxt_g,s32 gxt_h,s32 gxt_i,s32 gxt_j)
{
	u8 gxt_cnt=0;//计数
	u8 gxt_sc=0;//对总数进行累加
	u8 gxt_ac=0;//ac对sc进行累加
	
	gxt_data_to_send[gxt_cnt++]=0xAA;//帧头
	gxt_data_to_send[gxt_cnt++]=0xFF;//帧头
	gxt_data_to_send[gxt_cnt++]=0xF0+gxt_chx;//通道
	gxt_data_to_send[gxt_cnt++]=0;//数据字节数
	
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_a);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_a);
	gxt_data_to_send[gxt_cnt++]=BYTE2(gxt_a);
	gxt_data_to_send[gxt_cnt++]=BYTE3(gxt_a);
	
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_b);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_b);
	gxt_data_to_send[gxt_cnt++]=BYTE2(gxt_b);
	gxt_data_to_send[gxt_cnt++]=BYTE3(gxt_b);
	
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_c);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_c);
	gxt_data_to_send[gxt_cnt++]=BYTE2(gxt_c);
	gxt_data_to_send[gxt_cnt++]=BYTE3(gxt_c);
	
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_d);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_d);
	gxt_data_to_send[gxt_cnt++]=BYTE2(gxt_d);
	gxt_data_to_send[gxt_cnt++]=BYTE3(gxt_d);
	
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_e);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_e);
	gxt_data_to_send[gxt_cnt++]=BYTE2(gxt_e);
	gxt_data_to_send[gxt_cnt++]=BYTE3(gxt_e);
	
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_f);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_f);
	gxt_data_to_send[gxt_cnt++]=BYTE2(gxt_f);
	gxt_data_to_send[gxt_cnt++]=BYTE3(gxt_f);
	
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_g);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_g);
	gxt_data_to_send[gxt_cnt++]=BYTE2(gxt_g);
	gxt_data_to_send[gxt_cnt++]=BYTE3(gxt_g);
	
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_h);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_h);
	gxt_data_to_send[gxt_cnt++]=BYTE2(gxt_h);
	gxt_data_to_send[gxt_cnt++]=BYTE3(gxt_h);
	
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_i);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_i);
	gxt_data_to_send[gxt_cnt++]=BYTE2(gxt_i);
	gxt_data_to_send[gxt_cnt++]=BYTE3(gxt_i);
	
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_j);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_j);
	gxt_data_to_send[gxt_cnt++]=BYTE2(gxt_j);
	gxt_data_to_send[gxt_cnt++]=BYTE3(gxt_j);
	
	gxt_data_to_send[3]=gxt_cnt-4;
	
	for(u8 gxt_i=0;gxt_i<gxt_data_to_send[3]+4;gxt_i++)
	{
		gxt_sc+=gxt_data_to_send[gxt_i];
		gxt_ac+=gxt_sc;
	}
	
	gxt_data_to_send[gxt_cnt++]=gxt_sc;
	gxt_data_to_send[gxt_cnt++]=gxt_ac;
	UART1_Send_Str(gxt_data_to_send,gxt_cnt);
}

void gxt_v7_send(u16 v7_id,s32 v7_val)
{
	u8 gxt_cnt=0;//计数
	u8 gxt_sc=0;//对总数进行累加
	u8 gxt_ac=0;//ac对sc进行累加
	
	gxt_data_to_send[gxt_cnt++]=0xAA;//帧头
	gxt_data_to_send[gxt_cnt++]=0xAF;//帧头
	gxt_data_to_send[gxt_cnt++]=0xE2;//通道
	gxt_data_to_send[gxt_cnt++]=0;//数据字节数--在下方已经赋值不用管
	
	gxt_data_to_send[gxt_cnt++]=BYTE0(v7_id);
	gxt_data_to_send[gxt_cnt++]=BYTE1(v7_id);
	gxt_data_to_send[gxt_cnt++]=BYTE0(v7_val);
	gxt_data_to_send[gxt_cnt++]=BYTE1(v7_val);
	gxt_data_to_send[gxt_cnt++]=BYTE2(v7_val);
	gxt_data_to_send[gxt_cnt++]=BYTE3(v7_val);
	gxt_data_to_send[3]=gxt_cnt-4;
	
	for(u8 gxt_i=0;gxt_i<gxt_data_to_send[3]+4;gxt_i++)
	{
		gxt_sc+=gxt_data_to_send[gxt_i];
		gxt_ac+=gxt_sc;
	}
	gxt_data_to_send[gxt_cnt++]=gxt_sc;
	gxt_data_to_send[gxt_cnt++]=gxt_ac;
	UART1_Send_Str(gxt_data_to_send,gxt_cnt);
}



void gxt_v7_send_check(u8 v7_id,u8 sc,u8 ac)
{
	u8 gxt_cnt=0;//计数
	u8 gxt_sc=0;//对总数进行累加
	u8 gxt_ac=0;//ac对sc进行累加
	
	gxt_data_to_send[gxt_cnt++]=0xAA;//帧头
	gxt_data_to_send[gxt_cnt++]=0xAF;//帧头
	gxt_data_to_send[gxt_cnt++]=0x00;//通道
	gxt_data_to_send[gxt_cnt++]=0;//数据字节数--在下方已经赋值不用管
	
	gxt_data_to_send[gxt_cnt++]=v7_id;
	gxt_data_to_send[gxt_cnt++]=sc;
	gxt_data_to_send[gxt_cnt++]=ac;
	gxt_data_to_send[3]=gxt_cnt-4;
	
	for(u8 gxt_i=0;gxt_i<gxt_data_to_send[3]+4;gxt_i++)
	{
		gxt_sc+=gxt_data_to_send[gxt_i];
		gxt_ac+=gxt_sc;
	}
	gxt_data_to_send[gxt_cnt++]=gxt_sc;
	gxt_data_to_send[gxt_cnt++]=gxt_ac;
	UART1_Send_Str(gxt_data_to_send,gxt_cnt);
}



void UART1_Send_Str(u8 *s,u8 cnt_s)//发送字符串 函数   应用指针 方法
{
	u8 i;
	for(i=0;i<cnt_s;i++)
	{
		USART_SendData(USART1,s[i]);
		while( USART_GetFlagStatus(USART1,USART_FLAG_TXE)!= SET);
	}
}


//四元数q0,q1,q2,q3放大10000倍，ronghe是融合状态,1或0
void Send_Quaternion(s16 gxt_a,s16 gxt_b,s16 gxt_c,s16 gxt_d,u8 ronghe)
{
	u8 gxt_cnt=0;//计数
	u8 gxt_sc=0;//对总数进行累加
	u8 gxt_ac=0;//ac对sc进行累加
	
	gxt_data_to_send[gxt_cnt++]=0xAA;//帧头
	gxt_data_to_send[gxt_cnt++]=0xFF;//帧头
	gxt_data_to_send[gxt_cnt++]=0x04;//通道
	gxt_data_to_send[gxt_cnt++]=9;//数据字节数
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_a);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_a);
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_b);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_b);
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_c);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_c);
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_d);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_d);
	gxt_data_to_send[gxt_cnt++]=ronghe;
	
	for(u8 gxt_i=0;gxt_i<gxt_data_to_send[3]+4;gxt_i++)
	{
		gxt_sc+=gxt_data_to_send[gxt_i];
		gxt_ac+=gxt_sc;
	}
	gxt_data_to_send[gxt_cnt++]=gxt_sc;
	gxt_data_to_send[gxt_cnt++]=gxt_ac;
	UART1_Send_Str(gxt_data_to_send,gxt_cnt);
}


//罗盘，气压，温度
void Send_LP_QY_TEMP(s16 gxt_a,s16 gxt_b,s16 gxt_c,s32 gxt_d,s16 gxt_e,u8 gxt_f,u8 gxt_g)
{
	u8 gxt_cnt=0;//计数
	u8 gxt_sc=0;//对总数进行累加
	u8 gxt_ac=0;//ac对sc进行累加
	
	gxt_data_to_send[gxt_cnt++]=0xAA;//帧头
	gxt_data_to_send[gxt_cnt++]=0xFF;//帧头
	gxt_data_to_send[gxt_cnt++]=0x02;//通道
	gxt_data_to_send[gxt_cnt++]=14;//数据字节数
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_a);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_a);
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_b);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_b);
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_c);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_c);
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_d);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_d);
	gxt_data_to_send[gxt_cnt++]=BYTE2(gxt_d);
	gxt_data_to_send[gxt_cnt++]=BYTE3(gxt_d);
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_e);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_e);
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_f);
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_g);
	for(u8 gxt_i=0;gxt_i<gxt_data_to_send[3]+4;gxt_i++)
	{
		gxt_sc+=gxt_data_to_send[gxt_i];
		gxt_ac+=gxt_sc;
	}
	gxt_data_to_send[gxt_cnt++]=gxt_sc;
	gxt_data_to_send[gxt_cnt++]=gxt_ac;
	UART1_Send_Str(gxt_data_to_send,gxt_cnt);
}


void Send_AX_GY(s16 gxt_a,s16 gxt_b,s16 gxt_c,s16 gxt_d,s16 gxt_e,s16 gxt_f,u8 gxt_g)
{
	u8 gxt_cnt=0;//计数
	u8 gxt_sc=0;//对总数进行累加
	u8 gxt_ac=0;//ac对sc进行累加
	gxt_data_to_send[gxt_cnt++]=0xAA;//帧头
	gxt_data_to_send[gxt_cnt++]=0xFF;//帧头
	gxt_data_to_send[gxt_cnt++]=0x01;//通道
	gxt_data_to_send[gxt_cnt++]=13;//数据字节数
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_a);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_a);
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_b);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_b);
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_c);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_c);
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_d);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_d);
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_e);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_e);
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_f);
	gxt_data_to_send[gxt_cnt++]=BYTE1(gxt_f);
	gxt_data_to_send[gxt_cnt++]=BYTE0(gxt_g);
	for(u8 gxt_i=0;gxt_i<gxt_data_to_send[3]+4;gxt_i++)
	{
		gxt_sc+=gxt_data_to_send[gxt_i];
		gxt_ac+=gxt_sc;
	}
	gxt_data_to_send[gxt_cnt++]=gxt_sc;
	gxt_data_to_send[gxt_cnt++]=gxt_ac;
	UART1_Send_Str(gxt_data_to_send,gxt_cnt);
}




