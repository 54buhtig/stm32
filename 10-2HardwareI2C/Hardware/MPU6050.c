#include "stm32f10x.h"                  // Device header
#include "MPU6050_Reg.h"


#define  MPU6050_ADDRESS  0xD0

/**
   * @brief   ���г�ʱ�˳����Ƶ�CheakEvent����
   * @param   I2Cx:����ʱI2C1��I2C2
   EVENT:����������ѡ��
  *     @arg I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED           : EV1
  *     @arg I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED              : EV1
  *     @arg I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED     : EV1
  *     @arg I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED        : EV1
  *     @arg I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED            : EV1
  *     @arg I2C_EVENT_SLAVE_BYTE_RECEIVED                         : EV2
  *     @arg (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_DUALF)      : EV2
  *     @arg (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_GENCALL)    : EV2
  *     @arg I2C_EVENT_SLAVE_BYTE_TRANSMITTED                      : EV3
  *     @arg (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUALF)   : EV3
  *     @arg (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_GENCALL) : EV3
  *     @arg I2C_EVENT_SLAVE_ACK_FAILURE                           : EV3_2
  *     @arg I2C_EVENT_SLAVE_STOP_DETECTED                         : EV4
  *     @arg I2C_EVENT_MASTER_MODE_SELECT                          : EV5
  *     @arg I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED            : EV6     
  *     @arg I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED               : EV6
  *     @arg I2C_EVENT_MASTER_BYTE_RECEIVED                        : EV7
  *     @arg I2C_EVENT_MASTER_BYTE_TRANSMITTING                    : EV8
  *     @arg I2C_EVENT_MASTER_BYTE_TRANSMITTED                     : EV8_2
  *     @arg I2C_EVENT_MASTER_MODE_ADDRESS10                       : EV9
   * @retval
   */
void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
	uint32_t Timeout;
	Timeout=10000;
	while(I2C_CheckEvent(I2Cx,I2C_EVENT)!=SUCCESS)  //���EV5�¼�
	{
		Timeout--;
		if(Timeout==0)
		{
			break;  //����ѭ��  �򵥵ļƴμ�ʱ,��ʱ�˳��Ļ���
//			return ; //������������
			//�ڹ�����Ŀ������Ӧ�ü�����Ӧ�Ĵ��������,�����ӡ������־��ϵͳ��λ������ͣ��
		}
	}
}




/**
   * @brief     ��ָ����ַд������
   * @param     RegAddrss:Ҫд��ļĴ�����ַ
                Data:��Ҫд�������
   * @retval    ��
   */
void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)
{

	I2C_GenerateSTART(I2C2,ENABLE);  //��ʼ������
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);  //���EV5�¼�
	
	
	I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Transmitter);//���ʹӻ���ַ
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);  //���EV6�¼�
	
	I2C_SendData(I2C2,RegAddress);
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING);  //���EV8�¼�
	
	I2C_SendData(I2C2,Data);
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED);  //���EV8_2�¼�
		
	I2C_GenerateSTOP(I2C2,ENABLE);   //��ֹ����
	
}



/**
   * @brief     ��ָ����ַ��ȡ����
   * @param     RegAddrss:Ҫ��ȡ�ļĴ�����ַ
   * @retval    ���ض�ȡ������
   */
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;

	I2C_GenerateSTART(I2C2,ENABLE);  //��ʼ������
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);  //���EV5�¼�
	
	I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Transmitter);//���ʹӻ���ַ
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);  //���EV6�¼�
	
	I2C_SendData(I2C2,RegAddress);
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED);  //���EV8_2�¼�

	I2C_GenerateSTART(I2C2,ENABLE);  //�ظ���ʼ������
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);  //���EV5�¼�

	I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Receiver);//���ʹӻ���ַ
	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);  //���EV6�¼�


	I2C_AcknowledgeConfig(I2C2,DISABLE);//ֻ����һ���ֽ�ʱ,��ǰ����Ack,��Ack��0
	I2C_GenerateSTOP(I2C2,ENABLE);   //��ǰ����ֹͣ����


	MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED);  //���EV7�¼�
	Data = I2C_ReceiveData(I2C2);
	
	I2C_AcknowledgeConfig(I2C2,ENABLE);  //��Ack��1,��ΪĬ����Ack������1,Ϊ�˷���ָ����ַ���ն��ֽ�
	return Data;
}


/**
   * @brief  MPU6050ģ��ĳ�ʼ��
   * @param  ��
   * @retval ��
   */
void MPU6050_Init(void)
{
		
	//��1��������I2C��GPIO���ŵ�ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	
	//��2������������Ϊ��©����ģʽ
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;  //��©���ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 |GPIO_Pin_11 ;   //����B10 ������B11
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//��3��:����I2C�ڲ��Ĳ���
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
	I2C_InitStructure.I2C_AcknowledgedAddress= I2C_AcknowledgedAddress_7bit;  //7λ��ַ
	I2C_InitStructure.I2C_ClockSpeed= 50000;  //50Khz
	I2C_InitStructure.I2C_DutyCycle= I2C_DutyCycle_2 ; 
	I2C_InitStructure.I2C_Mode=I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;  //�ӻ���ַ
	I2C_Init(I2C2,&I2C_InitStructure);
	
	//��4��:ʹ��I2C
	I2C_Cmd(I2C2,ENABLE);
	
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

















