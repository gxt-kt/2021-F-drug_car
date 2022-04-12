#include "attitude_up.h"

//气压计
struct SPL06 spl06_data;
//磁力计
struct AK8975 ak8975_data;
//六轴传感器
struct ICM20602 icm20602_data;


float t_ax,t_ay,t_az;//这边亲测需要float类型，不然会出错，缺少精度
float t_gx,t_gy,t_gz;


void Posture_solution(void)
{
	ICM20602_Updata(&icm20602_data);
	Prepare_Data(icm20602_data.accX,icm20602_data.accY,icm20602_data.accZ,icm20602_data.gyroX,icm20602_data.gyroY,icm20602_data.gyroZ);
	Imu_Update();
}

#undef SUCCESS 
#define SUCCESS 0
#undef FAILED 
#define FAILED 1
void ATTITUDE_INIT(void)
{
	SPI3_Init();
	delay_ms(400);
	while(ICM20602_Init() == FAILED)
	{
		//printf("ICM20602 init failed");
		delay_ms(400);
	}
	//printf("ICM20602 init successful\n");
	while(AK8975_init() == FAILED) 	
	{
		//printf("AK8975 init failed");
		delay_ms(400);
	}
	//printf("AK8975 init successful\n");
	while(spl0601_init() == FAILED) 
	{
		//printf("SPL06 init failed");
		delay_ms(400);
	}
	//printf("SPL06 init successful\n");
}

void spl_ak_read(void)//磁力计气压计数据读取
{
//气压计数据解读
	spl06_data.temperature = user_spl0601_get_temperature();
	spl06_data.presure = user_spl0601_get_presure();			 
	spl06_data.baro_height = (uint32_t)((102000.0f	- spl06_data.presure) * 78.740f);  //每1mpar平均海拔高度为78.740mm
	//磁力计数据解读
	AK8975_Updata(&ak8975_data);
}
static float invSqrt(float x) 		//快速计算 1/Sqrt(x)
{
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}


void Prepare_Data(int16_t ax,int16_t ay,int16_t az,int16_t gx,int16_t gy,int16_t gz)
{
	t_ax=(float)ax;t_ay=(float)ay;t_az=(float)az;
	t_gx=(float)gx;t_gy=(float)gy;t_gz=(float)gz;
	
	//将加速度原始AD值转换为m/s^2
	//t_ax = (float)t_ax * Acc_Gain * G;
	//t_ay = (float)t_ay * Acc_Gain * G;
	//t_az= (float)t_az * Acc_Gain * G;
	
	t_ax=t_ax * Acc_Gain * G;
	t_ay=t_ay * Acc_Gain * G;
	t_az=t_az * Acc_Gain * G;
	
	//将陀螺仪AD值转换为 弧度/s
	t_gx = t_gx * gyro_Gr;
	t_gy = t_gy * gyro_Gr;
	t_gz = t_gz * gyro_Gr;
}



#define Kp 1.50f
#define Ki 0.005f
#define halfT 0.0025f						//计算周期的一半，单位s

float yaw,pitch,roll;		
float q0 = 1, q1 = 0, q2 = 0, q3 = 0;		//四元数
float exInt = 0, eyInt = 0, ezInt = 0;		//叉积计算误差的累计积分


void Imu_Update(void)
{
	float vx,vy,vz;							//实际重力加速度
	float ex,ey,ez;							//叉积计算的误差
	float norm;
	
 	float q0q0 = q0*q0;
 	float q0q1 = q0*q1;
	float q0q2 = q0*q2;
	float q0q3 = q0*q3;
	float q1q1 = q1*q1;
 	float q1q2 = q1*q2;
 	float q1q3 = q1*q3;
	float q2q2 = q2*q2;
	float q2q3 = q2*q3;
	float q3q3 = q3*q3;
	
	if(t_ax*t_ay*t_az == 0)
		return;
	
	//加速度计测量的重力方向(机体坐标系)
	norm = invSqrt(t_ax*t_ax + t_ay*t_ay + t_az*t_az);			//之前这里写成invSqrt(t_ax*t_ax + t_ay+t_ay + t_az*t_az)是错误的，现在修改过来了
	t_ax = t_ax * norm;
	t_ay = t_ay * norm;
	t_az = t_az * norm;
	
	//四元数推出的实际重力方向(机体坐标系)
	vx = 2*(q1q3 - q0q2);												
  vy = 2*(q0q1 + q2q3);
  vz = q0q0 - q1q1 - q2q2 + q3q3;
	
	//叉积误差
	ex = (t_ay*vz - t_az*vy);
	ey = (t_az*vx - t_ax*vz);
	ez = (t_ax*vy - t_ay*vx);
	
	//叉积误差积分为角速度
	exInt = exInt + ex * Ki;
	eyInt = eyInt + ey * Ki;
	ezInt = ezInt + ez * Ki;
	
	//角速度补偿
	t_gx = t_gx + Kp*ex + exInt;
	t_gy = t_gy + Kp*ey + eyInt;
	t_gz = t_gz + Kp*ez + ezInt;
	
	//更新四元数
  q0 = q0 + (-q1*t_gx - q2*t_gy - q3*t_gz)*halfT;
  q1 = q1 + (q0*t_gx + q2*t_gz - q3*t_gy)*halfT;
  q2 = q2 + (q0*t_gy - q1*t_gz + q3*t_gx)*halfT;
  q3 = q3 + (q0*t_gz + q1*t_gy - q2*t_gx)*halfT;	
	
	//单位化四元数
	norm = invSqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
	q0 = q0 * norm;
	q1 = q1 * norm;
	q2 = q2 * norm;  
	q3 = q3 * norm;
	
	//四元数反解欧拉角
	yaw = atan2(2.f * (q1q2 + q0q3), q0q0 + q1q1 - q2q2 - q3q3)* 57.3f;
	pitch = -asin(2.f * (q1q3 - q0q2))* 57.3f-0.6;
	roll = atan2(2.f * q2q3 + 2.f * q0q1, q0q0 - q1q1 - q2q2 + q3q3)* 57.3f-0.7;
}
