#include "V7_data_deal.h"

s32 futile_x=0;//����ֵ����ֵ����ʱ�����ȱ��
/*��Ҫ��ֵ�ʹ��⿪ʼ��ע��Ҫ��&�����üǵ�һ����futile_x���*/
s32 *v7_val_11=(s32*)&test;
s32 *v7_val_12=&futile_x;
s32 *v7_val_13=&futile_x;
s32 *v7_val_14=&futile_x;
s32 *v7_val_15=&futile_x;
s32 *v7_val_16=&futile_x;

float u1_get_val[10]={0};
void USART1_Data_Count(char *buf)//��������pid��ֵ���������
{
	u8 i=0;
	u8 sc=0;
	u8 ac=0;
	u16 v7_id;
	if(buf[1]==0XAA&&(buf[2]==0XFF||buf[2]==0x05))//buf1�ж�֡ͷ��buf2�жϹ㲥����ר�÷ɿ�
	{
		for(i=1;i<buf[4]+5;i++){sc+=buf[i];ac+=sc;}//����У���
		if((sc!=buf[buf[4]+5])||(ac!=buf[buf[4]+6])) return;//У��Ͳ����㣬��ǰ����
		//У�鶼��ȷ����������
		if(buf[3]==0XE1)//��λ�������˶�ȡ��������
		{
			v7_id=*(u16*)(&buf[5]);//��ȡid
			switch (v7_id)
			{
				case 1:gxt_v7_send(v7_id,0x05); break;/*id-01ר�������뷢��05��60��fake�ɿ�*/
				/*������ԶԲ�ͬidѡ��pid��ֵ������λ��*/
				case 11:gxt_v7_send(v7_id,*v7_val_11); break;//��һ��ֵ
				case 12:gxt_v7_send(v7_id,*v7_val_12); break;//�ڶ���ֵ
				case 13:gxt_v7_send(v7_id,*v7_val_13); break;//������ֵ
				case 14:gxt_v7_send(v7_id,*v7_val_14); break;//��һ��ֵ
				case 15:gxt_v7_send(v7_id,*v7_val_15); break;//�ڶ���ֵ
				case 16:gxt_v7_send(v7_id,*v7_val_16); break;//������ֵ
				default: gxt_v7_send(v7_id,v7_id); break;//Ĭ�ϣ�����ʡ��
			}
		}
		else if(buf[3]==0XE2)//��λ��������д���������
		{
			v7_id=*(u16*)(&buf[5]);//��ȡid
			switch (v7_id)
			{
				//�ؼ���Ĳ�����ȡ
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
	else if(buf[1]=='g'&&buf[3]=='=')/*�Դ�ͨѶЭ�飬��v7������g1=1.23��CHR��ʽ����*/
	{
		if(buf[2]=='1') 		 {u1_get_val[1]=strtod(buf+4,NULL);flag_go=!flag_go;}//������ֵ
		else if(buf[2]=='2') u1_get_val[2]=strtod(buf+4,NULL);
		else if(buf[2]=='3') u1_get_val[3]=strtod(buf+4,NULL);
		else if(buf[2]=='4') u1_get_val[4]=strtod(buf+4,NULL);
		else if(buf[2]=='5') u1_get_val[5]=strtod(buf+4,NULL);
		else if(buf[2]=='6') u1_get_val[6]=strtod(buf+4,NULL);
		else if(buf[2]=='7') u1_get_val[7]=strtod(buf+4,NULL);
		else if(buf[2]=='8') u1_get_val[8]=strtod(buf+4,NULL);
		for(int j=0;j<15;j++) buf[j]=0;//������飬��ֹ�ϴ����ݶ�strtod������Ӱ��
		/*���齫��ֵ�����������,���治�����޸�*/
		//���� anti_val=u1_get_val[6];
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
