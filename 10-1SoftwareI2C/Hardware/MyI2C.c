#include "stm32f10x.h"                  // Device header
#include "Delay.h"


/**
   * @brief   MyI2C�ڲ�ʹ�õ�дSCL����   
   * @param   BitValue (��ƽ) ֵ:������0/1
   * @retval  ��
   */
void MyI2C_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	Delay_us(10);
}


/**
   * @brief   MyI2C�ڲ�ʹ�õ�дSDA����   
   * @param   BitValue (��ƽ) ֵ:������0/1
   * @retval  ��
   */
void MyI2C_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	Delay_us(10);
}

/**
   * @brief   MyI2C�ڲ�ʹ�õĶ�SDA����
   * @param   ��
   * @retval  ���ص�ƽ�ź�
   */
uint8_t MyI2C_R_SDA(void)
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
	return  BitValue;
}


/**
   * @brief   ��I2Cͨ�Ž���������ʼ��
   * @param   ��
   * @retval  ��
   */
void MyI2C_Init(void)
{
	
	//��1������SDA��SCL���Ž������ã����øߵ�ƽ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //ʱ��ʹ��
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;    //�������ÿ�©���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 |GPIO_Pin_11 ;   //����B10 ������B11
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
}



/**
   * @brief    I2CЭ���еĳ�ʼ����
   * @param    ��
   * @retval   ��
   */
void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}


/**
   * @brief   I2CЭ���е���ֹ����
   * @param   ��
   * @retval  ��
   */
void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

/**
   * @brief  I2CЭ���з���һ���ֽ�
   * @param  Byte (��Ҫ���͵��ֽ�)
   * @retval ��
   */
void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		MyI2C_W_SDA(Byte & (0x80>>i));
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);	
	}	
}


/**
   * @brief  I2CЭ���з���һ���ֽ�
   * @param  ��
   * @retval ���յ����ֽ�
   */
uint8_t MyI2C_ReceiveByte(void)
{
	uint8_t i,Byte = 0x00;
	MyI2C_W_SDA(1);
	for(i=0;i<8;i++)
	{
		MyI2C_W_SCL(1);
		if(MyI2C_R_SDA()==1)
		{
			Byte |= (0x80 >> i);
		}
		MyI2C_W_SCL(0);
	}
	return Byte;
}

/**
   * @brief  ����Ӧ��
   * @param  AckBit (����Ӧ��λ,����Ϊ0/1)
   * @retval ��
   */
void MyI2C_SendAck(uint8_t AckBit)
{

	MyI2C_W_SDA(AckBit)	;
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);	
	
}


/**
   * @brief  ����Ӧ��
   * @param  ��
   * @retval ����Ӧ��λ,����Ϊ0/1
   */
uint8_t MyI2C_ReceiveAck(void)
{
	uint8_t AckBit;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
    AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	return AckBit;
}








