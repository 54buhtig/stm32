#include "stm32f10x.h"                  // Device header


uint16_t AD_Value[3];

/**
   * @brief   对ADC进行初始化
   * @param   无
   * @retval  无
   */
void AD_Init(void)
{
	//第1步：开启RCC时钟，引脚时钟和ADC时钟 		//第1步:开启DMA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);  //开启ADC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //开启GPIOA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);  //DMA是AHB总线上的外设

	
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  //配置ADCCLK,对APB2时钟进行6分频,所以是12MHz
	
	
	//第2步：配置GPIO引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  //选择模拟输入模式
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;   //引脚A0A1A2A3
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	
	//第3步：选择规则组的输入通道，填充菜单
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);
	
	
	//第4步：初始化ADC结构体
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE ;   //ENABLE为连续模式，DISABLE为单次模式
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right ; //右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //软件触发
	ADC_InitStructure.ADC_Mode =  ADC_Mode_Independent;  //独立模式
	ADC_InitStructure.ADC_NbrOfChannel = 3;   //非扫描模式下默认为1
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ;  //扫描模式 
	ADC_Init(ADC1,&ADC_InitStructure); 
	
	

	
	//第5步:配置DMA参数
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_PeripheralDataSize =  DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //不自增
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;
	DMA_InitStructure.DMA_MemoryDataSize =DMA_MemoryDataSize_HalfWord ;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable  ;
	DMA_InitStructure.DMA_BufferSize = 3;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC ;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable ;    //选择硬件触发

	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;   //DMA的循环模式

	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium ;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	
	
	//第6步:DMA使能
//	DMA_Cmd(DMA1_Channel1,DISABLE);  //DMA失能
	DMA_Cmd(DMA1_Channel1,ENABLE);   //DMA使能	
	
	
	//第7步：打开DMA输出
	ADC_DMACmd(ADC1,ENABLE);
	//第8步：开启ADC的电源
	ADC_Cmd(ADC1,ENABLE);	
	
	//第9步：对ADC进行校准
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1)==SET);
	ADC_StartCalibration(ADC1); //启动校准
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);  //软件触发ADC1一次后进入连续扫描模式

	
//	ADC_SoftwareStartConvCmd(ADC1,ENABLE);  //软件触发ADC1，连续传换时只需在初始化触发一次即可
}

/** 
   * @brief   获取ADC数据寄存器内的值
* @param   无
   * @retval  无
   */
//void AD_GetValue(void)
//{	
//	DMA_Cmd(DMA1_Channel1,DISABLE);   //给DMA失能,然后才能给转移计数器赋值
//	DMA_SetCurrDataCounter(DMA1_Channel1,3);
//	DMA_Cmd(DMA1_Channel1,ENABLE);   //DMA使能
//	
////	ADC_SoftwareStartConvCmd(ADC1,ENABLE);  //软件触发ADC1
//	
//	while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);  //转移标志位是否置1
//	DMA_ClearFlag(DMA1_FLAG_TC1);  //清除标志位
//}


