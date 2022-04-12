#include "V7_data_deal.h"

s32 futile_x=0;//无用值，当值不用时来填空缺的
/*需要改值就从这开始，注意要留&，不用记得一定用futile_x填充*/
s32 *v7_val_11=(s32*)&test;
s32 *v7_val_12=&futile_x;
s32 *v7_val_13=&futile_x;
s32 *v7_val_14=&futile_x;
s32 *v7_val_15=&futile_x;
s32 *v7_val_16=&futile_x;

float u1_get_val[10]={0};
void USART1_Data_Count(char *buf)//用来调节pid的值，方便调参
{
	u8 i=0;
	u8 sc=0;
	u8 ac=0;
	u16 v7_id;
	if(buf[1]==0XAA&&(buf[2]==0XFF||buf[2]==0x05))//buf1判断帧头，buf2判断广播或者专用飞控
	{
		for(i=1;i<buf[4]+5;i++){sc+=buf[i];ac+=sc;}//计算校验和
		if((sc!=buf[buf[4]+5])||(ac!=buf[buf[4]+6])) return;//校验和不满足，提前结束
		//校验都正确，解析程序
		if(buf[3]==0XE1)//上位机发送了读取参数命令
		{
			v7_id=*(u16*)(&buf[5]);//读取id
			switch (v7_id)
			{
				case 1:gxt_v7_send(v7_id,0x05); break;/*id-01专属，必须发送05或60，fake飞控*/
				/*下面可以对不同id选择pid的值发给上位机*/
				case 11:gxt_v7_send(v7_id,*v7_val_11); break;//第一组值
				case 12:gxt_v7_send(v7_id,*v7_val_12); break;//第二组值
				case 13:gxt_v7_send(v7_id,*v7_val_13); break;//第三组值
				case 14:gxt_v7_send(v7_id,*v7_val_14); break;//第一组值
				case 15:gxt_v7_send(v7_id,*v7_val_15); break;//第二组值
				case 16:gxt_v7_send(v7_id,*v7_val_16); break;//第三组值
				default: gxt_v7_send(v7_id,v7_id); break;//默认，不可省略
			}
		}
		else if(buf[3]==0XE2)//上位机发送了写入参数命令
		{
			v7_id=*(u16*)(&buf[5]);//读取id
			switch (v7_id)
			{
				//关键点的参数读取
				case 11:*v7_val_11=*(s32*)(&buf[7]); break;
				case 12:*v7_val_12=*(s32*)(&buf[7]); break;
				case 13:*v7_val_13=*(s32*)(&buf[7]); break;
				case 14:*v7_val_14=*(s32*)(&buf[7]); break;
				case 15:*v7_val_15=*(s32*)(&buf[7]); break;
				case 16:*v7_val_16=*(s32*)(&buf[7]); break;
				default: break;
			}
			gxt_v7_send_check(buf[3],buf[buf[4]+5],buf[buf[4]+6]);
		}
	}
	else if(buf[1]=='g'&&buf[3]=='=')/*自创通讯协议，在v7里输入g1=1.23，CHR格式发送*/
	{
		if(buf[2]=='1') 		 {u1_get_val[1]=strtod(buf+4,NULL);flag_go=!flag_go;}//解析数值
		else if(buf[2]=='2') u1_get_val[2]=strtod(buf+4,NULL);
		else if(buf[2]=='3') u1_get_val[3]=strtod(buf+4,NULL);
		else if(buf[2]=='4') u1_get_val[4]=strtod(buf+4,NULL);
		else if(buf[2]=='5') u1_get_val[5]=strtod(buf+4,NULL);
		else if(buf[2]=='6') u1_get_val[6]=strtod(buf+4,NULL);
		else if(buf[2]=='7') u1_get_val[7]=strtod(buf+4,NULL);
		else if(buf[2]=='8') u1_get_val[8]=strtod(buf+4,NULL);
		for(int j=0;j<15;j++) buf[j]=0;//清空数组，防止上次数据对strtod函数有影响
		/*建议将赋值代码放在下面,上面不建议修改*/
		//例如 anti_val=u1_get_val[6];
//		angle_kp=u1_get_val[1];
//		angle_kd=u1_get_val[2];
//		zj_angle=u1_get_val[3];
//		x_val=(int)u1_get_val[1];
//		y_val=(int)u1_get_val[2];
//		if(pwm_out1>2500) pwm_out1=2500;
//		if(pwm_out1<500) pwm_out1=500;
//		balance_pi.kd=u1_get_val[3];
//		balance_pi.ki=balance_pi.kp/100;
	}
}
