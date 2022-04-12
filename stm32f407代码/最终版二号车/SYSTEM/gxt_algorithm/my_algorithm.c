#include "my_algorithm.h"
/*GXT-求绝对值算法*/
abs_type GXT_abs(abs_type a)
{
	return a>0?a:(-a);
}
/***************************************************************/


///*GXT-均值滤波算法*/
//my_type M_F_array[M_F_num];//定义滤波数组
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

/*GXT-生成随机数算法*/
int GXT_Random_Num(void)
{
	srand((unsigned int)system_time);//这里使用了系统时钟，对用TIM6累加的时钟，单位ms
	return (GXT_RANDOM);//取值范围为20~120
}
/***************************************************************/

FILTER tt1;
FILTER tt2;
float GXT_Mean_Filter(FILTER *filter,int data)
{
	/**********以下是内存申请实现部分-GXT***********/
	if(filter->first==0){//如果是第一次申请
	filter->first=1;//标志位设1
	int* p = (int*)malloc(filter->len * (sizeof(float)));//申请对应长度个float型的空间
	filter->add=p;//将申请的地址存到结构体里面
	}
	/**********以下是算法实现部分-GXT***********/
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
