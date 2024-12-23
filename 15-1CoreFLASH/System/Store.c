#include "stm32f10x.h"                  // Device header
#include "MyFLASH.h"

#define STORE_START_ADDRESS  0x0800FC00

#define STORE_SIZE  512

uint16_t Store_Data[STORE_SIZE];

/**
   * @brief    ��FLASH���Զ�����粻��ʧ�洢��ַ���г�ʼ��,
               ��־λ��0x0800FC00��ַ�µ�����,��������Ϊ0xA4A4
   * @param    ��
   * @retval   ��
   */
void Store_Init(void)
{
	//��1��ʹ��ʱ��������г�ʼ��
	if(MyFLASH_ReadHalfWord(STORE_START_ADDRESS)!=0xA4A4)
	{
		MyFLASH_ErasePage(STORE_START_ADDRESS);
		MyFLASH_ProgramHalfWord(STORE_START_ADDRESS,0xA4A4);
		for(uint16_t i=1;i<STORE_SIZE;i++)
		{
			MyFLASH_ProgramHalfWord(STORE_START_ADDRESS+i*2,0x0000);
		}
	}
	 
	for(uint16_t i=0;i<STORE_SIZE;i++)
	{
		Store_Data[i] = MyFLASH_ReadHalfWord(STORE_START_ADDRESS+i*2);
	}
}

/**
   * @brief   ��SRAM������������д��FLASH��
              ע��!!!SRAM�������ĵ�һ������Ϊ��־λ,�̶�ΪA4A4,����д����������
   * @param   ��
   * @retval  ��
   */
void Store_Save(void)
{
	MyFLASH_ErasePage(STORE_START_ADDRESS);
	for(uint16_t i=0;i<STORE_SIZE;i++)
	{
		MyFLASH_ProgramHalfWord(STORE_START_ADDRESS+i*2,Store_Data[i]); 
	}
}

/**
   * @brief    ��SRAM��������FLASG�Զ���洢��ַ�������
               ע��!!!SRAM�������ĵ�һ�������Ǳ�־λ,�������
   * @param    ��
   * @retval   ��
   */
void Store_Clear(void)
{
	for(uint16_t i=1;i<STORE_SIZE;i++)
	{
		Store_Data[i] = 0x0000;
	}
	Store_Save();
}





