#ifndef attitude_up__h__
#define attitude_up__h__
#include "sys.h"

 //��ѹ��
extern struct SPL06 spl06_data;
//������
extern struct AK8975 ak8975_data;
//���ᴫ����
extern struct ICM20602 icm20602_data;


//ע����ߵ�ֵ����Ҫ��һ�£����ǰٷְ�׼ȷ����Ҫ*2����/2
#define Acc_Gain 0.00012207f			//���ٶ�ת����λ(��ʼ�����ٶȼ�����+-4g������mpu6050�����ݼĴ�����16λ�ģ�LSBa = 2*4 / 65535.0)
#define gyro_Gain 0.0304985f		//���ٶ�ת��Ϊ�Ƕ�(LSBg = 2000*2 / 65535)
#define gyro_Gr 0.0005323			//���ٶ�ת���ɻ���(3.1415 / 180 * LSBg)
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
void spl_ak_read(void);//��������ѹ�����ݶ�ȡ
#endif //attitude_up__h__
