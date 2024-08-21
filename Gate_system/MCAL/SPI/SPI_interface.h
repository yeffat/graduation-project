

/*Preprocessor Guard*/
#ifndef SPI_INTERFACE_H 
#define SPI_INTERFACE_H 
#include "../../LIB/STD_TYPES.h"

/*
 * Description: Function to initialize the SPI peripheral
 * Inputs: none
 * Output: void
 */
void SPI_vInit (void);

/*
 * Description: Synchronous Function to send and receive a byte using polling mechanism
 * Inputs: the byte needed to be sent and a pointer to received byte
 * Output: the Error state of the function
 */
uint8_t SPI_u8ReceiveByte_Synch (uint8_t *Copy_pu8RecByte);
uint8_t SPI_u8SendByte_Synch (uint8_t Copy_u8SentByte);
/*
 * Description: Asynchronous Function to start sending a string using Serial Transfer Complete interrupt
 * Inputs: (1) pointer to array of characters needed to be sent
 * 		   (2) pointer to array of characters that is supposed to be received
 * 		   (3) the expected size of the transmitted and received buffer
 * 		   (4) the callback function to notify the upper layer that the complete message is successfully sent
 * Output: the Error state of the function
 */
uint8_t SPI_u8SendReceiveBuffer_Asynch (uint8_t *Copy_pu8SentBuffer,uint8_t *Copy_pu8RecBuffer,uint8_t Copy_u8NoOfBytes,void (*CallBack)(void));



#endif /* SPI_INTERFACE_H */ 
