#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Motor.h"
#include "Servo.h"
#include "Key.h"
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "onenet.h"
#include "esp8266.h"
#include "dht11.h"
#include "BH1750.h"
#include "mq135.h"


extern uint8_t Virtual_Key;
extern uint8_t Virtual_Key2;
extern unsigned int rec_data[4];
float Light = 0;   //照度
u16 value ; //空气质量

uint8_t KeyNum;   //接收键值
//int8_t Speed=0;     //速度
extern uint8_t Speed2;     //速度
float Angle;   //舵机角度
extern uint8_t Angle2;
int8_t CounterWise = 0;  //正反转
unsigned short timeCount = 0;




int main(void)
{
	u8 t =0;   //用来控制光照 、 温湿度和mq135
	u8 l = 0;  //用来控制温湿度
	u8 k = 0;  //用来控制mq135
	unsigned char *dataPtr;
	
	//硬件初始化
	LED_Init();   //LED初始化
	Motor_Init();  //初始化电机
	KEY_Init();    //初始化按键
	OLED_Init();  //OLED初始化
	Servo_Init();//初始化舵机
	
	
	
	Serial_Init();
	Usart2_Init(115200);  //初始化esp8266串口
	ESP8266_Init();       //初始化esp8266
	BH1750_Init();          //初始化BH1750
	MQ135_Init();         //初始化MQ135
	
//	LED1_On();
	
	
	while(OneNet_DevLink())			//接入OneNET
	Delay_ms(500);	
	
	LED2_On();
	
	OneNET_Subscribe();  //ONeNET订阅
	
	OLED_ShowCN(1,1,0);//温
	OLED_ShowCN(1,2,5);//度
	OLED_ShowChar(1,5,':');
	OLED_ShowChar(1,8,'.');//小数点
	OLED_ShowCN(1,6,10);//℃
	OLED_ShowCN(2,1,1);//湿
	OLED_ShowCN(2,2,5);//度
	OLED_ShowChar(2,5,':');
	OLED_ShowChar(2,8,'.');//小数点
	OLED_ShowString(2,11,"%RH");//%RH
	OLED_ShowCN(3,1,2);//光
	OLED_ShowCN(3,2,3);//照
	OLED_ShowCN(3,3,4);//强
	OLED_ShowCN(3,4,5);//度
	OLED_ShowChar(3,9,':');
	OLED_ShowCN(4,1,6);//空
	OLED_ShowCN(4,2,7);//气
	OLED_ShowCN(4,3,8);//质
	OLED_ShowCN(4,4,9);//量
	OLED_ShowChar(4,9,':');
	

	while(1)
	{
		if(t%10==0)
		{
			l++;
			k++;
			if(l%10==0)
			{
				DHT11_REC_Data(); //接收温度和湿度的数据
			}
			if(k%2==0)
			{
				value = MQ135_GetData();
			}
			if (!i2c_CheckDevice(BH1750_Addr))
			{
				Light = LIght_Intensity();//获取光照强度
			}
		}
		Delay_ms(10);
		t++;
		OLED_ShowNum(1,6,rec_data[2],2);
		OLED_ShowNum(1,9,rec_data[3],1);
		OLED_ShowNum(2,6,rec_data[0],2);
		OLED_ShowNum(2,9,rec_data[1],2);
		OLED_ShowFNum(3,10,Light);
		OLED_ShowNum(4,10,value,4);
		
		if(++timeCount >= 50)									//发送间隔5s
		{
			OneNet_SendData();									//发送数据
			timeCount = 0;
			ESP8266_Clear();
		}
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)
		{
			OneNet_RevPro(dataPtr);
		}
		


		Motor_SetSpeed(CounterWise,Speed2);

		Angle = (float) Angle2;
		Servo_SetAngle(Angle);

	}
}



