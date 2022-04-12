#ifndef SPL06_01_C
#define SPL06_01_C
#include "spl06_001.h"


#undef SUCCESS 
#define SUCCESS 0
#undef FAILED 
#define FAILED 1
#undef ENABLE 
#define ENABLE 1
#undef DISABLE 
#define DISABLE 0

//寄存器定义
#define PRESSURE_REG 0X00
#define TEMP_REG 0X03
#define PRS_CFG_REG 0x06 //气压测量速率配置
#define TMP_CFG_REG 0x07 //温度测量速度配置
#define MEAS_CFG_REG 0x08 //测量配置与传感器配置
#define CFG_REG 0x09 //中断/FIFO/SPI线数等配置
#define INT_STS_REG 0X0A //中断状态标志位
#define FIFO_STS_REG 0X0B //FIFO状态
#define RESET_REG 0X0C
#define ID_REG 0x0D
#define COEF_REG 0x10


#define s32 int32
#define int16 short
#define int32 int
#define uint8 unsigned char


static struct  {	//内部出厂校准数据
    int16 c0;
    int16 c1;
    int32 c00;
    int32 c10;
    int16 c01;
    int16 c11;
    int16 c20;
    int16 c21;
    int16 c30;       
}spl06_calib_param;


struct  {	
    uint8 chip_id; /**<chip id*/	
    int32 i32rawPressure;//原始气压数据
    int32 i32rawTemperature;//原始温度数据
    int32 i32kP;    //气压补偿参数
    int32 i32kT;//温度补偿参数
}spl06;



//读写配置
void spl0601_write(uint8 REG,uint8 DATA)
{
	SPL06_CS_L;//CS拉低则为SPI模式
	SPI_RW(REG&0x7f);//发送寄存器地址+写命令
	SPI_RW(DATA);
	SPL06_CS_H;
}
uint8 spl0601_read(uint8 REG)
{
	uint8 data;
	SPL06_CS_L;//CS拉低则为SPI模式
	SPI_RW(REG|0x80);//发送寄存器地址+读命令
	data = SPI_RW(0xff);
	SPL06_CS_H;
	return data;
}

//什么是过采样，就是采样多组取一次数据，比如温度采样频率10HZ，设置过采样为8，就是每个温度读取都是8组取平均，内部实际做了80HZ的数据采集，后台模式无过采样
/***********************************************************************
 * 气压采样率配置
 * @param[in] 后台模式background_rate采样频率N次/每秒（仅供后台模式使用,命令模式采样频率由用户自己决定，最小间隔取决于过采样所需时间,不同的过采样时间可以有不同的功耗），oversamply过采样次数
 * @param[out] 
 * @return     
 **********************************************************************/
#define PRESSURE_RATE_1_TIMES 0 //采样率 
#define PRESSURE_RATE_2_TIMES 1
#define PRESSURE_RATE_4_TIMES 2
#define PRESSURE_RATE_8_TIMES 3
#define PRESSURE_RATE_16_TIMES 4
#define PRESSURE_RATE_32_TIMES 5
#define PRESSURE_RATE_64_TIMES 6
#define PRESSURE_RATE_128_TIMES 7

void spl06_pressure_rate_config(u8 background_rate,u8 oversamply)
{
		u8 data;
	
		data = (background_rate<<4)|oversamply;
		if(oversamply>PRESSURE_RATE_8_TIMES)//过采样次数大于EMPERATURE_RATE_8_TIMES，应当允许数据被新的数据覆盖，内部拥有气压和温度共32级的FIFO，在大于8次（也就是大于或等于16次过采样）的时候需要被新的数据覆盖，否则数据就会丢失
		{
				u8 data;
				data = spl0601_read(CFG_REG);//读取原寄存器值
				data |= 0X04;//P-SHIFT位置1
				spl0601_write(CFG_REG, data);//重新写回寄存器					
		}		
		switch(oversamply)
    {
        case PRESSURE_RATE_2_TIMES:
          spl06.i32kP = 1572864;
            break;
        case PRESSURE_RATE_4_TIMES:
            spl06.i32kP  = 3670016;
            break;
        case PRESSURE_RATE_8_TIMES:
            spl06.i32kP  = 7864320;
            break;
        case PRESSURE_RATE_16_TIMES:
            spl06.i32kP = 253952;
            break;
        case PRESSURE_RATE_32_TIMES:
            spl06.i32kP = 516096;       
            break;
        case PRESSURE_RATE_64_TIMES:
            spl06.i32kP = 1040384;           
            break;
        case PRESSURE_RATE_128_TIMES:
            spl06.i32kP = 2088960;
            break;
        case PRESSURE_RATE_1_TIMES:
        default:
            spl06.i32kP = 524288;
            break;
    }		
		spl0601_write( PRS_CFG_REG, data);//写入配置
}

