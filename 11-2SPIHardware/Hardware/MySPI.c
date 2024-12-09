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
   * @brief   对SPI的通信引脚进行初始化
   * @param   无
   * @retval  无
   */
void MySPI_Init(void)
{
	//第1步：开启GPIO和SPI的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //GPIO时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);   //SPI时钟使能
	
	//第2步：初始化GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //CS引脚选择通用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;   //引脚A4
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //SCK和MOSI引脚选择复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;   //引脚A5和引脚A7
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //MISO引脚选择上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;   //引脚A6
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//第3步：初始化SPI的配置
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_128;
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_Low;
	SPI_InitStructure.SPI_CRCPolynomial = 7 ;
	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;
	SPI_Init(SPI1,&SPI_InitStructure);
	
	
	
	//第4步：SPI开关使能
	SPI_Cmd(SPI1,ENABLE);


	MySPI_W_SS(1); //给SS初始化电平

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
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)!=SET);
	SPI_I2S_SendData(SPI1,ByteSend);   //发送和接收是同时进行的,不能只调用接收函数
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)!=SET);
	
	return SPI_I2S_ReceiveData(SPI1);//发送和接收是同时进行的,不能只调用接收函数
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




