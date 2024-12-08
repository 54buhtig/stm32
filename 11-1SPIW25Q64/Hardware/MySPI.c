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
   * @brief   SPIЭ���п���SCK���ŵ�ƽ
   * @param   BitValue:��ʾ�ߵ͵�ƽ��0/1)
   * @retval  ��
   */
void MySPI_W_SCK(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)BitValue);
}



/**
   * @brief   SPIЭ���п���MOSI���ŵ�ƽ
   * @param   BitValue:��ʾ�ߵ͵�ƽ��0/1)
   * @retval  ��
   */
void MySPI_W_MOSI(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)BitValue);
}


/**
   * @brief  SPIЭ���ж�ȡMISO���ŵ�ƽ
   * @param  ��
   * @retval ����MISO���ŵ�ƽ
   */
uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}


/**
   * @brief   ��SPI��ͨ�����Ž��г�ʼ��
   * @param   ��
   * @retval  ��
   */
void MySPI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //ʱ��ʹ��
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //CS��CLK��MOSI����ѡ���������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_7 ;   //����A4������A5������A7
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //MISO����ѡ����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;   //����A6
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	MySPI_W_SS(1);   //��ʼ��SS���ŵ�ƽ
	MySPI_W_SCK(0);  //��ʼ��SCK���ŵ�ƽ
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
	uint8_t i,ByteReceive = 0x00;

	
	for(i=0;i<8;i++)
	{
		MySPI_W_MOSI(ByteSend & 0x80>>i);  //ͨ�������޹�λ����ѡ������Ҫ��λ,���ַ�ʽ��Ϊ����
		MySPI_W_SCK(1);  
		if(MySPI_R_MISO()==1){ ByteReceive |= (0x80>>i);}
		MySPI_W_SCK(0); 
	}
 
	
	return ByteReceive;
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




