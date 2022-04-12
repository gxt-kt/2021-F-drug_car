#ifndef SPL06_01_H
#define SPL06_01_H

#include "sys.h"






struct SPL06{
float temperature;//读取的温度值 单位℃摄氏度
float presure;//温度补偿后的气压值 单位mpar 毫帕
int baro_height;//解算后的气压高度值，单位mm毫米
};





unsigned char spl0601_init(void);

float user_spl0601_get_presure(void);
float user_spl0601_get_temperature(void);
#endif

