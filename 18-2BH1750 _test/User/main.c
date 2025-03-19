//	#include "sys.h"	
	#include "delay.h"	
	#include "led.h" 
	#include "key.h"
	#include "OLED.h"
//	#include "bmp.h"
//	#include "dht11.h"
	#include "BH1750.h"
	
	u8 temperature =0;  	    
	u8 humidity = 0; 
	float Light = 0; //���ն�
	
	 int main(void)
	 {
		u8 t =0;
//		delay_init();	    	 //��ʱ������ʼ��	  
//		LED_Init();		  	 	//��ʼ����LED���ӵ�Ӳ���ӿ�
//		KEY_Init();            //��ʼ���밴�����ӵ�Ӳ���ӿ�
		OLED_Init();           //��ʼ����OLED��ʾ��
		OLED_Clear();           //�����Ļ
		 
//		DHT11_Init();          //��ʼ��DHT11
		BH1750_Init();          //��ʼ��BH1750
		  
		while(1)
		{
		
		if(t%10==0)			//ÿ100ms��ȡһ��
			{									  
//				DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ	
				if (!i2c_CheckDevice(BH1750_Addr))
				{
					Light = LIght_Intensity();              //��ȡ����ǿ��
				}		
	 	   
			}	
			Delay_ms(10);
			t++;
			//OLED��ʾ���� "�¶ȣ�"
//			OLED_ShowCHinese(0,3,7);//��
//			OLED_ShowCHinese(18,3,8);//��
//			OLED_ShowString(40,4,":",26);//:
//			OLED_ShowNum(50,3,temperature,2,16);//��ʾASCII�ַ�����ֵ 	
			
//			//OLED��ʾ���� "ʪ�ȣ�"
//			OLED_ShowCHinese(0,6,9);//ʪ
//			OLED_ShowCHinese(18,6,8);//��
//			OLED_ShowString(40,7,":",26);//:
//			OLED_ShowNum(50,6,humidity,2,16);//��ʾASCII�ַ�����ֵ
			 
			//OLED��ʾ���� "����ǿ��"
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
			OLED_ShowFNum(3,10,Light);
			OLED_ShowCN(4,1,6);//��
			OLED_ShowCN(4,2,7);//��
			OLED_ShowCN(4,3,8);//��
			OLED_ShowCN(4,4,9);//��
			OLED_ShowChar(4,9,':');
//			if(Light<50)//����ǿ��С��50��LED1����
//			{
//				LED1 = 0;
//			
//			}
//			else
//			{
//				LED1=1;
//			
//			}
			
		}
		
	}


