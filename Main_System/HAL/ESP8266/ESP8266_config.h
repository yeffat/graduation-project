#ifndef ESP8266_CONFIG_H_
#define ESP8266_CONFIG_H_

/* Wi-Fi Configuration */
#define ESP8266_WIFI_SSID        "simple"
#define ESP8266_WIFI_PASSWORD    "12345678"

/* Server Configuration */
#define ESP8266_SERVER_URL       "render-two.vercel.app"
#define ESP8266_SERVER_PORT      "80"
#define ESP8266_UPDATE_ENDPOINT  "/update-slots/1"

/* LED Configuration */
#define WIFI_POWER_LED_PORT      DIO_PORTC
#define WIFI_POWER_LED_PIN       DIO_PIN0

#define WIFI_CONNECTED_LED_PORT  DIO_PORTC
#define WIFI_CONNECTED_LED_PIN   DIO_PIN1

#define WIFI_SENDING_LED_PORT    DIO_PORTC
#define WIFI_SENDING_LED_PIN     DIO_PIN2

#endif // ESP8266_CONFIG_H_
