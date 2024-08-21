#include "..\..\LIB\STD_TYPES.h"
#include "..\..\MCAL\UART\UART_interface.h"
#include "..\..\LIB\DELAY\DELAY_interface.h"
#include "..\..\MCAL\DIO\DIO_int.h"
#include "ESP8266_interface.h"
#include "ESP8266_private.h"
#include "ESP8266_config.h"

#include <string.h>

void ESP8266_Init(void) {
    UART_vInit();
    DIO_U8SetPinDirection(WIFI_POWER_LED_PORT, WIFI_POWER_LED_PIN, DIO_OUTPUT);
    DIO_U8SetPinDirection(WIFI_CONNECTED_LED_PORT, WIFI_CONNECTED_LED_PIN, DIO_OUTPUT);
    DIO_U8SetPinDirection(WIFI_SENDING_LED_PORT, WIFI_SENDING_LED_PIN, DIO_OUTPUT);

    DIO_U8SetPinValue(WIFI_POWER_LED_PORT, WIFI_POWER_LED_PIN, DIO_HIGH); // Turn on power LED

    delay_milliseconds(200); // Wait for the ESP8266 to initialize

    UART_u8SendStringSynch((const uint8_t*)"AT\r\n");
    delay_milliseconds(1000); // Small delay before next command

    UART_u8SendStringSynch((const uint8_t*)"AT+RST\r\n");
    delay_milliseconds(10000); // Wait for the ESP8266 to reset

    UART_u8SendStringSynch((const uint8_t*)"AT+CWMODE=1\r\n");
    delay_milliseconds(1000); // Small delay before next command
}

void ESP8266_ConnectToWiFi(void) {
    char command[100];
    snprintf(command, sizeof(command), "AT+CWJAP=\"%s\",\"%s\"\r\n", ESP8266_WIFI_SSID, ESP8266_WIFI_PASSWORD);
    UART_u8SendStringSynch((const uint8_t*)command);

    delay_milliseconds(10000); // Wait for the ESP8266 to connect to Wi-Fi

    DIO_U8SetPinValue(WIFI_CONNECTED_LED_PORT, WIFI_CONNECTED_LED_PIN, DIO_HIGH); // Turn on connected LED
}

void ESP8266_SendData(const char *data) {
    char command[100];

    DIO_U8SetPinValue(WIFI_SENDING_LED_PORT, WIFI_SENDING_LED_PIN, DIO_HIGH); // Turn on sending LED

    snprintf(command, sizeof(command), "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", ESP8266_SERVER_URL, ESP8266_SERVER_PORT);
    UART_u8SendStringSynch((const uint8_t*)command);
    delay_milliseconds(2000); // Wait for the connection to establish

    snprintf(command, sizeof(command), "AT+CIPSEND=%d\r\n", strlen(data));
    UART_u8SendStringSynch((const uint8_t*)command);
    delay_milliseconds(200); // Wait for the prompt

    UART_u8SendStringSynch((const uint8_t*)data);
    delay_milliseconds(2000); // Wait for the data to be sent

    DIO_U8SetPinValue(WIFI_SENDING_LED_PORT, WIFI_SENDING_LED_PIN, DIO_LOW); // Turn off sending LED
}
