#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>


uint8_t  Serial_RxFlag;
uint8_t  Serial_TxPacket[4];
uint8_t  Serial_RxPacket[4];


/**
   * @brief    ��ʼ������
   * @param    ��
   * @retval   ��
   */
void Serial_Init(void)
{
	//��1��:����USART��GPIO��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	//��2��:��ʼ��GPIO��PA9���� TX����
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9  ;   //����A9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10  ;   //����A10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//��3��:��ʼ��USART
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl =  USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx  ;  //ѡ��Tx��Rx��Ϊģʽ
	USART_InitStructure.USART_Parity = USART_Parity_No  ; 
	USART_InitStructure.USART_StopBits = USART_StopBits_1 ;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b ;
	USART_Init(USART1,&USART_InitStructure);
	
	
	
	
	// �����жϵķ���ʵ�ִ��ڽ�������
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);	//���ô����жϣ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC
	NVIC_InitTypeDef NVIC_InitStructure;//��ʼ��NVIC��
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd =  ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;
	NVIC_Init(&NVIC_InitStructure);
	
	//��4��:ʹ��USART
	USART_Cmd(USART1,ENABLE);
}


/**
   * @brief    ���ڷ���һ���ַ�
   * @param    Byte:Ҫ���͵��ַ���Ϣ
   * @retval   ��
   */
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

/**
   * @brief    ���ڷ���һ������
* @param    Array:����������׵�ַ
            Length:��������ĸ���
   * @retval
   */
void Serial_SendArray(uint8_t* Array, uint16_t Length)
{
	uint16_t i;
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Array[i]);
	}
}


/**
   * @brief   ���ڷ����ַ���
   * @param   String:�����ַ������׵�ַ
   * @retval  ��
   */
void Serial_SendString(char* String)
{
	uint8_t i;
	for(i=0;String[i]!= 0;i++)
	{
		Serial_SendByte(String[i]);
	}
}


/**
   * @brief    ����ģ���ָ������
   * @param    X:����
               Y:ָ��
   * @retval   ����ָ�������Ľ��
   */
uint32_t Serial_Pow(uint32_t X,uint32_t Y)
{
	uint32_t result = 1;
	while(Y--)
	{
		result*=X;
	}
	return result;
}


/**
   * @brief    ���ڷ�������
   * @param Number:Ҫ��������
            Length:�������ֵĳ���
   * @retval
   */
void Serial_SendNumber(uint32_t Number,uint8_t Length )
{
	uint8_t i;
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Number/Serial_Pow(10,Length-i-1)%10+'0');
	}
}


/**
   * @brief    ��print���������ض���,���º�����fputc��ԭ��,fputc��
			   printf�����ĵײ�,	
   * @param
   * @retval
   */
int fputc(int ch,FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}


/**
   * @brief   ��װ��Sprintf����
   * @param
   * @retval
   */
void Serial_Printf(char* format,...)
{
	char String[100];
	va_list arg;    //va_list����������
	va_start(arg,format);   //��formatλ�ÿ�ʼ���ղ���������arg����
	vsprintf(String,format,arg);  //Ҫ��vsprintf����,��Ϊsprintf����ֻ�ܽ��ճ���(ֱ��д���ַ��ͱ���)
	va_end(arg); //�ͷŲ�����
	Serial_SendString(String);  //�����ַ���
}

/**
   * @brief   ����TxPacket�����ݲ����ϰ�ͷ��β
   * @param   ��
   * @retval  ��
   */
void Serial_SendPacket(void)
{
	Serial_SendByte(0xFF);   //���Ͱ�ͷ
	Serial_SendArray(Serial_TxPacket,4);
	Serial_SendByte(0xFE);  //���Ͱ�β
}

/**
   * @brief   ��ȡ������Ϣ��־λ
   * @param   ��
   * @retval  ���ر�־λ(1/0	)
   */
uint8_t Serial_GetRxFlag(void)
{
	if(Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}



/**
   * @brief   USART1���жϺ���
   * @param   ��
   * @retval  ��
   */
void USART1_IRQHandler(void)
{
	static uint8_t RxState = 0;   //ֻ���ʼ��1��
	static uint8_t pRxPacket = 0;   //ֻ���ʼ��1��

	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		uint8_t RxData = USART_ReceiveData(USART1);	
		if(RxState == 0)  //�ȴ���ͷ
		{
			if(RxData==0xFF)
			{
				RxState = 1;
				pRxPacket = 0;
			} 
		}
		else if(RxState == 1) //��������
		{
			Serial_RxPacket[pRxPacket] = RxData;
			pRxPacket++;
			if(pRxPacket>=4)
			{
				RxState = 2;
			}
		}
		else if(RxState == 2)  //�ȴ���β
		{
			if(RxData == 0xFE)  //��β
			{
				RxState  = 0;
				Serial_RxFlag = 1; //���ݰ����ձ�־
			}
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);  //�ֶ��Ա�־λ����
	}
}


