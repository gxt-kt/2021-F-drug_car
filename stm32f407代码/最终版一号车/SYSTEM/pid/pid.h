#ifndef pid_h__
#define pid_h__
#include "sys.h"



typedef struct PID_zl{
    float err;                //����ƫ��ֵ
    float err_last;            //������һ��ƫ��ֵ
		float err_pre;            //�������ϸ�ƫ��
		float dif;								//����΢��ֵ
		float dif_two;								//�������΢��ֵ
    float kp,ki,kd;            //������������֡�΢��ϵ��
    float out;          
		float limit_up;
		float limit_dn;
}PID_zl;
typedef struct PID_wz{
		float now;                //���嵱ǰֵ
    float anti;            //��������ֵ
    float err;                //����ƫ��ֵ
    float err_last;            //������һ��ƫ��ֵ
		float dif;								//����΢��ֵ
    float kp,ki,kd;            //������������֡�΢��ϵ��
    float integral;            //�������ֵ
    float out;          //�����ѹֵ������ִ�����ı�����
		float itl_lim_up;//�����޷�
		float itl_lim_dn;
		float limit_up;//����޷�
		float limit_dn;
}PID_wz;
extern struct PID_zl zl_text;
extern struct PID_wz wz_text;

void  pid_Init(void);
float PID_WZ_TEST(float pid_now,float pid_anti);
float PID_ZL_TEST(float pid_now,float pid_anti);
#endif //pid_h__