/***********************************************************************
 * 温度采样率配置
 * @param[in] background_rate采样频率N次/每秒（仅供后台模式使用,命令模式采样频率由用户自己决定，最小间隔取决于过采样所需时间），oversamply过采样次数 ext温度计选择
 * @param[out] 
 * @return     
 **********************************************************************/
#define TEMPERATURE_RATE_1_TIMES 0 //采样率
#define TEMPERATURE_RATE_2_TIMES 1
#define TEMPERATURE_RATE_4_TIMES 2
#define TEMPERATURE_RATE_8_TIMES 3
#define TEMPERATURE_RATE_16_TIMES 4
#define TEMPERATURE_RATE_32_TIMES 5
#define TEMPERATURE_RATE_64_TIMES 6
#define TEMPERATURE_RATE_128_TIMES 7
#define TEMPERATURE_RATE_TMP_EXT_INTERNAL 0  //集成电路上的温度计
#define TEMPERATURE_RATE_TMP_EXT_EXTERNAL 1  //传感器MEMS气压芯片上温度计
void spl06_temperature_rate_config(u8 background_rate,u8 oversamply,u8 ext)
{
		u8 data;
	
			data = (ext<<7)|(background_rate<<4)|oversamply;
			if(oversamply>TEMPERATURE_RATE_8_TIMES)//过采样次数大于EMPERATURE_RATE_8_TIMES，应当允许数据被新的数据覆盖
			{
					u8 data;
					data = spl0601_read( CFG_REG);//读取原寄存器值
					data |= 0X08;//T-SHIFT位置1
					spl0601_write( CFG_REG, data);	//重新写回寄存器					
			}			
		switch(oversamply)
    {
        case TEMPERATURE_RATE_2_TIMES:
          spl06.i32kT = 1572864;
            break;
        case TEMPERATURE_RATE_4_TIMES:
            spl06.i32kT  = 3670016;
            break;
        case TEMPERATURE_RATE_8_TIMES:
            spl06.i32kT  = 7864320;
            break;
        case TEMPERATURE_RATE_16_TIMES:
            spl06.i32kT = 253952;
            break;
        case TEMPERATURE_RATE_32_TIMES:
            spl06.i32kT = 516096;       
            break;
        case TEMPERATURE_RATE_64_TIMES:
            spl06.i32kT = 1040384;           
            break;
        case TEMPERATURE_RATE_128_TIMES:
            spl06.i32kT = 2088960;
            break;
        case TEMPERATURE_RATE_1_TIMES:
        default:
            spl06.i32kT = 524288;
            break;
    }		
		spl0601_write( TMP_CFG_REG, data);//写入配置
}
/***********************************************************************
 * 传感器测量模式配置与状态读取
 * @param[in] 
 * @param[out] 
 * @return     
 **********************************************************************/
