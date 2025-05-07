//单片机头文件
#include "stm32f10x.h"                  // Device header


//网络设备
#include "esp8266.h"

//协议文件
#include "onenet.h"
#include "Common.h"
#include "Mqttkit.h"
#include "cJSON.h"

//硬件驱动
#include "Serial.h"
#include "LED.h"
#include "dht11.h"
#include "BH1750.h"
#include "mq135.h"
//C库
#include <string.h>
#include <stdio.h>
#define PROID		"n9aSJm39Mh" //产品ID

#define AUTH_INFO	 "version=2018-10-31&res=products%2Fn9aSJm39Mh%2Fdevices%2Fmotor&et=1784415600&method=md5&sign=ly4VkP16E0CcaxU82dRLqw%3D%3D"//鉴权信息

#define DEVID		"motor"//设备ID

extern unsigned char esp8266_buf[128];
extern uint8_t SendString[2];
float Receive[5] = {10.5,11.1,12.3};
extern  float x;
extern float NTCTemp;
extern float temperature;  //温度
extern float humidity;     //湿度
extern float lightvalue;  //照度
extern u16 Airvalue;   //空气质量



uint8_t LED_Statue = 0;
uint8_t Virtual_Key = 0;   //初始化虚拟按键为0，防止风扇打开
uint8_t Speed=100;     //速度
uint8_t Virtual_Key2 = 0;   //初始化虚拟按键为0，防止舵机抽搐
float Angle=0;   //舵机角度
//==========================================================
//	函数名称：	OneNet_DevLink
//
//	函数功能：	与onenet创建连接
//
//	入口参数：	无
//
//	返回参数：	1-成功	0-失败
//
//	说明：		与onenet平台建立连接
//==========================================================
_Bool OneNet_DevLink(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};					//协议包

	unsigned char *dataPtr;
	
	_Bool status = 1;
	
	Serial_Printf("OneNet_DevLink\r\nPROID: %s,	AUIF: %s,	DEVID:%s\r\n", PROID, AUTH_INFO, DEVID);
	
	if(MQTT_PacketConnect(PROID, AUTH_INFO, DEVID, 256, 1, MQTT_QOS_LEVEL0, NULL, NULL, 0, &mqttPacket) == 0)
	{
		ESP8266_SendData(mqttPacket._data, mqttPacket._len);			//上传平台
		dataPtr = ESP8266_GetIPD(250);									//等待平台响应
		if(dataPtr != NULL)
		{
			if(MQTT_UnPacketRecv(dataPtr) == MQTT_PKT_CONNACK)
			{
				switch(MQTT_UnPacketConnectAck(dataPtr))
				{
					case 0:Serial_Printf("Tips:	连接成功\r\n");status = 0;break;
					
					case 1:Serial_Printf("WARN:	连接失败：协议错误\r\n");break;
					case 2:Serial_Printf("WARN:	连接失败：非法的clientid\r\n");break;
					case 3:Serial_Printf("WARN:	连接失败：服务器失败\r\n");break;
					case 4:Serial_Printf("WARN:	连接失败：用户名或密码错误\r\n");break;
					case 5:Serial_Printf("WARN:	连接失败：非法链接(比如token非法)\r\n");break;
					
					default:Serial_Printf("ERR:	连接失败：未知错误\r\n");break;
				}
			}
		}
		
		MQTT_DeleteBuffer(&mqttPacket);								//删包
	}
	else
		Serial_Printf("WARN:	MQTT_PacketConnect Failed\r\n");
	
	return status;
	
}


unsigned char OneNet_FillBuf(char *buf)
{
	char text[48];
	int Angle2 = (int)Angle;
	
	Serial_Printf("%.3f\r\n",Angle);
	Serial_Printf("%d\r\n",Angle2);
	LED_Statue = GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_8);
//	Virtual_Key=0;   //!!!!对虚拟按键进行复位
//	Virtual_Key2 = 0;   //!!!!对虚拟按键进行复位
	memset(text, 0, sizeof(text));
	//数据格式：   {"id":"123","version":"1.0","params":{"humi":{"value":%d},"temp":{"value":%d}}}
	strcpy(buf, "{\"id\":\"123\",\"version\":\"1.0\",\"params\":{");   
