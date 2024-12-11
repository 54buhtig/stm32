#include "stm32f10x.h"                  // Device header
#include <time.h>

uint16_t MyRTC_Time[]={2024,12,31,23,59,54};
void MyRTC_SetTime(void);

/**
   * @brief  RTC初始化
   * @param  无
   * @retval 无
   */
void MyRTC_Init(void)
{
	//第1步：开启PWR和BKP的时钟，使能BKP和RTC的访问
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	
	
	if(BKP_ReadBackupRegister(BKP_DR1)!=0x7788) //通过BKP的特性保证掉电后不用重新初始化
	{
		//第2步：设置RTCCLK的时钟源
		RCC_LSEConfig(RCC_LSE_ON);
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)!=SET);
	//	RCC_LSICmd(ENABLE);
	//	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY)!=SET);	
		
		
		//第3步：配置时钟源选择
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
	//	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	//	RCC_RTCCLKCmd(ENABLE);	
		
		//第4步：等待同步和上次操作完成
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
		
		
		//第5步：配置预分频器,对32768进行分频
		RTC_SetPrescaler(32768-1);
	//	RTC_SetPrescaler(40000-1);
		RTC_WaitForLastTask();
		
		
		//第6步:设置初始时间
	//	RTC_SetCounter(1672588795);
	//	RTC_WaitForLastTask();
		MyRTC_SetTime();
		
		
		BKP_WriteBackupRegister(BKP_DR1,0x7788);
	}
	else
	{
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
		
	}
	
	
	
}


/**
   * @brief  用来设置初始时间
   * @param  无
   * @retval 无
   */
void MyRTC_SetTime(void)
{
	time_t time_cnt;
	struct tm time_date;
	
	time_date.tm_year=MyRTC_Time[0]-1900;
	time_date.tm_mon=MyRTC_Time[1]-1;
	time_date.tm_mday=MyRTC_Time[2];
	time_date.tm_hour=MyRTC_Time[3];
	time_date.tm_min=MyRTC_Time[4];
	time_date.tm_sec=MyRTC_Time[5];


	time_cnt = mktime(&time_date)-8*60*60;  //将东8时间自动转化为0时区时间
	
	RTC_SetCounter(time_cnt);
	RTC_WaitForLastTask();
	
}

/**
   * @brief   读取CNT的值并转化为年月日时分秒 
   * @param   无
   * @retval  无
   */
void MyRTC_ReadTime(void)
{
	time_t time_cnt;
	struct tm time_date;

	time_cnt = RTC_GetCounter()+8*60*60;  //加入8个小时的偏移
	
	time_date = *localtime(&time_cnt);
	
	MyRTC_Time[0] = time_date.tm_year+1900 ;
	MyRTC_Time[1] = time_date.tm_mon +1;
	MyRTC_Time[2] = time_date.tm_mday;
	MyRTC_Time[3] = time_date.tm_hour;
	MyRTC_Time[4] = time_date.tm_min;
	MyRTC_Time[5] = time_date.tm_sec;	
	
}







