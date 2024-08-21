
#include "UART_config.h"
#include "UART_interface.h"
#include "UART_priv.h"
#include "..\..\LIB\STD_TYPES.h"
#include "..\..\LIB\BIT_MATH.h"

/*Static pointer to the passed string needed to be sent using the Asynchronous transmitting function*/
static uint8_t *UART_pu8TransmittedString;

/*Static pointer to the passed array needed to be filled using the Asynchronous receiving function*/
static uint8_t *UART_pu8ReceivedString;

/*Static variable that will be equal the required length of the received msg*/
static uint8_t UART_u8ReceivedMsgSize;

/* Incremented index using in asynchronous transmitting and receiving */
static uint8_t UART_u8Index;

static void (*PtrASychCallback) (void) = NULL;

/*
 * Description: Function to initialize the UART peripheral
 * Inputs: none
 * Output: void
 */
void UART_vInit(void)
{
	uint16_t Local_u16BaudRateCalc;

	#if (UART_u8_MODE == UART_u8_NORMAL_MODE)
		Local_u16BaudRateCalc = ((FCPU/(UART_u32_BAUDRATE*16))-1);
		UART_UBRRL = (Local_u16BaudRateCalc);
		UART_UBRRH = ((Local_u16BaudRateCalc) >> 8);

		/* Checking the transmitter state */
		if (UART_u8_TX_STATE == UART_u8_ENABLE)
			 SET_BIT(UART_UCSRB,TXEN);

		/* Checking the receiver state */
		if (UART_u8_RX_STATE == UART_u8_ENABLE)
			 SET_BIT(UART_UCSRB,RXEN);

		/* Checking the parity type */
		if (UART_u8_PARITY == UART_u8_EVEN_PARITY)
			UART_UCSRC |= (1 << URSEL) | (1 << UPM1);
		else if (UART_u8_PARITY == UART_u8_ODD_PARITY)
			UART_UCSRC |= (1 << URSEL) | (1 << UPM1) | (1 << UPM0);

		/* Checking the number of stop bits */
		if (UART_u8_NO_OF_STP_BITS == UART_u8_TWO_BITS)
			UART_UCSRC |= (1 << URSEL) | (1 << USBS);

		/* Checking the required character size */
		switch (UART_u8_DATA_SIZE)
		{
		    case UART_u8_SIX_BITS:
		    {
		    	UART_UCSRC |= (1 << URSEL) | (1 << UCSZ0);
		    	break;
		    }
		    case UART_u8_SEVEN_BITS:
		    {
		    	UART_UCSRC |= (1 << URSEL) | (1 << UCSZ1);
		    	break;
		    }
		    case UART_u8_EIGHT_BITS:
		    {
		    	UART_UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
		    	break;
		    }
		    case UART_u8_NINE_BITS:
		    {
		    	UART_UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
		    	SET_BIT(UART_UCSRB,UCSZ2);
		    	break;
		    }
		}
	#elif (UART_u8_MODE == UART_u8_DBL_SPD_MODE)
		SET_BIT(UART_UCSRA,U2X);
		Local_u16BaudRateCalc = ((FCPU/(UART_u32_BAUDRATE*8))-1);
		UART_UBRRL = Local_u16BaudRateCalc;
		UART_UBRRH = ((Local_u16BaudRateCalc) >> 8);

		/* Checking the transmitter state */
		if (UART_u8_TX_STATE == UART_u8_ENABLE)
			 SET_BIT(UART_UCSRB,TXEN);

		/* Checking the receiver state */
		if (UART_u8_RX_STATE == UART_u8_ENABLE)
			 SET_BIT(UART_UCSRB,RXEN);

		/* Checking the parity type */
		if (UART_u8_PARITY == UART_u8_EVEN_PARITY)
			UART_UCSRC |= (1 << URSEL) | (1 << UPM1);
		else if (UART_u8_PARITY == UART_u8_ODD_PARITY)
			UART_UCSRC |= (1 << URSEL) | (1 << UPM1) | (1 << UPM0);

		/* Checking the number of stop bits */
		if (UART_u8_NO_OF_STP_BITS == UART_u8_TWO_BITS)
			UART_UCSRC |= (1 << URSEL) | (1 << USBS);

		/* Checking the required character size */
		switch (UART_u8_DATA_SIZE)
		{
		    case UART_u8_SIX_BITS:
		    {
		    	UART_UCSRC |= (1 << URSEL) | (1 << UCSZ0);
		    	break;
		    }
		    case UART_u8_SEVEN_BITS:
		    {
		    	UART_UCSRC |= (1 << URSEL) | (1 << UCSZ1);
		    	break;
		    }
		    case UART_u8_EIGHT_BITS:
		    {
		    	UART_UCSRC |= (1 << URSEL) | (1 << USBS) | (1 << UCSZ0);
		    	break;
		    }
		    case UART_u8_NINE_BITS:
		    {
		    	UART_UCSRC |= (1 << URSEL) | (1 << USBS) | (1 << UCSZ0);
		    	SET_BIT(UART_UCSRB,UCSZ2);
		    	break;
		    }
		}
	#elif (UART_u8_MODE == UART_u8_DBL_SNQ_MSTR_MODE)
		UART_UCSRC |= (1 << URSEL) | (1 << UMSEL);
		Local_u16BaudRateCalc = ((FCPU/(UART_u32_BAUDRATE*2))-1);
		UART_UBRRL = Local_u16BaudRateCalc;
		UART_UBRRH = ((Local_u16BaudRateCalc) >> 8);
	#endif

	return;
}