//		MOM=MOM+1;
	memset(text, 0, sizeof(text));
	sprintf(text,"\"Temperature\":{\"value\":%.2f},", temperature);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text,"\"Humidity\":{\"value\":%.2f},", humidity);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text,"\"Light\":{\"value\":%.2f},", lightvalue);
	strcat(buf, text);
	
	
	
	
	memset(text, 0, sizeof(text));
	sprintf(text,"\"Air\":{\"value\":%d},", Airvalue);
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text,"\"FAN\":{\"value\":%d},", Speed);
	strcat(buf, text);

	memset(text, 0, sizeof(text));
	sprintf(text,"\"SERVO\":{\"value\":%d},", Angle2);
	strcat(buf, text);

	memset(text, 0, sizeof(text));
	sprintf(text,"\"LED\":{\"value\":\"%s\"}", LED_Statue?"OFF":"ON");
	strcat(buf, text);
	
	strcat(buf, "}}");
	return strlen(buf);
}


//==========================================================
//	函数名称：	OneNet_SendData
//
//	函数功能：	上传数据到平台
//
//	入口参数：	type：发送数据的格式
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_SendData(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};												//协议包
	
	char buf[512];
	
	short body_len = 0, i = 0;
	
//	Serial_Printf("Tips:	OneNet_SendData-MQTT\r\n");
	
	memset(buf, 0, sizeof(buf));
	
	body_len = OneNet_FillBuf(buf);																	//获取当前需要发送的数据流的总长度
	
	if(body_len)
	{
		if(MQTT_PacketSaveData(DEVID, body_len, NULL, 5, &mqttPacket) == 0)							//封包
		{                                                                                                         
			for(; i < body_len; i++)
				mqttPacket._data[mqttPacket._len++] = buf[i];
			
			ESP8266_SendData(mqttPacket._data, mqttPacket._len);									//上传数据到平台
			Serial_Printf("Send %d Bytes\r\n", mqttPacket._len);
			
			MQTT_DeleteBuffer(&mqttPacket);															//删包
		}
		else
			Serial_Printf("WARN:	EDP_NewBuffer Failed\r\n");
	}

}



//==========================================================
//	函数名称：	OneNET_Publish
//
//	函数功能：	发布消息
//
//	入口参数：	topic：发布的主题
//				msg：消息内容
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNET_Publish(const char *topic, const char *msg)
{

	MQTT_PACKET_STRUCTURE mqtt_packet = {NULL, 0, 0, 0};						//协议包
	
	Serial_Printf( "Publish Topic: %s, Msg: %s\r\n", topic, msg);
	
	if(MQTT_PacketPublish(MQTT_PUBLISH_ID, topic, msg, strlen(msg), MQTT_QOS_LEVEL0, 0, 1, &mqtt_packet) == 0)
	{
		ESP8266_SendData(mqtt_packet._data, mqtt_packet._len);					//向平台发送订阅请求
		
		MQTT_DeleteBuffer(&mqtt_packet);										//删包
	}

}


//==========================================================
//	函数名称：	OneNET_Subscribe
//
//	函数功能：	订阅
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNET_Subscribe(void)
{
	
	MQTT_PACKET_STRUCTURE mqtt_packet = {NULL, 0, 0, 0};						//协议包
	
	char topic_buf[56];
	const char *topic = topic_buf;
	
	snprintf(topic_buf, sizeof(topic_buf), "$sys/%s/%s/thing/property/set", PROID, DEVID);
	
	Serial_Printf( "Subscribe Topic: %s\r\n", topic_buf);
	
	if(MQTT_PacketSubscribe(MQTT_SUBSCRIBE_ID, MQTT_QOS_LEVEL0, &topic, 1, &mqtt_packet) == 0)
	{
		ESP8266_SendData(mqtt_packet._data, mqtt_packet._len);					//向平台发送订阅请求
		
		MQTT_DeleteBuffer(&mqtt_packet);										//删包
	}

}



