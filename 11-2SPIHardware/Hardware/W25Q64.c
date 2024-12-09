#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "W25Q64_Ins.h"

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
	MySPI_SwapByte(W25Q64_JEDEC_ID);  //读取ID指令
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);    //读厂商ID
	*DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);    //读设备ID高8位
	*DID <<=8;
	*DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);    //读厂商ID低8位
	MySPI_Stop();		
}


/**
   * @brief  实现W25Q64的写使能时序
   * @param  无
   * @retval 无
   */
void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);  //写使能指令
	MySPI_Stop();			
}



/**
   * @brief   等待忙状态结束
   * @param   无
   * @retval  无
   */
void W25Q64_WaitBusy(void)
{
	uint32_t Timeout;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);  //读状态寄存器1
	Timeout = 100000;
	while((MySPI_SwapByte(W25Q64_DUMMY_BYTE)& 0x01) == 0x01)//掩码取出Busy位判断是否为1，1为忙状态
	{
			Timeout--;
		if(Timeout==0)
		{
			break; //退出循环
		}
	}  
	MySPI_Stop();			
}

/**
   * @brief   W25Q64的页编程
   * @param   Address:存储的地址
              DataArray:存储数据的数据首地址
              Count:表示一次写入的个数
   * @retval  无
   */
void W25Q64_PageProgram(uint32_t Address,uint8_t* DataArray,uint16_t Count)
{
	uint16_t i;
//	W25Q64_WaitBusy(); //事前等待效率高
	W25Q64_WriteEnable();   //写使能
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);  //页编程
	MySPI_SwapByte(Address>>16);  
	MySPI_SwapByte(Address>>8);  
	MySPI_SwapByte(Address);  
	
	for(i=0;i<Count;i++)
	{
		MySPI_SwapByte(DataArray[i]);  		
	}
	MySPI_Stop();	
	W25Q64_WaitBusy();   //事后等待最保险	
}


/**
   * @brief  对选定的扇区进行擦除
   * @param  Address:指定的扇区地址
   * @retval 无
   */
void W25Q64_SectorErase(uint32_t Address)
{
	W25Q64_WriteEnable();  //写使能
	MySPI_Start();
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);  //发送扇区擦除指令
	MySPI_SwapByte(Address>>16);  
	MySPI_SwapByte(Address>>8);  
	MySPI_SwapByte(Address); 	
	MySPI_Stop();
	W25Q64_WaitBusy();   //事后等待最保险	
	
}


/**
   * @brief  W25Q64进行读数据时序
   * @param  Address:指定读取数据的地址
             DataArray:存放数据的数组首地址
             Count:读取数据的个数
   * @retval 无
   */
void W25Q64_ReadData(uint32_t Address,uint8_t* DataArray,uint32_t Count)
{
	uint32_t i;
//	W25Q64_WaitBusy(); //事前等待效率高	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);  //读数据
	MySPI_SwapByte(Address>>16);  
	MySPI_SwapByte(Address>>8);  
	MySPI_SwapByte(Address);	
	
	for(i=0;i<Count;i++)
	{
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	MySPI_Stop();			 				
}





