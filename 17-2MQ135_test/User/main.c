#include "stm32f10x.h"
#include "led.h"
#include "Serial.h"
#include "delay.h"
#include "OLED.h"
#include "mq135.h"
#include "AD.h"
 

 
u16 value;
u8 buff[30];//������ʾ��������
float ppm;
 
int main(void)
{ 
	OLED_Init();
	SystemInit();//����ϵͳʱ��Ϊ72M	
//	delay_init(72);
//	LED_Init();
//	LED_On();
	MQ135_Init();
//	Serial_Init();//���ڳ�ʼ��
	
//	OLED_Init();
//	printf("Start \n");
//	Delay_ms(1000);
	
//	OLED_Clear();
	//��ʾ����������:��
			OLED_ShowCN(1,1,0);//��
			OLED_ShowCN(1,2,5);//��
			OLED_ShowChar(1,5,':');
			OLED_ShowCN(2,1,1);//ʪ
			OLED_ShowCN(2,2,5);//��
			OLED_ShowChar(2,5,':');
			OLED_ShowCN(3,1,2);//��
			OLED_ShowCN(3,2,3);//��
			OLED_ShowCN(3,3,4);//ǿ
			OLED_ShowCN(3,4,5);//��
			OLED_ShowChar(3,9,':');
			OLED_ShowCN(4,1,6);//��
			OLED_ShowCN(4,2,7);//��
			OLED_ShowCN(4,3,8);//��
			OLED_ShowCN(4,4,9);//��
			OLED_ShowChar(4,9,':');
	
	
 
  while (1)
  {
//		LED_Toggle();
		value = MQ135_GetData();  
		
//		printf("��������: %d\r\n",value);  //���ڷ���
		OLED_ShowNum(4,10,value,4);
		
//		ppm = MQ135_GetData_PPM();
//		sprintf((char*)buff, "%.2fppm    ",ppm);
//		OLED_ShowString(4,10,(char*)buff);
		
//		if(value)
//		{
//			OLED_ShowChinese(48,32,4,16,1);	//��
//			OLED_ShowChinese(64,32,6,16,1);	//��
//		}
//		else
//		{
//			OLED_ShowChinese(48,32,5,16,1);	//��
//			OLED_ShowChinese(64,32,6,16,1);	//��
//		}
 
		Delay_ms(200);
 
  }
	
}

