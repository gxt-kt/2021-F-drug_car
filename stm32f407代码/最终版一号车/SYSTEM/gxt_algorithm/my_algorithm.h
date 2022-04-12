#ifndef __my_algorithm_h__
#define __my_algorithm_h__
#include "sys.h"

/*GXT-求绝对值算法*/
typedef int abs_type;//定义数据类型
abs_type GXT_abs(abs_type a);
/***************************************************************/


/*GXT-均值滤波算法*/
//#define M_F_num 10	//定义滤波个数
//typedef int my_type;//定义数据类型
//my_type GXT_Mean_Filter(my_type a);

typedef struct FILTER
{
	uint16_t len;//滤波器数据个数
	u8 first;//是否第一次申请内存
	int *add;//数据存放地址，由动态空间提供地址
}FILTER;
extern struct FILTER tt1;
extern struct FILTER tt2;

float GXT_Mean_Filter(FILTER *filter,int data);
/***************************************************************/



#define GXT_RANDOM (rand()%100-30) //取值范围是-30~70
int GXT_Random_Num(void);



#endif //__my_algorithm_h__

