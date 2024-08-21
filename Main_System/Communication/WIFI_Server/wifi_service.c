#include "WIFI_service.h"
#include "..\..\HAL\ESP8266\ESP8266_interface.h"
#include "..\..\HAL\ESP8266\ESP8266_config.h"

uint8_t WIFI_Init(void) {
    ESP8266_Init();
    ESP8266_ConnectToWiFi();
    return 0; // Return 0 to indicate success
}

uint8_t WIFI_SendEmptySlots(uint8_t emptySlots) {
    char json_data[50];
    char request[256];

    snprintf(json_data, sizeof(json_data), "{\"slots\":%d}", emptySlots);
    snprintf(request, sizeof(request),
             "POST %s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Content-Type: application/json\r\n"
             "Content-Length: %d\r\n\r\n"
             "%s",
             ESP8266_UPDATE_ENDPOINT, ESP8266_SERVER_URL, strlen(json_data), json_data);

    ESP8266_SendData(request);
    return 0; // Return 0 to indicate success
}
