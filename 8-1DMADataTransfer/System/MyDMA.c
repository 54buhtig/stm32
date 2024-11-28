#include "stm32f10x.h"                  // Device header

uint16_t MyDMA_Size;

/**
   * @brief  对DMA进行初始化
   * @param  AddrA:外设的地址 
   * 		 AddrB:存储器的地址 
   * 		 Size:转移次数    
   * @retval 无
   */
void  MyDMA_Init(uint32_t AddrA,uint32_t AddrB,uint16_t Size)	
{
	MyDMA_Size = Size;
	
	//第1步:开启DMA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);  //DMA是AHB总线上的外设
	
	//第2步:配置DMA参数
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_BufferSize = Size;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC ;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable ;  //选择软件触发
	DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;
	DMA_InitStructure.DMA_MemoryDataSize =DMA_MemoryDataSize_Byte ;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable  ;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;
	DMA_InitStructure.DMA_PeripheralDataSize =  DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium ;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	
	
	//第3步:DMA使能
	DMA_Cmd(DMA1_Channel1,DISABLE);  //DMA失能
//	DMA_Cmd(DMA1_Channel1,ENABLE);   //DMA使能	
	
}

/**
   * @brief   DMA转移次数
   * @param   无
   * @retval 无
   */
void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1,DISABLE);   //给DMA失能,然后才能给转移计数器赋值
	DMA_SetCurrDataCounter(DMA1_Channel1,MyDMA_Size);
	DMA_Cmd(DMA1_Channel1,ENABLE);   //DMA使能	
	
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);  //转移标志位是否置1
	DMA_ClearFlag(DMA1_FLAG_TC1);  //清除标志位
}






