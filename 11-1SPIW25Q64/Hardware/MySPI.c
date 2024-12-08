#include "stm32f10x.h"                  // Device header

/**
   * @brief   SPI协议中控制SS引脚电平
   * @param   BitValue:表示高低电平（0/1)
   * @retval  无
   */
void MySPI_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)BitValue);
}


/**
   * @brief   SPI协议中控制SCK引脚电平
   * @param   BitValue:表示高低电平（0/1)
   * @retval  无
   */
void MySPI_W_SCK(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)BitValue);
}



/**
   * @brief   SPI协议中控制MOSI引脚电平
   * @param   BitValue:表示高低电平（0/1)
   * @retval  无
   */
void MySPI_W_MOSI(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)BitValue);
}


/**
   * @brief  SPI协议中读取MISO引脚电平
   * @param  无
   * @retval 返回MISO引脚电平
   */
uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}


/**
   * @brief   对SPI的通信引脚进行初始化
   * @param   无
   * @retval  无
   */
void MySPI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //时钟使能
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //CS、CLK和MOSI引脚选择推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_7 ;   //引脚A4、引脚A5和引脚A7
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //MISO引脚选择上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;   //引脚A6
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	MySPI_W_SS(1);   //初始化SS引脚电平
	MySPI_W_SCK(0);  //初始化SCK引脚电平
}


/**
   * @brief   SPI协议中的初始化时序
   * @param   无
   * @retval  无
   */
void MySPI_Start(void)
{
	MySPI_W_SS(0);   	
}


/**
   * @brief   SPI协议中的终止时序
   * @param   无
   * @retval  无
   */
void MySPI_Stop(void)
{
	MySPI_W_SS(1);   	
}

/**
   * @brief   SPI协议中主从机交换一个字节
   * @param   ByteSend:主机发送的字节
   * @retval  主机接收的字节
   */
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	uint8_t i,ByteReceive = 0x00;

	
	for(i=0;i<8;i++)
	{
		MySPI_W_MOSI(ByteSend & 0x80>>i);  //通过屏蔽无关位来挑选我们需要的位,这种方式称为掩码
		MySPI_W_SCK(1);  
		if(MySPI_R_MISO()==1){ ByteReceive |= (0x80>>i);}
		MySPI_W_SCK(0); 
	}
 
	
	return ByteReceive;
}


///**
//   * @brief   SPI协议中主从机交换一个字节(移位模型版)
//   * @param   ByteSend:主机发送的字节
//   * @retval  主机接收的字节
//   */
//uint8_t MySPI_SwapByte(uint8_t ByteSend)
//{
//	uint8_t i;

//	
//	for(i=0;i<8;i++)
//	{
//		MySPI_W_MOSI(ByteSend & 0x80);     //移位数据本身来设置我们需要的位
//		ByteSend<<=1;
//		MySPI_W_SCK(1);  
//		if(MySPI_R_MISO()==1){ ByteSend |= 0x01;}
//		MySPI_W_SCK(0); 
//	}
// 
//	
//	return ByteSend;
//}


//SPI模式1
//uint8_t MySPI_SwapByte(uint8_t ByteSend)
//{
//	uint8_t i,ByteReceive = 0x00;
//	
//	for(i=0;i<8;i++)
//	{
//		MySPI_W_SCK(1);  
//		MySPI_W_MOSI(ByteSend & 0x80>>i);  //通过屏蔽无关位来挑选我们需要的位,这种方式称为掩码
//		MySPI_W_SCK(0); 
//		if(MySPI_R_MISO()==1){ ByteReceive |= (0x80>>i);}
//	}
// 
//	
//	return ByteReceive;
//}




