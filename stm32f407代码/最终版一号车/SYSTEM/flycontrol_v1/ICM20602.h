#ifndef icm20602_h__
#define icm20602_h__
#include "sys.h"



 struct ICM20602
{
	int16_t accX,accY,accZ;
	int16_t gyroX,gyroY,gyroZ;	
};

uint8_t ICM20602_Init(void); //初始化
void ICM20602_Updata(struct ICM20602 *pICM20602); //读取数据;

#endif

