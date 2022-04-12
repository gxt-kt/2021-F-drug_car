#include "ak8975.h"

#undef SUCCESS
#define SUCCESS 0
#undef FAILED
#define FAILED  1
//***********AK8963 磁力计寄存器******
#define MAG_ID_REG  0x00 //磁力计ID的寄存器地址
#define MAG_ID  0X48
#define MAG_Status1			0x02
#define MAG_XOUT_L		0x03
#define MAG_XOUT_H		0x04
#define MAG_YOUT_L		0x05
#define MAG_YOUT_H		0x06
#define MAG_ZOUT_L		0x07
#define MAG_ZOUT_H		0x08

#define MAG_Status2			0x09
#define MAG_Control			0x0A
#define MAG_Self_test		0x0C
#define MAG_Self_test		0x0C


#define MAG_ADDR 0x0C //CAD0=0 CAD1=0 的磁力计的7位IIC地址



//读写配置
void ak8975_write(uint8_t REG,uint8_t DATA)
{
	AK8975_CS_L;//CS拉低则为SPI模式
	SPI_RW(REG&0x7f);//发送寄存器地址+写命令
	SPI_RW(DATA);
	AK8975_CS_H;
}
int ak89_id;
uint8_t ak8975_read(uint8_t REG)
{
	uint8_t data;
	AK8975_CS_L;//CS拉低则为SPI模式
	SPI_RW(REG|0x80);//发送寄存器地址+读命令
	data = SPI_RW(0xff);
	ak89_id=data;
	AK8975_CS_H;
	return data;
}
/****************************************************************************************
*启动一次转换 
*@brief   
*@param[in]
*****************************************************************************************/
void MAG_Restart(void)
{ 
	ak8975_write(  MAG_Control, 0x11);//0x10 16位模式 | 0x01 单次测量模式  //开始转换，和读取数据之间必须间隔7ms以上的时间
} 

/****************************************************************************************
*@brief   
*@brief   
*@param[in]
*****************************************************************************************/
uint8_t AK8975_init(void)
{
 
	//检查ID
	if(ak8975_read( MAG_ID_REG) != MAG_ID) 
		return FAILED;//ID错误
	//启动一次转换
	MAG_Restart(); //    0x10 16位模式|0x01 单次测量模式		//14位 - 0.6uT/LSB      16位 - 0.15uT/LSB
	//延时等待磁力计可用
	delay_ms(10); 
	
	return SUCCESS;
}	

/****************************************************************************************
*@brief   
*@in 要获取XYZ哪个轴的数据
*@out 当前轴16bit的数据
*@param[in]
*****************************************************************************************/
void AK8975_Updata(struct AK8975 *pAK8975)
{	
		uint8_t BUF[2];
	
		 BUF[0] = ak8975_read ( MAG_XOUT_L);
		 BUF[1] = ak8975_read ( MAG_XOUT_H);
		 pAK8975->magX =((BUF[1]<<8)|BUF[0]);
		
		 BUF[0] = ak8975_read ( MAG_YOUT_L);
		 BUF[1] = ak8975_read ( MAG_YOUT_H);
		 pAK8975->magY =((BUF[1]<<8)|BUF[0]);


		 BUF[0] = ak8975_read ( MAG_ZOUT_L);
		 BUF[1] = ak8975_read ( MAG_ZOUT_H);
		 pAK8975->magZ =((BUF[1]<<8)|BUF[0]);
	
		 MAG_Restart(); 
}
