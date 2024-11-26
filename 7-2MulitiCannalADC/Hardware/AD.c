#include "stm32f10x.h"                  // Device header


/**
   * @brief   ��ADC���г�ʼ��
   * @param   ��
   * @retval  ��
   */
void AD_Init(void)
{
	//��1��������RCCʱ�ӣ�����ʱ�Ӻ�ADCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);  //����ADCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //����GPIOAʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  //����ADCCLK,��APB2ʱ�ӽ���6��Ƶ,������12MHz
	
	
	//��2��������GPIO����
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  //ѡ��ģ������ģʽ
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;   //����A1A2A3
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	
	//��3����ѡ������������ͨ�������˵�
	
	
	//��4������ʼ��ADC�ṹ��
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE ;   //ENABLEΪ����ģʽ��DISABLEΪ����ģʽ
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right ; //�Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //�������
	ADC_InitStructure.ADC_Mode =  ADC_Mode_Independent;  //����ģʽ
	ADC_InitStructure.ADC_NbrOfChannel = 1;   //��ɨ��ģʽ��Ĭ��Ϊ1
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ;
	ADC_Init(ADC1,&ADC_InitStructure); 
	
	//��5��������ADC�ĵ�Դ
	ADC_Cmd(ADC1,ENABLE);	
	
	//��6������ADC����У׼
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1)==SET);
	ADC_StartCalibration(ADC1); //����У׼
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	
	
//	ADC_SoftwareStartConvCmd(ADC1,ENABLE);  //�������ADC1����������ʱֻ���ڳ�ʼ������һ�μ���
}

/** 
   * @brief   ��ȡADC���ݼĴ����ڵ�ֵ
* @param   ADC_Channel:��ADC�ڷ�ɨ��ģʽ��ָ����ͨ��
   * @retval  ����1��16λ��������
   */
uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	//��3����ѡ������������ͨ�������˵�
	ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);  //�������ADC1
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)== RESET);  //ת��ʱ����Ϊ5.6us������ת���������ж�EOC�ź��Ƿ���λ
	return ADC_GetConversionValue(ADC1);  //��ȡת������
}