/*
 * Description: Function to send a single character by UART through TXD pin (PD0)
 * Inputs: the character needed to be sent
 * Output: the Error state of the function
 */
uint8_t UART_u8SendChar (uint8_t Copy_u8Char)
{
	/*Local Variable holding the error state*/
	uint8_t Local_u8Error = ERROR_OK;
	uint16_t Local_u16Timeout = 0;

	/* Put data into buffer, sends the data */
	UART_UDR = Copy_u8Char;

	/* Wait for empty transmit buffer and checking that the timeout var doesn't exceed
	 * the fault timeout */
	while (GET_BIT(UART_UCSRA,UDRE) == 0 && Local_u16Timeout < UART_u16_FAULT_TIMEOUT)
	{
		Local_u16Timeout++;
	}

	if (Local_u16Timeout == UART_u16_FAULT_TIMEOUT)
		Local_u8Error = ERROR_NOK;

	/*Function return*/
	return Local_u8Error;
}

/*
 * Description: Synchronous Function to send string by UART through TXD pin (PD0)
 * Inputs: pointer to array of characters
 * Output: the Error state of the function
 */
uint8_t UART_u8SendStringSynch (const uint8_t* Copy_u8Data)
{
	/*Local Variable holding the error state*/
	uint8_t Local_u8Error = ERROR_OK;
	uint16_t Local_u16Timeout = 0;

	if (Copy_u8Data != NULL)
	{
		while (*Copy_u8Data != '\0')
		{
			Local_u16Timeout = 0;

			/* Put data into buffer, sends the data */
			UART_UDR = *Copy_u8Data;

			/* Wait for empty transmit buffer and checking that the timeout variable doesn't exceed
			 * the fault timeout */
			while (GET_BIT(UART_UCSRA,UDRE) == 0 && Local_u16Timeout < UART_u16_FAULT_TIMEOUT)
			{
				Local_u16Timeout++;
			}

			if (Local_u16Timeout != UART_u16_FAULT_TIMEOUT)
				Copy_u8Data++;
			else
			{
				Local_u8Error = ERROR_NOK;
				break;
			}
		}
	}
	else
	{
		Local_u8Error = ERROR_NOK;
	}

	/*Function return*/
	return Local_u8Error;
}

/*
 * Description: Asynchronous Function to start sending a string by UART through TXD pin (PD0)
 * 				then the Data Register Empty interrupt will send the rest of the string continuously
 * Inputs: pointer to array of characters and the callback function to notify the upper layer
 *         that the complete message is successfully sent
 * Output: the Error state of the function
 */
uint8_t UART_u8SendStringAsynch ( uint8_t* Copy_u8Data,void (*Callback)(void))
{
	/*Local Variable holding the error state*/
	uint8_t Local_u8Error = ERROR_OK;

	if (Copy_u8Data != NULL && Callback != NULL)
	{
		UART_u8Index = 0;

		/*Enabling Data Register Empty interrupt */
		SET_BIT(UART_UCSRB,UDRIE);

		UART_pu8TransmittedString = Copy_u8Data;

		/* Linking the driver pointer to function to the passed callback function */
		PtrASychCallback = Callback;
	}
	else
	{
		Local_u8Error = ERROR_NOK;
	}

	/*Function return*/
	return Local_u8Error;
}

/*
 * Description: Function to receive a single character by UART through RXD pin (PD1)
 * Inputs: pointer to the variable that will hold the received character
 * Output: the Error state of the function
 */
