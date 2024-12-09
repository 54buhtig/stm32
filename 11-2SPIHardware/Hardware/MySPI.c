#include "stm32f10x.h"                  // Device header

/**
   * @brief   SPIЭ���п���SS���ŵ�ƽ
   * @param   BitValue:��ʾ�ߵ͵�ƽ��0/1)
   * @retval  ��
   */
void MySPI_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)BitValue);
}



/**
   * @brief   ��SPI��ͨ�����Ž��г�ʼ��
   * @param   ��
   * @retval  ��
   */
void MySPI_Init(void)
{
	//��1��������GPIO��SPI��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //GPIOʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);   //SPIʱ��ʹ��
	
	//��2������ʼ��GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //CS����ѡ��ͨ���������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;   //����A4
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //SCK��MOSI����ѡ�����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;   //����A5������A7
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //MISO����ѡ����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;   //����A6
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//��3������ʼ��SPI������
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
	
	
	
	//��4����SPI����ʹ��
	SPI_Cmd(SPI1,ENABLE);


	MySPI_W_SS(1); //��SS��ʼ����ƽ

}


/**
   * @brief   SPIЭ���еĳ�ʼ��ʱ��
   * @param   ��
   * @retval  ��
   */
void MySPI_Start(void)
{
	MySPI_W_SS(0);   	
}


/**
   * @brief   SPIЭ���е���ֹʱ��
   * @param   ��
   * @retval  ��
   */
void MySPI_Stop(void)
{
	MySPI_W_SS(1);   	
}

/**
   * @brief   SPIЭ�������ӻ�����һ���ֽ�
   * @param   ByteSend:�������͵��ֽ�
   * @retval  �������յ��ֽ�
   */
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)!=SET);
	SPI_I2S_SendData(SPI1,ByteSend);   //���ͺͽ�����ͬʱ���е�,����ֻ���ý��պ���
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)!=SET);
	
	return SPI_I2S_ReceiveData(SPI1);//���ͺͽ�����ͬʱ���е�,����ֻ���ý��պ���
}


///**
//   * @brief   SPIЭ�������ӻ�����һ���ֽ�(��λģ�Ͱ�)
//   * @param   ByteSend:�������͵��ֽ�
//   * @retval  �������յ��ֽ�
//   */
//uint8_t MySPI_SwapByte(uint8_t ByteSend)
//{
//	uint8_t i;

//	
//	for(i=0;i<8;i++)
//	{
//		MySPI_W_MOSI(ByteSend & 0x80);     //��λ���ݱ���������������Ҫ��λ
//		ByteSend<<=1;
//		MySPI_W_SCK(1);  
//		if(MySPI_R_MISO()==1){ ByteSend |= 0x01;}
//		MySPI_W_SCK(0); 
//	}
// 
//	
//	return ByteSend;
//}


//SPIģʽ1
//uint8_t MySPI_SwapByte(uint8_t ByteSend)
//{
//	uint8_t i,ByteReceive = 0x00;
//	
//	for(i=0;i<8;i++)
//	{
//		MySPI_W_SCK(1);  
//		MySPI_W_MOSI(ByteSend & 0x80>>i);  //ͨ�������޹�λ����ѡ������Ҫ��λ,���ַ�ʽ��Ϊ����
//		MySPI_W_SCK(0); 
//		if(MySPI_R_MISO()==1){ ByteReceive |= (0x80>>i);}
//	}
// 
//	
//	return ByteReceive;
//}




