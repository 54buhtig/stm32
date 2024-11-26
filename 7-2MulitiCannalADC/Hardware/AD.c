#include "stm32f10x.h"                  // Device header


/**
   * @brief   对ADC进行初始化
   * @param   无
   * @retval  无
   */
void AD_Init(void)
{
	//第1步：开启RCC时钟，引脚时钟和ADC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);  //开启ADC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //开启GPIOA时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  //配置ADCCLK,对APB2时钟进行6分频,所以是12MHz
	
	
	//第2步：配置GPIO引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  //选择模拟输入模式
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;   //引脚A1A2A3
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	
	//第3步：选择规则组的输入通道，填充菜单
	
	
	//第4步：初始化ADC结构体
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE ;   //ENABLE为连续模式，DISABLE为单次模式
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right ; //右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //软件触发
	ADC_InitStructure.ADC_Mode =  ADC_Mode_Independent;  //独立模式
	ADC_InitStructure.ADC_NbrOfChannel = 1;   //非扫描模式下默认为1
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ;
	ADC_Init(ADC1,&ADC_InitStructure); 
	
	//第5步：开启ADC的电源
	ADC_Cmd(ADC1,ENABLE);	
	
	//第6步：对ADC进行校准
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1)==SET);
	ADC_StartCalibration(ADC1); //启动校准
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	
	
//	ADC_SoftwareStartConvCmd(ADC1,ENABLE);  //软件触发ADC1，连续传换时只需在初始化触发一次即可
}

/** 
   * @brief   获取ADC数据寄存器内的值
* @param   ADC_Channel:是ADC在非扫描模式下指定的通道
   * @retval  返回1个16位的数字量
   */
uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	//第3步：选择规则组的输入通道，填充菜单
	ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);  //软件触发ADC1
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)== RESET);  //转化时间大概为5.6us，连续转换就无需判断EOC信号是否置位
	return ADC_GetConversionValue(ADC1);  //读取转换数据
}


