
#include "SPI_interface.h"
#include "SPI_priv.h"
#include "SPI_config.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

/*Static pointer to the passed string needed to be sent using the Asynchronous transmitting function*/
static uint8_t *SPI_pu8TransmittedString;

/*Static pointer to the passed array needed to be filled using the Asynchronous receiving function*/
static uint8_t *SPI_pu8ReceivedString;

/*Static variable that will be equal the required length of the received msg*/
static uint8_t SPI_u8NoOfBytes;

/* Incremented index using in asynchronous transmitting and receiving */
static uint8_t SPI_u8Index;

/* Static Global callback function whic refers to the function needed to be called after finishing transmission the buffer*/
static void (*PtrASychCallback) (void) = NULL;

/*
 * Description: Function to initialize the SPI peripheral
 * Inputs: none
 * Output: void
 */
void SPI_vInit (void)
{
	if (SPI_u8_SELECTROLE == SPI_u8_MASTER)
	{
		SET_BIT(SPI_SPCR,MSTR);
	}

	if (SPI_u8_DATA_ORDER == SPI_u8_LSB)
	{
		SET_BIT(SPI_SPCR,DORD);
	}

	if (SPI_u8_CLKPOL == SPI_u8_FALLINGEDGE)
	{
		SET_BIT(SPI_SPCR,CPOL);
	}

	if (SPI_u8_CLKPHASE == SPI_u8_SETUP)
	{
		SET_BIT(SPI_SPCR,CPHA);
	}

	SPI_SPCR |= SPI_u8_SPRBITS;

	  //if Double SPI Speed is selected
	if (SPI_u8_CLKRATE > 3)
		SET_BIT(SPI_SPSR,SPI2X);

	SET_BIT(SPI_SPCR,SPE);
	return;
}

/*
 * Description: Synchronous Function to send and receive a byte using polling mechanism
 * Inputs: the byte needed to be sent and a pointer to received byte
 * Output: the Error state of the function
 */
uint8_t SPI_u8ReceiveByte_Synch(uint8_t *Copy_pu8RecByte) {
    /* Local Variable holding the error state */
    uint8_t Local_u8Error = ERROR_NOK;
    uint16_t Local_u16Timeout = 0;

    /* Check if the receive buffer pointer is valid */
    if (Copy_pu8RecByte != NULL) {
        /* Wait for reception to complete */
        while (GET_BIT(SPI_SPSR, SPIF) == 0 && Local_u16Timeout < SPI_u16_FAULT_TIMEOUT) {
            Local_u16Timeout++;
        }

        /* Check if the timeout occurred */
        if (Local_u16Timeout == SPI_u16_FAULT_TIMEOUT) {
            return ERROR_NOK;
        }

        /* Read the received data from SPDR */
        *Copy_pu8RecByte = SPI_SPDR;

        /* Set the error state to OK as the reception completed successfully */
        Local_u8Error = ERROR_OK;
    }

    /* Function return */
    return Local_u8Error;
}

uint8_t SPI_u8SendByte_Synch(uint8_t Copy_u8SentByte) {
    /* Local Variable holding the error state */
    uint8_t Local_u8Error = ERROR_NOK;
    uint16_t Local_u16Timeout = 0;

    /* Start the transmission by writing the data to SPDR */
    SPI_SPDR = Copy_u8SentByte;

    /* Wait for the transmission to complete */
    while (GET_BIT(SPI_SPSR, SPIF) == 0 && Local_u16Timeout < SPI_u16_FAULT_TIMEOUT) {
        Local_u16Timeout++;
    }

    /* Check if the timeout occurred */
    if (Local_u16Timeout == SPI_u16_FAULT_TIMEOUT) {
        return ERROR_NOK;
    }

    /* Set the error state to OK as the transmission completed successfully */
    Local_u8Error = ERROR_OK;

    /* Function return */
    return Local_u8Error;
}


/*
 * Description: Asynchronous Function to start sending a string using Serial Transfer Complete interrupt
 * Inputs: (1) pointer to array of characters needed to be sent
 * 		   (2) pointer to array of characters that is supposed to be received
 * 		   (3) the expected size of the transmitted and received buffer
 * 		   (4) the callback function to notify the upper layer that the complete message is successfully sent
 * Output: the Error state of the function
 */
uint8_t SPI_u8SendReceiveBuffer_Asynch (uint8_t *Copy_pu8SentBuffer,uint8_t *Copy_pu8RecBuffer,uint8_t Copy_u8NoOfBytes,void (*CallBack)(void))
{
	/*Local Variable holding the error state*/
	uint8_t Local_u8Error = ERROR_NOK;

	if (Copy_pu8SentBuffer != NULL && Copy_pu8RecBuffer != NULL && CallBack != NULL)
	{
		Local_u8Error = ERROR_OK;
		SPI_pu8TransmittedString = Copy_pu8SentBuffer;
		SPI_pu8ReceivedString = Copy_pu8RecBuffer;
		PtrASychCallback = CallBack;
		SPI_u8NoOfBytes = Copy_u8NoOfBytes;
		SPI_SPDR = SPI_pu8TransmittedString[SPI_u8Index];
		SET_BIT(SPI_SPCR,SPIE);
	}
	/*Function return*/
	return Local_u8Error;
}

/* The ISR of Serial Transfer Complete */
void __vector_12 (void)
{
	SPI_pu8ReceivedString[SPI_u8Index] = SPI_SPDR;
	if (SPI_u8Index == SPI_u8NoOfBytes)
	{
		SPI_u8Index = 0;
		SPI_u8NoOfBytes = 0;
		CLR_BIT(SPI_SPCR,SPIE);
		PtrASychCallback();
	}
	else
	{
		SPI_u8Index++;
		SPI_SPDR = SPI_pu8TransmittedString[SPI_u8Index];
	}
	return;
}
