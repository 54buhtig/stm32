#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "W25Q64_Ins.h"

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
	MySPI_SwapByte(W25Q64_JEDEC_ID);  //��ȡIDָ��
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);    //������ID
	*DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);    //���豸ID��8λ
	*DID <<=8;
	*DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);    //������ID��8λ
	MySPI_Stop();		
}


/**
   * @brief  ʵ��W25Q64��дʹ��ʱ��
   * @param  ��
   * @retval ��
   */
void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);  //дʹ��ָ��
	MySPI_Stop();			
}



/**
   * @brief   �ȴ�æ״̬����
   * @param   ��
   * @retval  ��
   */
void W25Q64_WaitBusy(void)
{
	uint32_t Timeout;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);  //��״̬�Ĵ���1
	Timeout = 100000;
	while((MySPI_SwapByte(W25Q64_DUMMY_BYTE)& 0x01) == 0x01)//����ȡ��Busyλ�ж��Ƿ�Ϊ1��1Ϊæ״̬
	{
			Timeout--;
		if(Timeout==0)
		{
			break; //�˳�ѭ��
		}
	}  
	MySPI_Stop();			
}

/**
   * @brief   W25Q64��ҳ���
   * @param   Address:�洢�ĵ�ַ
              DataArray:�洢���ݵ������׵�ַ
              Count:��ʾһ��д��ĸ���
   * @retval  ��
   */
void W25Q64_PageProgram(uint32_t Address,uint8_t* DataArray,uint16_t Count)
{
	uint16_t i;
//	W25Q64_WaitBusy(); //��ǰ�ȴ�Ч�ʸ�
	W25Q64_WriteEnable();   //дʹ��
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);  //ҳ���
	MySPI_SwapByte(Address>>16);  
	MySPI_SwapByte(Address>>8);  
	MySPI_SwapByte(Address);  
	
	for(i=0;i<Count;i++)
	{
		MySPI_SwapByte(DataArray[i]);  		
	}
	MySPI_Stop();	
	W25Q64_WaitBusy();   //�º�ȴ����	
}


/**
   * @brief  ��ѡ�����������в���
   * @param  Address:ָ����������ַ
   * @retval ��
   */
void W25Q64_SectorErase(uint32_t Address)
{
	W25Q64_WriteEnable();  //дʹ��
	MySPI_Start();
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);  //������������ָ��
	MySPI_SwapByte(Address>>16);  
	MySPI_SwapByte(Address>>8);  
	MySPI_SwapByte(Address); 	
	MySPI_Stop();
	W25Q64_WaitBusy();   //�º�ȴ����	
	
}


/**
   * @brief  W25Q64���ж�����ʱ��
   * @param  Address:ָ����ȡ���ݵĵ�ַ
             DataArray:������ݵ������׵�ַ
             Count:��ȡ���ݵĸ���
   * @retval ��
   */
void W25Q64_ReadData(uint32_t Address,uint8_t* DataArray,uint32_t Count)
{
	uint32_t i;
//	W25Q64_WaitBusy(); //��ǰ�ȴ�Ч�ʸ�	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);  //������
	MySPI_SwapByte(Address>>16);  
	MySPI_SwapByte(Address>>8);  
	MySPI_SwapByte(Address);	
	
	for(i=0;i<Count;i++)
	{
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	MySPI_Stop();			 				
}





