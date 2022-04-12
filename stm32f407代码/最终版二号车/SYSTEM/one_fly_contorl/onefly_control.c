#include "onefly_control.h"

u8 onefly_setup=0;
PID_wz onefly_pid;

void  onefly_pid_init(void)
{    
	onefly_pid.kp=5;
	onefly_pid.ki=5/100;
	onefly_pid.kd=0;
	onefly_pid.out=0;
	onefly_pid.itl_lim_up=5000;
	onefly_pid.itl_lim_dn=-5000;
	onefly_pid.limit_up=800;
	onefly_pid.limit_dn=0;
}

s16 onefly_control(s16 pid_now,s16 pid_anti)
{
	if((pid_now>2500)||(onefly_setup==0))//�ж��Ƿ��Ѿ�ʧ�ػ��߻�û��ʼ����
	{
		onefly_setup=0;
		TIM_SetCompare1(TIM8,0);
		return 0;
	}
	
	onefly_pid.err =pid_anti-pid_now; // ���㵱ǰ���
	if(onefly_setup==1) //������������
	{onefly_pid.integral += onefly_pid.err;      //���ƫ��Ļ���
	if(1)//���������޷�
		{if(onefly_pid.integral >= onefly_pid.itl_lim_up){onefly_pid.integral =  onefly_pid.itl_lim_up;}//�����޷�
		else if(onefly_pid.integral <= onefly_pid.itl_lim_dn){onefly_pid.integral =  onefly_pid.itl_lim_dn;}}
	if(1)/*�������ַ���*/{if((onefly_pid.err<=30)&&(onefly_pid.err>=-30))onefly_pid.integral=0;}
	}
		else onefly_pid.integral=0;//���������֣�����ֵΪ0
	
	onefly_pid.dif=onefly_pid.err-onefly_pid.err_last;
	onefly_pid.out = onefly_pid.kp*onefly_pid.err + onefly_pid.ki*onefly_pid.integral + onefly_pid.kd*onefly_pid.dif;   //λ��ʽPID������
	onefly_pid.err_last = onefly_pid.err;   //������һ��ƫ�� 
	
	if(1){//�Ƿ�����޷�
	if(onefly_pid.out >= onefly_pid.limit_up){onefly_pid.out =  onefly_pid.limit_up;}//����޷�
	else if(onefly_pid.out <= onefly_pid.limit_dn){onefly_pid.out =  onefly_pid.limit_dn;}}
	//return (u16)onefly_pid.out;
	
	//������ֱ�������
	TIM_SetCompare1(TIM8,(u16)onefly_pid.out);
	return 1;
}
