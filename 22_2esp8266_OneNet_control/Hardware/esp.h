#ifndef __esp_H
#define __esp_H

int contains_substring(const u8 *main_string, const char *substring);
char esp_Init(void);
char Esp_PUB(void);
int esp_Get_LED(void);
void esp_Get_Data(void);
#endif
