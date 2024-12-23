#include "stm32f10x.h"                  // Device header

/**
   * @brief   ������������ʽ���ڲ�FLASH��ָ����ַ����
   * @param   Address:д��32λ��ָ����ַ  ��ַ��0x0800 0000��0x0800 FC00
   * @retval  ����32λ������
   */
uint32_t MyFLASH_ReadWord(uint32_t Address)
{
		return *((__IO uint32_t*)(Address)) ;
}

/**
   * @brief   �������԰�����ʽ���ڲ�FLASH��ָ����ַ����
   * @param   Address:д��32λ��ָ����ַ  ��ַ��0x0800 0000��0x0800 FC00
   * @retval  ����16λ������
   */
uint16_t MyFLASH_ReadHalfWord(uint32_t Address)
{
		return *((__IO uint16_t*)(Address)) ;
}



/**
   * @brief   ���������ֽ���ʽ���ڲ�FLASH��ָ����ַ����
   * @param   Address:д��32λ��ָ����ַ  ��ַ��0x0800 0000��0x0800 FC00
   * @retval  ����8λ������
   */
uint8_t MyFLASH_ReadByte(uint32_t Address)
{
		return *((__IO uint8_t*)(Address)) ;
}

/**
   * @brief   ����FLASHȫ��ҳ
   * @param   ��
   * @retval  ��
   */
void MyFLASH_EraseAllPages(void)
{
	FLASH_Unlock();
	FLASH_EraseAllPages();
	FLASH_Lock();
}

/**
   * @brief  ����FLASHָ��ҳ
   * @param  PageAddress:ָ��ҳ�ĵ�ַ,32λ,��Χ��0x0800 0000��0x0800 FC00
   * @retval ��
   */
void MyFLASH_ErasePage(uint32_t PageAddress)
{
	FLASH_Unlock();
	FLASH_ErasePage(PageAddress);
	FLASH_Lock();
}

/**
   * @brief  ���ڲ�FLASH��ָ����ַ����һ���ֵı��(д��һ����)
   * @param  Address:ָ��д��ĵ�ַ,32λ,��Χ��0x0800 0000��0x0800 FC00
             Data:д���������
   * @retval ��
   */
void MyFLASH_ProgramWord(uint32_t Address,uint32_t Data)
{
	FLASH_Unlock();
	FLASH_ProgramWord(Address,Data);	
	FLASH_Lock();
}

/**
   * @brief  ���ڲ�FLASH��ָ����ַ���а��ֵı��(д�����)
   * @param  Address:ָ��д��ĵ�ַ,32λ,��Χ��0x0800 0000��0x0800 FC00
             Data:д��İ�������
   * @retval ��
   */
void MyFLASH_ProgramHalfWord(uint32_t Address,uint16_t Data)
{
	FLASH_Unlock();
	FLASH_ProgramHalfWord(Address,Data);	
	FLASH_Lock();
}













