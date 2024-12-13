#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;

int main(void)
{
   
	OLED_Init();  //��ʼ��OLED

	OLED_ShowString(1,1,"RxData:");
	Serial_Init(); //��ʼ������
	
	


	while(1)  
	{
		//���ò�ѯ�ķ�����������
//		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
//		{
//			RxData = USART_ReceiveData(USART1);
//			OLED_ShowChar(1,1,RxData);
//		}
		
		//�����жϵķ�����������
		if(Serial_GetRxFlag()==1)
		{
			RxData  =  Serial_GetRxData();
			Serial_SendByte(RxData);
			OLED_ShowHexNum(1,8,RxData,2);
		}
	
		OLED_ShowString(2,1,"Running");
		Delay_ms(100);
		OLED_ShowString(2,1,"       ");
		Delay_ms(100);	


		__WFI();  //WFIָ���˯��ģʽ���жϻ��ѣ�
//        __WFE();  //WFEָ��¼�����
	}
}
