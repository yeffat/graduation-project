
/*Preprocessor Guard*/
#ifndef UART_PRIV_H 
#define UART_PRIV_H 

/*Private macros to define the possible UART modes*/
#define UART_u8_NORMAL_MODE              0
#define UART_u8_DBL_SPD_MODE             1
#define UART_u8_DBL_SNQ_MSTR_MODE        2

/*Private macros to define the possible states of UART Transmitter,Receiver and the interrupts*/
#define UART_u8_ENABLE                   (uint8_t)1
#define UART_u8_DISABLE 				 (uint8_t)0

/*Private macros to define the possible parity types*/
#define UART_u8_NO_PARITY                (uint8_t)0
#define UART_u8_EVEN_PARITY              (uint8_t)1
#define UART_u8_ODD_PARITY               (uint8_t)2

/*Private macros to define the number of stop bits and the data size*/
#define UART_u8_ONE_BIT                  (uint8_t)0
#define UART_u8_TWO_BITS                 (uint8_t)1
#define UART_u8_FIVE_BITS                (uint8_t)2
#define UART_u8_SIX_BITS                 (uint8_t)3
#define UART_u8_SEVEN_BITS               (uint8_t)4
#define UART_u8_EIGHT_BITS               (uint8_t)5
#define UART_u8_NINE_BITS                (uint8_t)6

/****************************************************************/
/* Defining UART regisiters                                     */
/****************************************************************/

#define UART_UDR			(*(volatile uint8_t*)0x2C)

#define UART_UCSRA			(*(volatile uint8_t*)0x2B)
/*Defining the bits of UART_UCSRA register*/
#define MPCM                 (uint8_t)0
#define U2X                  (uint8_t)1
#define PE                   (uint8_t)2
#define DOR                  (uint8_t)3
#define FE                   (uint8_t)4
#define UDRE                 (uint8_t)5
#define TXC                  (uint8_t)6
#define RXC                  (uint8_t)7


#define UART_UCSRB			(*(volatile uint8_t*)0x2A)
/*Defining the bits of UART_UCSRB register*/
#define TXB8                 (uint8_t)0
#define RXB8                 (uint8_t)1
#define UCSZ2                (uint8_t)2
#define TXEN                 (uint8_t)3
#define RXEN                 (uint8_t)4
#define UDRIE                (uint8_t)5
#define TXCIE                (uint8_t)6
#define RXCIE                (uint8_t)7

#define UART_UCSRC			(*(volatile uint8_t*)0x40)
/*Defining the bits of UART_UCSRC register*/
#define UCPOL                (uint8_t)0
#define UCSZ0                (uint8_t)1
#define UCSZ1                (uint8_t)2
#define USBS                 (uint8_t)3
#define UPM0                 (uint8_t)4
#define UPM1                 (uint8_t)5
#define UMSEL                (uint8_t)6
#define URSEL                (uint8_t)7

#define UART_UBRRH			(*(volatile uint8_t*)0x40)
#define UART_UBRRL			(*(volatile uint8_t*)0x29)

/************************************************************/
/*      ISRs of UART interrupts                             */
/************************************************************/
/*The ISR of USART, Rx Complete interrupt*/
void __vector_13 (void) __attribute__((signal));

/*The ISR of USART Data Register Empty interrupt*/
void __vector_14 (void) __attribute__((signal));

/*The ISR of USART, Tx Complete interrupt*/
void __vector_15 (void) __attribute__((signal));

#endif /* UART_PRIV_H */ 
