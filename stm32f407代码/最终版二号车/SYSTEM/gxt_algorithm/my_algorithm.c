#include "my_algorithm.h"
/*GXT-�����ֵ�㷨*/
abs_type GXT_abs(abs_type a)
{
	return a>0?a:(-a);
}
/***************************************************************/


///*GXT-��ֵ�˲��㷨*/
//my_type M_F_array[M_F_num];//�����˲�����
//my_type GXT_Mean_Filter(my_type a)
//{
//	int i=0;
//	float sum=0;
//	for(;i<M_F_num-1;i++)
//	{
//		M_F_array[i]=M_F_array[i+1];
//	}
//	M_F_array[i]=a;
//	for(i=0;i<M_F_num;i++)
//	{
//		sum+=M_F_array[i];
//	}
//	return (my_type)(sum/M_F_num);
//}
/***************************************************************/

/*GXT-����������㷨*/
int GXT_Random_Num(void)
{
	srand((unsigned int)system_time);//����ʹ����ϵͳʱ�ӣ�����TIM6�ۼӵ�ʱ�ӣ���λms
	return (GXT_RANDOM);//ȡֵ��ΧΪ20~120
}
/***************************************************************/

FILTER tt1;
FILTER tt2;
float GXT_Mean_Filter(FILTER *filter,int data)
{
	/**********�������ڴ�����ʵ�ֲ���-GXT***********/
	if(filter->first==0){//����ǵ�һ������
	filter->first=1;//��־λ��1
	int* p = (int*)malloc(filter->len * (sizeof(float)));//�����Ӧ���ȸ�float�͵Ŀռ�
	filter->add=p;//������ĵ�ַ�浽�ṹ������
	}
	/**********�������㷨ʵ�ֲ���-GXT***********/
  int i=0;
  float sum=0;
  for(;i<filter->len-1;i++)
  {
    *(filter->add+i)=*(filter->add+i+1);
  }
  *(filter->add+i)=data;
  for(i=0;i<filter->len-1;i++)
  {
    sum+=*(filter->add+i);
  }
  return (float)(sum/filter->len); 
}