#define MEAS_CFG_COEF_RDY 0X80 // 传感器内部校准值可读，在启动后
#define MEAS_CFG_SENSOR_RDY 0X40 // 传感器已初始化完成，在启动后
#define MEAS_CFG_TMP_RDY 0x20 //温度值已经准备就绪，可以进行读取，该标志位读取后自动清0
#define MEAS_CFG_PRS_RDY 0x10 //气压值已经准备就绪，可以进行读取，该标志位
#define MEAS_CFG_MEAS_CTR_STANDBY 0 //模式配置 挂起模式
#define MEAS_CFG_MEAS_CTR_COMMAND_PRS 0x01 //模式配置 命令模式下启动气压采集
#define MEAS_CFG_MEAS_CTR_COMMAND_TMP 0x02 //模式配置 命令模式下启动温度采集
#define MEAS_CFG_MEAS_CTR_BACKGROUND_PRS 0x05 //模式配置 后台模式只读取气压值
#define MEAS_CFG_MEAS_CTR_BACKGROUND_TMP 0X06 //模式配置 后台模式只读取温度值
#define MEAS_CFG_MEAS_CTR_BACKGROUND_PSR_TMP 0X07 //模式配置 后台模式同时读取温度值和气压值
//获取传感器数据就位状态//传感器就绪状态
u8 spl06_get_measure_status(void)
{
	return spl0601_read( MEAS_CFG_REG);
}
//设置读取模式+读取方式
void spl06_set_measure_mode(u8 mode)  //参数为模式值
{
	 spl0601_write( MEAS_CFG_REG,mode);
}
//启动命令模式读取温度值
void spl06_start_temperature(void)
{
    spl0601_write( MEAS_CFG_REG, MEAS_CFG_MEAS_CTR_COMMAND_TMP);
}
//启动命令模式读取气压值
void spl06_start_pressure(void)
{
    spl0601_write(MEAS_CFG_REG, MEAS_CFG_MEAS_CTR_COMMAND_PRS);
}
//进入待机模式，进入后停止采集数据直到再次切换模式
void spl06_enter_standby(void)
{
    spl0601_write( MEAS_CFG_REG, MEAS_CFG_MEAS_CTR_STANDBY);
}

/***********************************************************************
 * 中断与FIFO配置、SPI模式配置
 * @param[in] 
 * @param[out] 
 * @return     
 **********************************************************************/
#define CFG_INT_LEVEL_ACTIVE_LOW 0//中断低电平有效
#define CFG_INT_LEVEL_ACTIVE_HIGH 1//中断高电平有效
#define CFG_INT_FIFO 0X40    //当FIFO满使能中断 
#define CFG_INT_PRS 0X20    //当气压计读取完毕使能中断 
#define CFG_INT_TMP 0X10    //当温度读取完毕使能中断 
#define CFG_T_SHIFT 0X08    //允许数据被覆盖，可以进行下一笔采集
#define CFG_P_SHIFT 0X04    //允许数据被覆盖，可以进行下一笔采集
#define CFG_FIF 0X02    //使能FIFO
#define CFG_SPI_3_WIRE 1    //3线SPI
#define CFG_SPI_4_WIRE 0    //4线SPI

void spl06_set_interrupt(u8 interrupt,u8 type)//设置中断使能
{
	u8 data;
	data = spl0601_read( CFG_REG);
	if(type!=ENABLE )
		data &= ~interrupt;
	else
		data |= interrupt;	
	spl0601_write( CFG_REG,data);
}

void spl06_set_spi_wire(u8 wire)//设置SPI线数 //3线/4线SPI读取数据
{
	u8 data;
	data = spl0601_read(CFG_REG);
	data &= 0xf7;//SPI线配置所在位清0
	data |= wire;
	spl0601_write( CFG_REG,data);
}

void spl06_set_intrupt_level(u8 level)//设置中断有效电平//INT高电平有效或者低电平有效//level为0则低电平有效,为1则高电平有效
{
	u8 data;
	data = spl0601_read( CFG_REG);
	data &= 0x7f;//中断电平有效位清0
	data |= level<<7;
	spl0601_write( CFG_REG,data);
}

/***********************************************************************
 * 中断状态获取。由硬件置1，并发生相关引脚中断，读取该寄存器自动清0
 * @param[in] 
 * @param[out] 
 * @return     
 **********************************************************************/
#define INT_STS_FIFO_FULL  0X04 //FIFO满中断状态
#define INT_STS_FIFO_TMP   0X02  //温度测量完成标志位
#define INT_STS_FIFO_PRS  0X01  //气压测量完成标志位

u8 spl06_get_int_status(void)//读取传感器状态
{
	return spl0601_read( INT_STS_REG);
}

/***********************************************************************
 * FIFO状态获取。
 * @param[in] 
 * @param[out] 
 * @return     
 **********************************************************************/
#define FIFO_STS_FULL  0X02 //FIFO满
#define FIFO_STS_EMPTY   0X01 //FIFO空满
u8 spl06_get_fifo_status(void)
{
	return spl0601_read( FIFO_STS_REG);
}
/***********************************************************************
 *复位
 * @param[in] 
 * @param[out] 
 * @return     
 **********************************************************************/
#define RESET_FIFO_FLUSH 0X80 //FIFO清0
#define RESET_SOFT 0X09//软件复位

