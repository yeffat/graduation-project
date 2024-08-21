
/*Preprocessor Guard*/
#ifndef UART_INTERFACE_H 
#define UART_INTERFACE_H 
#include "..\..\LIB\STD_TYPES.h"
/*
 * Description: Function to initialize the UART peripheral

 * Inputs: none
 * Output: void
 */

void UART_vInit(void);

/*
 * Description: Function to send a single character by UART through TXD pin (PD0)
 * Inputs: the character needed to be sent
 * Output: the Error state of the function
 */
uint8_t UART_u8SendChar (uint8_t Copy_u8Char);

/*
 * Description: Synchronous Function to send string by UART through TXD pin (PD0)
 * Inputs: pointer to array of characters
 * Output: the Error state of the function
 */
uint8_t UART_u8SendStringSynch (const uint8_t* Copy_u8Data);

/*
 * Description: Asynchronous Function to start sending a string by UART through TXD pin (PD0)
 * 				then the Data Register Empty interrupt will send the rest of the string continuously
 * Inputs: pointer to array of characters and the callback function to notify the upper layer
 *         that the complete message is successfully sent
 * Output: the Error state of the function
 */
uint8_t UART_u8SendStringAsynch ( uint8_t* Copy_u8Data,void (*Callback)(void));


/*
 * Description: Function to receive a single character by UART through RXD pin (PD1)
 * Inputs: pointer to the variable that will hold the received character
 * Output: the Error state of the function
 */
uint8_t UART_u8ReceiveChar (uint8_t *Copy_u8Char);

/*
 * Description: Synchronous Function to receive string by UART through RXD pin (PD1)
 * Inputs: a pointer to array of character which will hold the received string and the message Size
 * Output: the Error state of the function
 */
uint8_t UART_u8ReceiveStringSynch (uint8_t* Copy_u8ReceivedData,uint8_t Copy_u8MessageLength);

/*
 * Description: Asynchronous Function to start receiving string by UART through RXD pin (PD1)
 * 			    then the  Rx Complete interrupt will receive the rest of the string continuously
 * Inputs: a pointer to array of character which will hold the received string + the message Size
 *         + the callback function to notify the upper layer that the complete message is successfully sent
 * Output: the Error state of the function
 */
uint8_t UART_u8ReceiveStringAsynch (uint8_t* Copy_u8ReceivedData,uint8_t Copy_u8MessageLength,void (*Callback)(void));

#endif /* UART_INTERFACE_H */ 
