#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

uint8_t KeyNum;



uint16_t ArrayWrite[]={0x1234,0x5678};
uint16_t ArrayRead[2];


int main(void)
{
   
	OLED_Init();  //��ʼ��OLED

	
	KEY_Init();
	OLED_ShowString(1,1,"W:");
	OLED_ShowString(2,1,"R:");
	
	
	//��1������ʼ��PWR��BKP��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
	
	//��2����PWR����DBPλ�������BKP��RTC�ķ���
	PWR_BackupAccessCmd(ENABLE);
	
	
//	
//	//��3����д�����ݵ�BKP
//	BKP_WriteBackupRegister(BKP_DR1,0x1234);
//	
//	
//	//��4������ȡBKP_DR1������
//	OLED_ShowHexNum(1,1,BKP_ReadBackupRegister(BKP_DR1),4);
	while(1)  
	{
		
		KeyNum = Key_GetNum();
		
		if(KeyNum==1)
		{
			ArrayWrite[0]++;
			ArrayWrite[1]++;
			
			BKP_WriteBackupRegister(BKP_DR1,ArrayWrite[0]);
			BKP_WriteBackupRegister(BKP_DR2,ArrayWrite[1]);
			
			
			OLED_ShowHexNum(1,3,ArrayWrite[0],4);
			OLED_ShowHexNum(1,8,ArrayWrite[1],4);

		}
		
		ArrayRead[0] = BKP_ReadBackupRegister(BKP_DR1);
		ArrayRead[1] = BKP_ReadBackupRegister(BKP_DR2);
		
		
		OLED_ShowHexNum(2,3,ArrayRead[0],4);
		OLED_ShowHexNum(2,8,ArrayRead[1],4);
	}
	
}

