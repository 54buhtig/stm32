#include "stm32f10x.h" // Device header
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "delay.h"
#include "esp.h"

#include "led.h"

extern u8 USART_RX_BUF[];

/**
 * @brief 判断主字符串中是否包含子字符串
 *
 * @param main_string 主字符串
 * @param substring 子字符串
 * @return int 如果包含子字符串返回1，否则返回0
 */
int contains_substring(const u8 *main_string, const char *substring)
{
	// 如果strstr()返回非空指针，则表示找到了子字符串
	if (strstr((const char *)main_string, substring) != NULL)
	{
		return 1; // 找到子字符串
	}
	else
	{
		return 0; // 未找到子字符串
	}
}

/**
 * @brief 复位ESP8266模块
 *
 */
void esp_Rst(void)
{
	memset(USART_RX_BUF, 0, sizeof(USART_RX_BUF)); // 清空接收缓冲区
	printf("AT+RST\r\n");						   // 发送复位指令
	while (0 == contains_substring(USART_RX_BUF, "OK\r\n"))
		;										   // 等待模块响应"OK\r\n"
	memset(USART_RX_BUF, 0, sizeof(USART_RX_BUF)); // 再次清空接收缓冲区
}

/**
 * @brief 向ESP8266发送指令并等待响应
 *
 * @param str 要发送的指令
 * @param res 期望的响应
 * @return int 执行结果，始终返回0
 */
int esp_Cmd(const char *str, const char *res)
{
	while (0 == contains_substring(USART_RX_BUF, res)) // 等待期望的响应
	{
		memset(USART_RX_BUF, 0, sizeof(USART_RX_BUF)); // 清空接收缓冲区
		printf("%s\r\n", str);						   // 发送指令
		Delay_ms(8000);
		Delay_ms(8000); // 等待响应
	}
	memset(USART_RX_BUF, 0, sizeof(USART_RX_BUF)); // 清空接收缓冲区

	return 0;
}

/**
 * @brief 初始化ESP8266模块
 *
 * @return char 初始化结果，始终返回0
 */
char esp_Init(void)
{
	/* 1.复位指令 */
	esp_Rst();

	/* 2.设置为station模式 */
	esp_Cmd("AT+CWMODE=1", "OK");

	/* 3.启动DHCP */
	esp_Cmd("AT+CWDHCP=1,1", "OK");

	/* 4.连接热点 */
	esp_Cmd("AT+CWJAP=\"TP-LINK_D9EB\",\"ljp548554\"", "OK");

	/* 5.配置MQTT用户信息 */
	esp_Cmd("AT+MQTTUSERCFG=0,1,\"dht11\",\"50ftPIy42a\",\"version=2018-10-31&res=products%2F50ftPIy42a%2Fdevices%2Fdht11&et=1784415600&method=md5&sign=Co%\",0,0,\"\"", "OK");

	/* 6.建立MQTT连接 */
	esp_Cmd("AT+MQTTCONN=0,\"mqtts.heclouds.com\",1883,1", "OK");

	/* 7.订阅主题 */
	// 主题用于接收服务器对客户端发布消息的回复
	esp_Cmd("AT+MQTTSUB=0,\"$sys/0S43la9qNI/LED/thing/property/post/reply\",1", "OK");

	// esp_Cmd("AT+MQTTSUB=0,\"$sys/0S43la9qNI/LED/thing/property/post/set_reply\",1", "OK");

	// 主题用于接收服务器下发的属性设置命令
	esp_Cmd("AT+MQTTSUB=0,\"$sys/50ftPIy42a/dht11/thing/property/set\",1", "OK");

	/* 8.发布消息 */
	esp_Cmd("AT+MQTTPUB=0,\"$sys/50ftPIy42a/dht11/thing/property/post\",\"{\\\"id\\\":\\\"123\\\"\\,\\\"params\\\":{\\\"LED01\\\":{\\\"value\\\":true}}}\",0,0", "success");

	// esp_Cmd("AT+MQTTPUB=0,\"$sys/0S43la9qNI/LED/thing/property/set_reply\",\"{\\\"id\\\":\\\"56\\\",\\\"code\\\":200,\\\"msg\\\":\\\"success\\\"}\",0,0", "ok");

	// esp_Cmd("AT+MQTTPUB=0,\"$sys/0S43la9qNI/LED/thing/property/set_reply\",\"{\\\"id\\\":\\\"52\\\",\\\"code\\\":200,\\\"msg\\\":\\\"success\\\",\\\"data\\\":{\\\"LightSwitch\\\":true}}\",0,0", "ok");
	return 0;
}


/**
 * @brief 检查接收到的数据中是否包含特定的设备和属性。
 *
 * @param res1 设备名或关键字，用于识别设备。
 * @param res2 属性值，用于识别设备的属性状态。
 * @return int 如果接收到的数据中包含指定的设备和属性，则返回1，否则返回0。
 */
int esp_Get(const char *res1, const char *res2)
{
	// 示例接收数据格式："+MQTTSUBRECV:0,\"$sys/0S43la9qNI/LED/thing/property/set\",58,{\"id\":\"58\",\"version\":\"1.0\",\"params\":{\"LightSwitch\":false}}"

	/* 检查接收缓冲区中是否包含指定的设备名或关键字 */
	if (1 == contains_substring(USART_RX_BUF, res1))
	{
		/* 如果包含设备名，再检查是否包含指定的属性值 */
		if (1 == contains_substring(USART_RX_BUF, res2))
		{
			return 1; // 找到匹配的设备和属性
		}
	}
	return 0; // 未找到匹配的设备和属性
}

/**
 * @brief 根据接收到的数据设置LED的状态。
 *
 * @return int 返回处理结果，此处没有具体实现返回值，实际应用中可能需要返回状态。
 */
int esp_Get_LED(void)
{

	if (1 == esp_Get("LightSwitch", "false"))
	{
		LED1_Off();
	}
	else if (1 == esp_Get("LightSwitch", "true"))
	{
		LED1_On();
	}
	return 1;
}



void esp_Get_Data(void)
{
	esp_Get_LED();
	memset(USART_RX_BUF, 0, sizeof(USART_RX_BUF)); // 清空接收缓冲区
}

