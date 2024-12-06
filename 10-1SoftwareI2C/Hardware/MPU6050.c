#include "stm32f10x.h"                  // Device header
#include "MyI2C.h"                 
#include "MPU6050_Reg.h"


#define  MPU6050_ADDRESS  0xD0



/**
   * @brief     在指定地址写入数据
   * @param     RegAddrss:要写入的寄存器地址
                Data:需要写入的数据
   * @retval    无
   */
void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Data);
	MyI2C_ReceiveAck();	
	MyI2C_Stop();
}



/**
   * @brief     在指定地址读取数据
   * @param     RegAddrss:要读取的寄存器地址
   * @retval    返回读取的数据
   */
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);
	MyI2C_ReceiveAck();
	Data = MyI2C_ReceiveByte();
	MyI2C_SendAck(1);
	MyI2C_Stop();
	
	return Data;
}


/**
   * @brief  MPU6050模块的初始化
   * @param  无
   * @retval 无
   */
void MPU6050_Init(void)
{
	MyI2C_Init();	
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);   //电源1配置给0x01,选择X轴陀螺仪作为时钟,关闭睡眠模式
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);   //电源2配置给0x00,待机关闭
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);   //采样率分频, 10分频
	MPU6050_WriteReg(MPU6050_CONFIG,0x06);       //MPU6050配置, 外部同步关闭,数字低通滤波给110
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);  //关闭陀螺仪自测, 量程选最大
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18); //关闭加速器自测, 量程选最大,关闭高通滤波
}


uint8_t MPU6050_GetID(void)
{
	return  MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

/**
   * @brief    读取MPU6050加速度和角速度寄存器的数据
   * @param    参数是存放加速度和角速度X,Y,Z轴的数据地址
   * @retval   无
   */
void MPU6050_GetData(int16_t* AccX,int16_t* AccY,int16_t* AccZ,
				     int16_t* GyroX,int16_t* GyroY,int16_t* GyroZ)
{
	uint8_t DataH,DataL;
	
	//加速度X轴
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH<<8)  |  DataL;

	//加速度Y轴
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH<<8)  |  DataL;

	//加速度Z轴
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH<<8)  |  DataL;

	//角速度X轴
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH<<8)  |  DataL;

	//角速度Y轴
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH<<8)  |  DataL;

	//角速度Z轴
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	*GyroZ = (DataH<<8)  |  DataL;

}

















