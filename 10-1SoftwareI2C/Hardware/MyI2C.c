#include "stm32f10x.h"                  // Device header
#include "Delay.h"


/**
   * @brief   MyI2C内部使用的写SCL函数   
   * @param   BitValue (电平) 值:可以是0/1
   * @retval  无
   */
void MyI2C_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	Delay_us(10);
}


/**
   * @brief   MyI2C内部使用的写SDA函数   
   * @param   BitValue (电平) 值:可以是0/1
   * @retval  无
   */
void MyI2C_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	Delay_us(10);
}

/**
   * @brief   MyI2C内部使用的读SDA函数
   * @param   无
   * @retval  返回电平信号
   */
uint8_t MyI2C_R_SDA(void)
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
	return  BitValue;
}


/**
   * @brief   对I2C通信进行软件初始化
   * @param   无
   * @retval  无
   */
void MyI2C_Init(void)
{
	
	//第1步：对SDA和SCL引脚进行配置，并置高电平
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //时钟使能
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;    //引脚配置开漏输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 |GPIO_Pin_11 ;   //引脚B10 和引脚B11
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
}



/**
   * @brief    I2C协议中的初始条件
   * @param    无
   * @retval   无
   */
void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}


/**
   * @brief   I2C协议中的终止条件
   * @param   无
   * @retval  无
   */
void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

/**
   * @brief  I2C协议中发送一个字节
   * @param  Byte (需要发送的字节)
   * @retval 无
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
   * @brief  I2C协议中发送一个字节
   * @param  无
   * @retval 接收到的字节
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
   * @brief  发送应答
   * @param  AckBit (发送应答位,可以为0/1)
   * @retval 无
   */
void MyI2C_SendAck(uint8_t AckBit)
{

	MyI2C_W_SDA(AckBit)	;
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);	
	
}


/**
   * @brief  接收应答
   * @param  无
   * @retval 接收应答位,可以为0/1
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









