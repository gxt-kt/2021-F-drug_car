#ifndef attitude_up__h__
#define attitude_up__h__
#include "sys.h"

 //气压计
extern struct SPL06 spl06_data;
//磁力计
extern struct AK8975 ak8975_data;
//六轴传感器
extern struct ICM20602 icm20602_data;


//注意这边的值还是要算一下，不是百分百准确，需要*2或者/2
#define Acc_Gain 0.00012207f			//加速度转换单位(初始化加速度计量程+-4g，由于mpu6050的数据寄存器是16位的，LSBa = 2*4 / 65535.0)
#define gyro_Gain 0.0304985f		//角速度转换为角度(LSBg = 2000*2 / 65535)
#define gyro_Gr 0.0005323			//角速度转换成弧度(3.1415 / 180 * LSBg)
#define G 9.80665f					// m/s^2



extern float t_ax,t_ay,t_az;
extern float t_gx,t_gy,t_gz;
extern float q0,q1,q2,q3;
extern float yaw,pitch,roll;
static float invSqrt(float x);
void Prepare_Data(int16_t ax,int16_t ay,int16_t az,int16_t gx,int16_t gy,int16_t gz);
void Imu_Update(void);
void Posture_solution(void);
void ATTITUDE_INIT(void);
void spl_ak_read(void);//磁力计气压计数据读取
#endif //attitude_up__h__
