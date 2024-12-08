#include "stm32f10x.h"                  // Device header
#include "MySPI.h"


/**
   * @brief   对W25Q64进行初始化
   * @param   无
   * @retval  无
   */
void W25Q64_Init(void)
{
	MySPI_Init();
}

/**
   * @brief  实现W25Q64的读设备ID时序
   * @param  MID:指向MID变量的指针
             DID:指向DID变量的指针
   * @retval 无
   */
void W25Q64_ReadID(uint8_t *MID,uint16_t*  DID)
{
	MySPI_Start();
	MySPI_SwapByte(0x9F);  //读取ID指令
	*MID = MySPI_SwapByte(0xFF);    //读厂商ID
	*DID = MySPI_SwapByte(0xFF);    //读设备ID高8位
	*DID <<=8;
	*DID |= MySPI_SwapByte(0xFF);    //读厂商ID低8位
	MySPI_Stop();		
}


