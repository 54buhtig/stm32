#include "stm32f10x.h"                  // Device header
#include "MyFLASH.h"

#define STORE_START_ADDRESS  0x0800FC00

#define STORE_SIZE  512

uint16_t Store_Data[STORE_SIZE];

/**
   * @brief    对FLASH的自定义掉电不丢失存储地址进行初始化,
               标志位是0x0800FC00地址下的数据,数据内容为0xA4A4
   * @param    无
   * @retval   无
   */
void Store_Init(void)
{
	//第1次使用时对闪存进行初始化
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
   * @brief   将SRAM缓存区的内容写入FLASH中
              注意!!!SRAM缓存区的第一个半字为标志位,固定为A4A4,不能写入其他数据
   * @param   无
   * @retval  无
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
   * @brief    对SRAM缓存区和FLASG自定义存储地址进行清除
               注意!!!SRAM缓存区的第一个半字是标志位,不会清除
   * @param    无
   * @retval   无
   */
void Store_Clear(void)
{
	for(uint16_t i=1;i<STORE_SIZE;i++)
	{
		Store_Data[i] = 0x0000;
	}
	Store_Save();
}





