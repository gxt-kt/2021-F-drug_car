#ifndef imu_spi_h__
#define imu_spi_h__
#include "sys.h"


void SPI3_Init(void);
u8 SPI_RW(u8 dat);


#define ICM20602_CS_H GPIO_SetBits(GPIOE, GPIO_Pin_10)
#define ICM20602_CS_L GPIO_ResetBits(GPIOE, GPIO_Pin_10)
#define AK8975_CS_H GPIO_SetBits(GPIOE, GPIO_Pin_11)
#define AK8975_CS_L GPIO_ResetBits(GPIOE, GPIO_Pin_11)
#define SPL06_CS_H GPIO_SetBits(GPIOE, GPIO_Pin_12)
#define SPL06_CS_L GPIO_ResetBits(GPIOE, GPIO_Pin_12)

#endif
