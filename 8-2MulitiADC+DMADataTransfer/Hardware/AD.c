#include "stm32f10x.h"                  // Device header


uint16_t AD_Value[3];

/**
   * @brief   ��ADC���г�ʼ��
   * @param   ��
   * @retval  ��
   */
void AD_Init(void)
{
	//��1��������RCCʱ�ӣ�����ʱ�Ӻ�ADCʱ�� 		//��1��:����DMAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);  //����ADCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //����GPIOAʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);  //DMA��AHB�����ϵ�����

	
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  //����ADCCLK,��APB2ʱ�ӽ���6��Ƶ,������12MHz
	
	
	//��2��������GPIO����
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  //ѡ��ģ������ģʽ
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;   //����A0A1A2A3
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	
	//��3����ѡ������������ͨ�������˵�
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);
	
	
	//��4������ʼ��ADC�ṹ��
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE ;   //ENABLEΪ����ģʽ��DISABLEΪ����ģʽ
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right ; //�Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //�������
	ADC_InitStructure.ADC_Mode =  ADC_Mode_Independent;  //����ģʽ
	ADC_InitStructure.ADC_NbrOfChannel = 3;   //��ɨ��ģʽ��Ĭ��Ϊ1
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ;  //ɨ��ģʽ 
	ADC_Init(ADC1,&ADC_InitStructure); 
	
	

	
	//��5��:����DMA����
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_PeripheralDataSize =  DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //������
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;
	DMA_InitStructure.DMA_MemoryDataSize =DMA_MemoryDataSize_HalfWord ;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable  ;
	DMA_InitStructure.DMA_BufferSize = 3;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC ;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable ;    //ѡ��Ӳ������

	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;   //DMA��ѭ��ģʽ

	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium ;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	
	
	//��6��:DMAʹ��
//	DMA_Cmd(DMA1_Channel1,DISABLE);  //DMAʧ��
	DMA_Cmd(DMA1_Channel1,ENABLE);   //DMAʹ��	
	
	
	//��7������DMA���
	ADC_DMACmd(ADC1,ENABLE);
	//��8��������ADC�ĵ�Դ
	ADC_Cmd(ADC1,ENABLE);	
	
	//��9������ADC����У׼
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1)==SET);
	ADC_StartCalibration(ADC1); //����У׼
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);  //�������ADC1һ�κ��������ɨ��ģʽ

	
//	ADC_SoftwareStartConvCmd(ADC1,ENABLE);  //�������ADC1����������ʱֻ���ڳ�ʼ������һ�μ���
}

/** 
   * @brief   ��ȡADC���ݼĴ����ڵ�ֵ
* @param   ��
   * @retval  ��
   */
//void AD_GetValue(void)
//{	
//	DMA_Cmd(DMA1_Channel1,DISABLE);   //��DMAʧ��,Ȼ����ܸ�ת�Ƽ�������ֵ
//	DMA_SetCurrDataCounter(DMA1_Channel1,3);
//	DMA_Cmd(DMA1_Channel1,ENABLE);   //DMAʹ��
//	
////	ADC_SoftwareStartConvCmd(ADC1,ENABLE);  //�������ADC1
//	
//	while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);  //ת�Ʊ�־λ�Ƿ���1
//	DMA_ClearFlag(DMA1_FLAG_TC1);  //�����־λ
//}