uint8_t UART_u8ReceiveChar (uint8_t *Copy_u8Char)
{
	/*Local Variable holding the error state*/
	uint8_t Local_u8Error = ERROR_OK;
	uint16_t Local_u16Timeout = 0;

	if (Copy_u8Char != NULL)
	{
		/* Wait for empty receive buffer and checking that the timeout var doesn't exceed
		 * the fault timeout */
		while (GET_BIT(UART_UCSRA,RXC) == 0 && Local_u16Timeout < UART_u16_FAULT_TIMEOUT)
		{
			Local_u16Timeout++;
		}

		if (Local_u16Timeout == UART_u16_FAULT_TIMEOUT)
			Local_u8Error = ERROR_NOK;
		else
			/* Get and return received data from buffer */
			*Copy_u8Char = UART_UDR;

	}
	else
	{
		Local_u8Error = ERROR_NOK;
	}

	/*Function return*/
	return Local_u8Error;
}

/*
 * Description: Synchronous Function to receive string by UART through RXD pin (PD1)
 * Inputs: a pointer to array of character which will hold the received string and the message Size
 * Output: the Error state of the function
 */
uint8_t UART_u8ReceiveStringSynch (uint8_t* Copy_u8ReceivedData,uint8_t Copy_u8MessageLength)
{
	/*Local Variable holding the error state*/
	uint8_t Local_u8Error = ERROR_OK;
	uint8_t Local_u8LoopIndex;
	uint16_t Local_u16Timeout = 0;

	if (Copy_u8ReceivedData != NULL)
	{
		for (Local_u8LoopIndex = 0 ; Local_u8LoopIndex < Copy_u8MessageLength;Local_u8LoopIndex++)
		{
			/* Wait for data to be received and checking that the timeout variable doesn't exceed
			 * the fault timeout */
			while (GET_BIT(UART_UCSRA,RXC) == 0 && Local_u16Timeout < UART_u16_FAULT_TIMEOUT)
			{
				Local_u16Timeout++;
			}

			if (Local_u16Timeout != UART_u16_FAULT_TIMEOUT)
				/* Get and return received data from buffer */
				Copy_u8ReceivedData[Local_u8LoopIndex] = UART_UDR;
			else
			{
				Local_u8Error = ERROR_NOK;
				break;
			}
		}
	}
	else
	{
		Local_u8Error = ERROR_NOK;
	}

	/*Function return*/
	return Local_u8Error;
}

/*
 * Description: Asynchronous Function to start receiving string by UART through RXD pin (PD1)
 * 			    then the  Rx Complete interrupt will receive the rest of the string continuously
 * Inputs: a pointer to array of character which will hold the received string + the message Size
 *         + the callback function to notify the upper layer that the complete message is successfully sent
 * Output: the Error state of the function
 */
uint8_t UART_u8ReceiveStringAsynch (uint8_t* Copy_u8ReceivedData,uint8_t Copy_u8MessageLength,void (*Callback)(void))
{
	/*Local Variable holding the error state*/
	uint8_t Local_u8Error = ERROR_OK;


	if (Copy_u8ReceivedData != NULL && Callback != NULL)
	{
		UART_u8Index = 0;
		UART_pu8ReceivedString = Copy_u8ReceivedData;
		UART_u8ReceivedMsgSize = Copy_u8MessageLength;

		/* Linking the driver pointer to function to the passed callback function */
		PtrASychCallback = Callback;

		/*Enabling Data Register Empty interrupt */
		SET_BIT(UART_UCSRB,UDRIE);
	}
	else
	{
		Local_u8Error = ERROR_NOK;
	}

	/*Function return*/
	return Local_u8Error;
}
/************************************************************/
/*      ISRs of UART interrupts                             */
/************************************************************/
/*The ISR of USART, Rx Complete interrupt*/
void __vector_13 (void)
{
	/* Put data into buffer, sends the data */
	UART_pu8ReceivedString[UART_u8Index] = UART_UDR;

	UART_u8Index++;

	if (UART_u8Index == UART_u8ReceivedMsgSize)
	{
		UART_u8Index = 0;
		CLR_BIT(UART_UCSRB,RXCIE);
		PtrASychCallback();
	}
}

/*The ISR of USART Data Register Empty interrupt*/
void __vector_14 (void)
{
	if (UART_pu8TransmittedString[UART_u8Index] != '\0')
		/* Put data into buffer, sends the data */
		UART_UDR = UART_pu8TransmittedString[UART_u8Index];
	else
	{
		UART_u8Index = 0;
		PtrASychCallback();
		CLR_BIT(UART_UCSRB,UDRIE);
	}

	UART_u8Index++;

	return;
}

/*The ISR of USART, Tx Complete interrupt*/
void __vector_15 (void)
{
	return;
}


