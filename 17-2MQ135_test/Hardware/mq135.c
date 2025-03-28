#include "stm32f10x.h"                  // Device header
#include "mq135.h"
#include "Delay.h"


 
void MQ135_Init(void)
{
	#if MODE
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_APB2PeriphClockCmd (MQ135_AO_GPIO_CLK, ENABLE );	// 打开 ADC IO端口时钟
		GPIO_InitStructure.GPIO_Pin = MQ135_AO_GPIO_PIN;					// 配置 ADC IO 引脚模式
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		// 设置为模拟输入
		
		GPIO_Init(MQ135_AO_GPIO_PORT, &GPIO_InitStructure);				// 初始化 ADC IO
 
		AD_Init();    //修改1
	}
	#else
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_APB2PeriphClockCmd (MQ135_DO_GPIO_CLK, ENABLE );	// 打开连接 传感器DO 的单片机引脚端口时钟
		GPIO_InitStructure.GPIO_Pin = MQ135_DO_GPIO_PIN;			// 配置连接 传感器DO 的单片机引脚模式
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			// 设置为上拉输入
		
		GPIO_Init(MQ135_DO_GPIO_PORT, &GPIO_InitStructure);				// 初始化 
		
	}
	#endif
	
}
 
#if MODE
uint16_t MQ135_ADC_Read(void)
{
	//设置指定ADC的规则组通道，采样时间  修改2
	return AD_GetValue();
}
#endif
 
uint16_t MQ135_GetData(void)
{
	
	#if MODE
	uint32_t  tempData = 0;
	for (uint8_t i = 0; i < MQ135_READ_TIMES; i++)
	{
		tempData += MQ135_ADC_Read();
		Delay_ms(5);
	}
 
	tempData /= MQ135_READ_TIMES;
	return tempData;
	
	#else
	uint16_t tempData;
	tempData = !GPIO_ReadInputDataBit(MQ135_DO_GPIO_PORT, MQ135_DO_GPIO_PIN);
	return tempData;
	#endif
}
 
 
float MQ135_GetData_PPM(void)
{
	#if MODE
	float  tempData = 0;
	
 
	for (uint8_t i = 0; i < MQ135_READ_TIMES; i++)
	{
		tempData += MQ135_ADC_Read();
		Delay_ms(5);
	}
	tempData /= MQ135_READ_TIMES;
	
	float Vol = (tempData*5/4096);
	float RS = (5-Vol)/(Vol*0.5);
	float R0=6.64;
	
	float ppm = pow(11.5428*R0/RS, 0.6549f);
	
	return ppm;
	#endif
}


