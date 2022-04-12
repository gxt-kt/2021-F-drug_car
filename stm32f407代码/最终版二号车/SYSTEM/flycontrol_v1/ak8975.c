#include "ak8975.h"

#undef SUCCESS
#define SUCCESS 0
#undef FAILED
#define FAILED  1
//***********AK8963 �����ƼĴ���******
#define MAG_ID_REG  0x00 //������ID�ļĴ�����ַ
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


#define MAG_ADDR 0x0C //CAD0=0 CAD1=0 �Ĵ����Ƶ�7λIIC��ַ



//��д����
void ak8975_write(uint8_t REG,uint8_t DATA)
{
	AK8975_CS_L;//CS������ΪSPIģʽ
	SPI_RW(REG&0x7f);//���ͼĴ�����ַ+д����
	SPI_RW(DATA);
	AK8975_CS_H;
}
int ak89_id;
uint8_t ak8975_read(uint8_t REG)
{
	uint8_t data;
	AK8975_CS_L;//CS������ΪSPIģʽ
	SPI_RW(REG|0x80);//���ͼĴ�����ַ+������
	data = SPI_RW(0xff);
	ak89_id=data;
	AK8975_CS_H;
	return data;
}
/****************************************************************************************
*����һ��ת�� 
*@brief   
*@param[in]
*****************************************************************************************/
void MAG_Restart(void)
{ 
	ak8975_write(  MAG_Control, 0x11);//0x10 16λģʽ | 0x01 ���β���ģʽ  //��ʼת�����Ͷ�ȡ����֮�������7ms���ϵ�ʱ��
} 

/****************************************************************************************
*@brief   
*@brief   
*@param[in]
*****************************************************************************************/
uint8_t AK8975_init(void)
{
 
	//���ID
	if(ak8975_read( MAG_ID_REG) != MAG_ID) 
		return FAILED;//ID����
	//����һ��ת��
	MAG_Restart(); //    0x10 16λģʽ|0x01 ���β���ģʽ		//14λ - 0.6uT/LSB      16λ - 0.15uT/LSB
	//��ʱ�ȴ������ƿ���
	delay_ms(10); 
	
	return SUCCESS;
}	

/****************************************************************************************
*@brief   
*@in Ҫ��ȡXYZ�ĸ��������
*@out ��ǰ��16bit������
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
