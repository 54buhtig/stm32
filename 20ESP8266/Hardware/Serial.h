#ifndef __SERIAL__H_
#define __SERIAL__H_


#include <stdio.h>

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t* Array, uint16_t Length);
void Serial_SendString(char* String);
void Serial_SendNumber(uint32_t Number,uint8_t Length );
void Serial2_Printf(char* format,...);
uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);

#endif
