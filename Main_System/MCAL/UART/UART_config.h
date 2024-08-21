
/*Preprocessor Guard*/
#ifndef UART_CONFIG_H 
#define UART_CONFIG_H 


/*Macro to define the System clock which feeds the UART peripherl*/
#define FCPU               8000000

/*Macto to specify the desired UART Baudrate*/
#define UART_u32_BAUDRATE   (uint32_t) 9600

#define UBRR_Value (((FCPU / (UART_u16_BAUDRATE * 16UL))) - 1)
/*
  Macro to specify the UART mode
  Ranges: UART_u8_NORMAL_MODE
		  UART_u8_DBL_SPD_MODE
		  UART_u8_DBL_SNQ_MSTR_MODE
*/
#define UART_u8_MODE		UART_u8_NORMAL_MODE

/*
  Macro to specify state of the UART transmitter and the receiver
  Ranges: UART_u8_ENABLE
		  UART_u8_DISABLE
*/
#define UART_u8_TX_STATE         UART_u8_ENABLE
#define UART_u8_RX_STATE         UART_u8_ENABLE

/*
  Macro to select the parity type
  Ranges: UART_u8_NO_PARITY
		  UART_u8_EVEN_PARITY
		  UART_u8_ODD_PARITY
*/
#define UART_u8_PARITY			UART_u8_NO_PARITY

/*
  Macro to select the number of the stop bits
  Ranges: UART_u8_ONE_BIT
		  UART_u8_TWO_BITS
*/
#define UART_u8_NO_OF_STP_BITS  UART_u8_ONE_BIT

/*
  Macro to select the number of the stop bits
  Ranges: UART_u8_FIVE_BITS
		  UART_u8_SIX_BITS
		  UART_u8_SEVEN_BITS
		  UART_u8_EIGHT_BITS
		  UART_u8_NINE_BITS
*/
#define UART_u8_DATA_SIZE		UART_u8_EIGHT_BITS

/* Macro to define the timeout which determines the fault time in the UART TX/RX */
#define UART_u16_FAULT_TIMEOUT    (uint16_t) 40000

#endif /* UART_CONFIG_H */ 

