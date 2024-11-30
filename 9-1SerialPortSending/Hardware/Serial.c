#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>


/**
   * @brief    初始化串口
   * @param    无
   * @retval   无
   */
void Serial_Init(void)
{
	//第1步:开启USART和GPIO的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	//第2步:初始化GPIO的PA9引脚 TX引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9  ;   //引脚A9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//第3步:初始化USART
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl =  USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx ;  //选择Tx作为模式
	USART_InitStructure.USART_Parity = USART_Parity_No  ; 
	USART_InitStructure.USART_StopBits = USART_StopBits_1 ;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b ;
	USART_Init(USART1,&USART_InitStructure);
	
	//第4步:使能USART
	USART_Cmd(USART1,ENABLE);
}


/**
   * @brief    串口发送一个字符
   * @param    Byte:要发送的字符信息
   * @retval   无
   */
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

/**
   * @brief    串口发送一个数组
* @param    Array:发送数组的首地址
            Length:发送数组的个数
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
   * @brief   串口发送字符串
   * @param   String:发送字符串的首地址
   * @retval  无
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
   * @brief    串口模块的指数函数
   * @param    X:底数
               Y:指数
   * @retval   返回指数函数的结果
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
   * @brief    串口发送数字
   * @param Number:要发送数字
            Length:发送数字的长度
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
   * @brief    对print函数进行重定向,以下函数是fputc的原型,fputc是
			   printf函数的底层,	
   * @param
   * @retval
   */
int fputc(int ch,FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}


/**
   * @brief   封装的Sprintf函数
   * @param
   * @retval
   */
void Serial_Printf(char* format,...)
{
	char String[100];
	va_list arg;    //va_list是数据类型
	va_start(arg,format);   //从format位置开始接收参数表，放在arg里面
	vsprintf(String,format,arg);  //要用vsprintf函数,因为sprintf函数只能接收常量(直接写的字符和变量)
	va_end(arg); //释放参数表
	Serial_SendString(String);  //发送字符串
}