void spl06_soft_reset(void)//软件复位
{
	 spl0601_write(RESET_REG,RESET_SOFT);
}
void spl06_reset_fifo(void)//软件清FIFO
{
  spl0601_write(RESET_REG,RESET_FIFO_FLUSH);
}
/***********************************************************************
 *ID
 * @param[in] 
 * @param[out] 
 * @return     
 **********************************************************************/
#define PRODUCT_ID 0X10//产品ID
u8 spl06_get_chip_id(void)//获取产品ID//获取产品版本//由于版本在不同的传感器有不同，本历程只判断ID来识别SPL06
{
	return spl0601_read( ID_REG);
}

/***********************************************************************
 * 获取气压计内部的校准参数
 * @param[in] 
 * @param[out] 
 * @return     
 **********************************************************************/
void spl0601_get_calib_param(void)//内部校准值//气压计解算以及温补使用//由内部出厂设定
{
    unsigned long h;
    unsigned long m;
    unsigned long l;
    h =  spl0601_read( 0x10);
    l  =  spl0601_read(  0x11);
    spl06_calib_param.c0 = (int16)h<<4 | l>>4;
    spl06_calib_param.c0 = (spl06_calib_param.c0&0x0800)?(0xF000|spl06_calib_param.c0):spl06_calib_param.c0;
    h =  spl0601_read(  0x11);
    l  =  spl0601_read(  0x12);
    spl06_calib_param.c1 = (int16)(h&0x0F)<<8 | l;
    spl06_calib_param.c1 = (spl06_calib_param.c1&0x0800)?(0xF000|spl06_calib_param.c1):spl06_calib_param.c1;
    h =  spl0601_read(  0x13);
    m =  spl0601_read(  0x14);
    l =  spl0601_read(  0x15);
    spl06_calib_param.c00 = (int32)h<<12 | (int32)m<<4 | (int32)l>>4;
    spl06_calib_param.c00 = (spl06_calib_param.c00&0x080000)?(0xFFF00000|spl06_calib_param.c00):spl06_calib_param.c00;
    h =  spl0601_read(  0x15);
    m =  spl0601_read(  0x16);
    l =  spl0601_read(  0x17);
    spl06_calib_param.c10 = (int32)h<<16 | (int32)m<<8 | l;
    spl06_calib_param.c10 = (spl06_calib_param.c10&0x080000)?(0xFFF00000|spl06_calib_param.c10):spl06_calib_param.c10;
    h =  spl0601_read(  0x18);
    l  =  spl0601_read(  0x19);
    spl06_calib_param.c01 = (int16)h<<8 | l;
    h =  spl0601_read(  0x1A);
    l  =  spl0601_read(  0x1B);
    spl06_calib_param.c11 = (int16)h<<8 | l;
    h =  spl0601_read(  0x1C);
    l  =  spl0601_read(  0x1D);
    spl06_calib_param.c20 = (int16)h<<8 | l;
    h =  spl0601_read(  0x1E);
    l  =  spl0601_read(  0x1F);
    spl06_calib_param.c21 = (int16)h<<8 | l;
    h =  spl0601_read(  0x20);
    l  =  spl0601_read(  0x21);
    spl06_calib_param.c30 = (int16)h<<8 | l;
}
/***********************************************************************
 * 初始化
 * @param[in] 
 * @param[out] 
 * @return     
 **********************************************************************/
u8 spl0601_init(void)
{
		u8 spl06_start_status;
		//等待内部校准数据可用
		do
			spl06_start_status = spl06_get_measure_status();//读取气压计启动状态
		while((spl06_start_status&MEAS_CFG_COEF_RDY)!=MEAS_CFG_COEF_RDY);
		//读取内部校准值	
    spl0601_get_calib_param();	
		//等待传感器内部初始化完成
		do
			spl06_start_status = spl06_get_measure_status();//读取气压计启动状态
		while((spl06_start_status&MEAS_CFG_SENSOR_RDY)!=MEAS_CFG_SENSOR_RDY);
		//读取CHIP ID
	  spl06.chip_id = spl06_get_chip_id();
		//判断读取的ID是否正确，这里只判断高4位的ID，不判断低4位的版本号
		if((spl06.chip_id&0xf0)!=PRODUCT_ID)
			return FAILED;//如果ID读取失败，则返回失败
		//后台数据采样速率128HZ 过采样率32次
	  spl06_pressure_rate_config(PRESSURE_RATE_128_TIMES,PRESSURE_RATE_32_TIMES);
		//后台数据采样速率32HZ 过采样率8次//设置传感器上的温度计作为温度采集
	  spl06_temperature_rate_config(TEMPERATURE_RATE_32_TIMES,TEMPERATURE_RATE_8_TIMES,TEMPERATURE_RATE_TMP_EXT_EXTERNAL);
		//启动后台读取数据
		spl06_set_measure_mode(MEAS_CFG_MEAS_CTR_BACKGROUND_PSR_TMP);
		return SUCCESS;//初始化成功
}


