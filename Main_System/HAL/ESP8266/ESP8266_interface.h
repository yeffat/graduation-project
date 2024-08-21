#ifndef ESP8266_INTERFACE_H_
#define ESP8266_INTERFACE_H_


void ESP8266_Init(void);
void ESP8266_ConnectToWiFi(void);
void ESP8266_SendData(const char *data);

#endif // ESP8266_INTERFACE_H_
