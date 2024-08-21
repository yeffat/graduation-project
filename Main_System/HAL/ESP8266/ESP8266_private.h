#ifndef ESP8266_PRIVATE_H_
#define ESP8266_PRIVATE_H_


/**
 * @brief Sends an AT command to the ESP8266 module and checks for the expected response.
 *
 * @param command The AT command to send.
 * @param expected_response The expected response from the ESP8266.
 * @param delay Delay in milliseconds after sending the command.
 * @return uint8_t Status of the command (ERROR_OK or ERROR_NOK).
 */
static uint8_t ESP8266_SendCommand(const char *command, const char *expected_response, uint16_t delay);

/**
 * @brief Reads the response from the ESP8266 module.
 *
 * @param response Buffer to store the response.
 * @param length Length of the response buffer.
 * @return uint8_t Status of the read operation (ERROR_OK or ERROR_NOK).
 */
static uint8_t ESP8266_ReadResponse(char *response, uint16_t length);

#endif // ESP8266_PRIVATE_H_
