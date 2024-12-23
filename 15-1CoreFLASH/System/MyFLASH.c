#include "stm32f10x.h"                  // Device header

/**
   * @brief   将数据以字形式从内部FLASH的指定地址读出
   * @param   Address:写入32位的指定地址  地址从0x0800 0000到0x0800 FC00
   * @retval  返回32位的数据
   */
uint32_t MyFLASH_ReadWord(uint32_t Address)
{
		return *((__IO uint32_t*)(Address)) ;
}

/**
   * @brief   将数据以半字形式从内部FLASH的指定地址读出
   * @param   Address:写入32位的指定地址  地址从0x0800 0000到0x0800 FC00
   * @retval  返回16位的数据
   */
uint16_t MyFLASH_ReadHalfWord(uint32_t Address)
{
		return *((__IO uint16_t*)(Address)) ;
}



/**
   * @brief   将数据以字节形式从内部FLASH的指定地址读出
   * @param   Address:写入32位的指定地址  地址从0x0800 0000到0x0800 FC00
   * @retval  返回8位的数据
   */
uint8_t MyFLASH_ReadByte(uint32_t Address)
{
		return *((__IO uint8_t*)(Address)) ;
}

/**
   * @brief   擦除FLASH全部页
   * @param   无
   * @retval  无
   */
void MyFLASH_EraseAllPages(void)
{
	FLASH_Unlock();
	FLASH_EraseAllPages();
	FLASH_Lock();
}

/**
   * @brief  擦除FLASH指定页
   * @param  PageAddress:指定页的地址,32位,范围从0x0800 0000到0x0800 FC00
   * @retval 无
   */
void MyFLASH_ErasePage(uint32_t PageAddress)
{
	FLASH_Unlock();
	FLASH_ErasePage(PageAddress);
	FLASH_Lock();
}

/**
   * @brief  在内部FLASH的指定地址进行一个字的编程(写入一个字)
   * @param  Address:指定写入的地址,32位,范围从0x0800 0000到0x0800 FC00
             Data:写入的字数据
   * @retval 无
   */
void MyFLASH_ProgramWord(uint32_t Address,uint32_t Data)
{
	FLASH_Unlock();
	FLASH_ProgramWord(Address,Data);	
	FLASH_Lock();
}

/**
   * @brief  在内部FLASH的指定地址进行半字的编程(写入半字)
   * @param  Address:指定写入的地址,32位,范围从0x0800 0000到0x0800 FC00
             Data:写入的半字数据
   * @retval 无
   */
void MyFLASH_ProgramHalfWord(uint32_t Address,uint16_t Data)
{
	FLASH_Unlock();
	FLASH_ProgramHalfWord(Address,Data);	
	FLASH_Lock();
}













