#ifndef SPL06_01_H
#define SPL06_01_H

#include "sys.h"






struct SPL06{
float temperature;//��ȡ���¶�ֵ ��λ�����϶�
float presure;//�¶Ȳ��������ѹֵ ��λmpar ����
int baro_height;//��������ѹ�߶�ֵ����λmm����
};





unsigned char spl0601_init(void);

float user_spl0601_get_presure(void);
float user_spl0601_get_temperature(void);
#endif