/***********************************************************************
 * 获取原始温度值
 * @param[in] 
 * @param[out] 
 * @return     
 **********************************************************************/
void spl0601_get_raw_temp(void)
{
    uint8 h[3] = {0};
    
		h[0] = spl0601_read(  0x03);
		h[1] = spl0601_read(  0x04);
		h[2] = spl0601_read(  0x05);

    spl06.i32rawTemperature = (int32)h[0]<<16 | (int32)h[1]<<8 | (int32)h[2];
    spl06.i32rawTemperature= (spl06.i32rawTemperature&0x800000) ? (0xFF000000|spl06.i32rawTemperature) : spl06.i32rawTemperature;
}

/***********************************************************************
 * 获取原始气压值
 * @param[in] 
 * @param[out] 
 * @return     
 **********************************************************************/
void spl0601_get_raw_pressure(void)
{
    uint8 h[3];
    
		h[0] = spl0601_read(  0x00);
		h[1] = spl0601_read(  0x01);
		h[2] = spl0601_read(  0x02);
    
    spl06.i32rawPressure = (int32)h[0]<<16 | (int32)h[1]<<8 | (int32)h[2];
    spl06.i32rawPressure= (spl06.i32rawPressure&0x800000) ? (0xFF000000|spl06.i32rawPressure) : spl06.i32rawPressure;
}


/***********************************************************************
 * 温度解算值
 * @param[in] 
 * @param[out] 
 * @return     
 **********************************************************************/
float spl0601_get_temperature(void)
{
    float fTCompensate;
    float fTsc;

    fTsc = spl06.i32rawTemperature / (float)spl06.i32kT;
    fTCompensate =  spl06_calib_param.c0 * 0.5 + spl06_calib_param.c1 * fTsc;
    return fTCompensate;
}

/***********************************************************************
 * 气压解算并进行温度补偿
 * @param[in] 
 * @param[out] 
 * @return     
 **********************************************************************/
float spl0601_get_pressure(void)
{
    float fTsc, fPsc;
    float qua2, qua3;
    float fPCompensate;

    fTsc = spl06.i32rawTemperature / (float)spl06.i32kT;
    fPsc = spl06.i32rawPressure / (float)spl06.i32kP;
    qua2 = spl06_calib_param.c10 + fPsc * (spl06_calib_param.c20 + fPsc* spl06_calib_param.c30);
    qua3 = fTsc * fPsc * (spl06_calib_param.c11 + fPsc * spl06_calib_param.c21);
		//qua3 = 0.9f *fTsc * fPsc * (spl06_calib_param.c11 + fPsc * spl06_calib_param.c21);
	
    fPCompensate = spl06_calib_param.c00 + fPsc * qua2 + fTsc * spl06_calib_param.c01 + qua3;
		//fPCompensate = spl06_calib_param.c00 + fPsc * qua2 + 0.9f *fTsc  * spl06_calib_param.c01 + qua3;
    return fPCompensate;
}



/***********************************************************************
 * 获取温度值
 * @param[in] 
 * @param[out] 
 * @return     
 **********************************************************************/
float user_spl0601_get_temperature()
{
		spl0601_get_raw_temp();//读取温度原始值
		return spl0601_get_temperature();//温度解算后的值
}
/***********************************************************************
 * 获取气压计温度补偿值
 * @param[in] 
 * @param[out] 
 * @return     
 **********************************************************************/
float user_spl0601_get_presure()
{
		spl0601_get_raw_pressure();//读取气压值原始值
		return spl0601_get_pressure();	//气压解算并经过温度补偿后的气压值
}

#endif
