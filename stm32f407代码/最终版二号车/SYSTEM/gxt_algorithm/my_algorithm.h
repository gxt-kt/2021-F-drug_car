#ifndef __my_algorithm_h__
#define __my_algorithm_h__
#include "sys.h"

/*GXT-�����ֵ�㷨*/
typedef int abs_type;//������������
abs_type GXT_abs(abs_type a);
/***************************************************************/


/*GXT-��ֵ�˲��㷨*/
//#define M_F_num 10	//�����˲�����
//typedef int my_type;//������������
//my_type GXT_Mean_Filter(my_type a);

typedef struct FILTER
{
	uint16_t len;//�˲������ݸ���
	u8 first;//�Ƿ��һ�������ڴ�
	int *add;//���ݴ�ŵ�ַ���ɶ�̬�ռ��ṩ��ַ
}FILTER;
extern struct FILTER tt1;
extern struct FILTER tt2;

float GXT_Mean_Filter(FILTER *filter,int data);
/***************************************************************/



#define GXT_RANDOM (rand()%100-30) //ȡֵ��Χ��-30~70
int GXT_Random_Num(void);



#endif //__my_algorithm_h__

