#include "stm32f10x.h"                  // Device header
#include "MyI2C.h"                 
#include "MPU6050_Reg.h"


#define  MPU6050_ADDRESS  0xD0



/**
   * @brief     ��ָ����ַд������
   * @param     RegAddrss:Ҫд��ļĴ�����ַ
                Data:��Ҫд�������
   * @retval    ��
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
   * @brief     ��ָ����ַ��ȡ����
   * @param     RegAddrss:Ҫ��ȡ�ļĴ�����ַ
   * @retval    ���ض�ȡ������
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
   * @brief  MPU6050ģ��ĳ�ʼ��
   * @param  ��
   * @retval ��
   */
void MPU6050_Init(void)
{
	MyI2C_Init();	
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);   //��Դ1���ø�0x01,ѡ��X����������Ϊʱ��,�ر�˯��ģʽ
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);   //��Դ2���ø�0x00,�����ر�
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);   //�����ʷ�Ƶ, 10��Ƶ
	MPU6050_WriteReg(MPU6050_CONFIG,0x06);       //MPU6050����, �ⲿͬ���ر�,���ֵ�ͨ�˲���110
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);  //�ر��������Բ�, ����ѡ���
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18); //�رռ������Բ�, ����ѡ���,�رո�ͨ�˲�
}


uint8_t MPU6050_GetID(void)
{
	return  MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

/**
   * @brief    ��ȡMPU6050���ٶȺͽ��ٶȼĴ���������
   * @param    �����Ǵ�ż��ٶȺͽ��ٶ�X,Y,Z������ݵ�ַ
   * @retval   ��
   */
void MPU6050_GetData(int16_t* AccX,int16_t* AccY,int16_t* AccZ,
				     int16_t* GyroX,int16_t* GyroY,int16_t* GyroZ)
{
	uint8_t DataH,DataL;
	
	//���ٶ�X��
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH<<8)  |  DataL;

	//���ٶ�Y��
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH<<8)  |  DataL;

	//���ٶ�Z��
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH<<8)  |  DataL;

	//���ٶ�X��
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH<<8)  |  DataL;

	//���ٶ�Y��
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH<<8)  |  DataL;

	//���ٶ�Z��
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	*GyroZ = (DataH<<8)  |  DataL;

}

















