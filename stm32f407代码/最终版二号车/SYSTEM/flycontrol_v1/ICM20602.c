#include "ICM20602.h"

#define gxt_gx_err (22+2.4846*spl06_data.temperature)
#define gxt_gy_err (-108-4.9597*spl06_data.temperature)
#define gxt_gz_err (223+4.4638*spl06_data.temperature)
//#define gxt_gx_err 0
//#define gxt_gy_err 0
//#define gxt_gz_err 0

#undef SUCCESS
#define SUCCESS 0
#undef FAILED
#define FAILED  1

#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIGL			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_ADDRESS	0x3B
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define GYRO_ADDRESS  0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		  0x75	//IIC地址寄存器(默认数值0x68，只读)
#define ICM20602_PRODUCT_ID 0x12


#define ICM20602_ADDRESS  0x69 //七位器件地址

//读写配置
void icm20602_write(uint8_t REG,uint8_t DATA)
{
	ICM20602_CS_L;//CS拉低则为SPI模式
	SPI_RW(REG&0x7f);//发送寄存器地址+写命令
	SPI_RW(DATA);
	ICM20602_CS_H;
}

uint8_t icm20602_read(uint8_t REG)
{
	uint8_t data;
	ICM20602_CS_L;//CS拉低则为SPI模式
	SPI_RW(REG|0x80);//发送寄存器地址+读命令
	data = SPI_RW(0xff);
	ICM20602_CS_H;
	return data;
}

void icm20602_read_nbyte(uint8_t REG,uint8_t len,uint8_t *buf)
{
	ICM20602_CS_L;//CS拉低则为SPI模式
	SPI_RW(REG|0x80);//发送寄存器地址+读命令
	while(len--)
		*buf++ = SPI_RW(0xff);
	ICM20602_CS_H;
}
/****************************************************************************************
ICM20602复位
*@brief  
*@brief   
*@param[in]
*****************************************************************************************/
void ICM20602_rest(void)
{
	icm20602_write(PWR_MGMT_1, 0x80);
	delay_ms(20);

}
/****************************************************************************************
ICM20602初始化
*@brief   
*@brief  
*@param[in]
*****************************************************************************************/
uint8_t ICM20602_Init(void) //初始化
{	
	icm20602_write(  PWR_MGMT_1, 0x80);	//复位传感器
	delay_ms(30);//等待复位完成
	icm20602_write(  SMPLRT_DIV, 0x02); //陀螺仪采样率，0x02( 1s/(1+SMPLRT_DIV)=333Hz 3ms更新一次)
	icm20602_write(  PWR_MGMT_1, 0x03);	//设置设备时钟源，陀螺仪Z轴
	icm20602_write(  CONFIGL, 0x03);   //低通滤波频率，0x03(42Hz)
	icm20602_write(  GYRO_CONFIG, 0x10);//+-2000deg/s
	icm20602_write(  ACCEL_CONFIG, 0x09);//+-4G

	if(icm20602_read(  WHO_AM_I)!= ICM20602_PRODUCT_ID) //如果地址正确
		return FAILED;
	return SUCCESS;
}


/****************************************************************************************
获取ICM20602_Init数据
*@brief    
*@in 无
*@out icm20602数据存储结构体   
*@param[in]
*****************************************************************************************/

#define  Acc_Read() icm20602_read_nbyte(  0X3B,6,buffer) //读取加速度
#define  Gyro_Read() icm20602_read_nbyte(  0x43,6,&buffer[6])  //  读取角速度

void ICM20602_Updata(struct ICM20602 *pICM20602) //读取数据
{
	#define lb1 0.5
	#define lb2 0.3
	#define lb3 0.2
	static int16_t icm20602_buf[12]={0};
	
	uint8_t buffer[14];
	
	icm20602_read_nbyte(ACCEL_XOUT_H,14,buffer);
	
	pICM20602->accX =  (buffer[0] << 8) | buffer[1];
	pICM20602->accY =  (buffer[2] << 8) | buffer[3];
	pICM20602->accZ =  (buffer[4] << 8) | buffer[5];
	pICM20602->gyroX = ((buffer[8] << 8) | buffer[9]) 	- gxt_gx_err;
	pICM20602->gyroY = ((buffer[10] << 8) | buffer[11]) - gxt_gy_err;
	pICM20602->gyroZ = ((buffer[12] << 8) | buffer[13]) - gxt_gz_err;
	
	if(1)//低通滤波
	{
		pICM20602->accX=pICM20602->accX*lb1+icm20602_buf[0]*lb2+icm20602_buf[1]*lb3;
		pICM20602->accY=pICM20602->accY*lb1+icm20602_buf[2]*lb2+icm20602_buf[3]*lb3;
		pICM20602->accZ=pICM20602->accZ*lb1+icm20602_buf[4]*lb2+icm20602_buf[5]*lb3;
		pICM20602->gyroX=pICM20602->gyroX*lb1+icm20602_buf[6]*lb2+icm20602_buf[7]*lb3;
		pICM20602->gyroY=pICM20602->gyroY*lb1+icm20602_buf[8]*lb2+icm20602_buf[9]*lb3;
		pICM20602->gyroZ=pICM20602->gyroZ*lb1+icm20602_buf[10]*lb2+icm20602_buf[11]*lb3;
		icm20602_buf[1]=icm20602_buf[0];
		icm20602_buf[3]=icm20602_buf[2];
		icm20602_buf[5]=icm20602_buf[4];
		icm20602_buf[7]=icm20602_buf[6];
		icm20602_buf[9]=icm20602_buf[8];
		icm20602_buf[11]=icm20602_buf[10];
		icm20602_buf[0]=pICM20602->accX;
		icm20602_buf[2]=pICM20602->accY;
		icm20602_buf[4]=pICM20602->accZ;
		icm20602_buf[6]=pICM20602->gyroX;
		icm20602_buf[8]=pICM20602->gyroY;
		icm20602_buf[10]=pICM20602->gyroZ;
	}
}



