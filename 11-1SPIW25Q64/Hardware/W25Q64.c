#include "stm32f10x.h"                  // Device header
#include "MySPI.h"


/**
   * @brief   ��W25Q64���г�ʼ��
   * @param   ��
   * @retval  ��
   */
void W25Q64_Init(void)
{
	MySPI_Init();
}

/**
   * @brief  ʵ��W25Q64�Ķ��豸IDʱ��
   * @param  MID:ָ��MID������ָ��
             DID:ָ��DID������ָ��
   * @retval ��
   */
void W25Q64_ReadID(uint8_t *MID,uint16_t*  DID)
{
	MySPI_Start();
	MySPI_SwapByte(0x9F);  //��ȡIDָ��
	*MID = MySPI_SwapByte(0xFF);    //������ID
	*DID = MySPI_SwapByte(0xFF);    //���豸ID��8λ
	*DID <<=8;
	*DID |= MySPI_SwapByte(0xFF);    //������ID��8λ
	MySPI_Stop();		
}