//==========================================================
//	函数名称：	OneNet_RevPro
//
//	函数功能：	平台返回数据检测
//
//	入口参数：	dataPtr：平台返回的数据
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_RevPro(unsigned char *cmd)
{
	
	char *req_payload = NULL;
	char *cmdid_topic = NULL;
	
	unsigned short topic_len = 0;
	unsigned short req_len = 0;
	unsigned char qos = 0;
	static unsigned short pkt_id = 0;
	
	unsigned char type = 0;
	
	short result = 0;
	cJSON *raw_json,*params_json,*LED_json,*Fan_json,*Servo_json; //定义4个指针变量
	type = MQTT_UnPacketRecv(cmd);
	switch(type)
	{
		case MQTT_PKT_PUBLISH:								//接收的Publish消息
		
			result = MQTT_UnPacketPublish(cmd, &cmdid_topic, &topic_len, &req_payload, &req_len, &qos, &pkt_id);
			if(result == 0)
			{	
				Serial_Printf( "topic: %s, topic_len: %d, payload: %s, payload_len: %d\r\n",
																	cmdid_topic, topic_len, req_payload, req_len);
				
				raw_json = cJSON_Parse(req_payload);
				Serial_Printf("req_payload success!\r\n");
				
				Serial_Printf("%d\r\n",raw_json->type);
				params_json = cJSON_GetObjectItem(raw_json,"params"); 
				Serial_Printf("params success!\r\n");
				LED_json = cJSON_GetObjectItem(params_json,"LED");
				Serial_Printf("LEDsuccess!\r\n");
				Fan_json = cJSON_GetObjectItem(params_json,"FAN");
				Serial_Printf("FAN success!\r\n");
				Servo_json = cJSON_GetObjectItem(params_json,"SERVO");
				Serial_Printf("SERVO\r\n");
				if(LED_json != NULL)
				{
					Serial_Printf("data:%d\r\n",LED_json->type);
					Serial_Printf("valueString:%s\r\n",LED_json->valuestring);
					if(LED_json->type == cJSON_String)
					{
						if(strcmp(LED_json->valuestring,"LEDON") == 0)
							LED2_On();
						if(strcmp(LED_json->valuestring,"LEDOFF") == 0)
							LED2_Off();
					}
				}
				if(Fan_json != NULL)
				{
					Serial_Printf("data:%d\r\n",Fan_json->type);
					Serial_Printf("valueString:%d\r\n",Fan_json->valueint);
					if(Fan_json->type == cJSON_Number)
					{
							Speed=Fan_json->valueint;   //设置速度
					}
				}
				if(Servo_json != NULL)
				{
					Serial_Printf("data:%d\r\n",Servo_json->type);
					Serial_Printf("valueString:%d\r\n",Servo_json->valueint);
					if(Servo_json->type == cJSON_Number)
					{
							Angle=(float)Servo_json->valueint;   //虚拟按键置为1
							Serial_Printf("%.3f\r\n",Angle);
					}
				}
				cJSON_Delete(raw_json);
			}
		case MQTT_PKT_PUBACK:														//发送Publish消息，平台回复的Ack
		
			if(MQTT_UnPacketPublishAck(cmd) == 0)
				Serial_Printf( "Tips:	MQTT Publish Send OK\r\n");
			
		break;
		
		case MQTT_PKT_SUBACK:																//发送Subscribe消息的Ack
		
			if(MQTT_UnPacketSubscribe(cmd) == 0)
				Serial_Printf( "Tips:	MQTT Subscribe OK\r\n");
			else
				Serial_Printf( "Tips:	MQTT Subscribe Err\r\n");
		
		break;
		
		default:
			result = -1;
		break;
	}
	
	ESP8266_Clear();									//清空缓存
	
	if(result == -1)
		return;
	
	if(type == MQTT_PKT_CMD || type == MQTT_PKT_PUBLISH)
	{
		MQTT_FreeBuffer(cmdid_topic);
		MQTT_FreeBuffer(req_payload);
	}
}
