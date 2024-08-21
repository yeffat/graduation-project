#ifndef DIO_H_
#define DIO_H_
#include "..\..\LIB\STD_TYPES.h"
#define DIO_INPUT 	(uint8_t)0
#define DIO_OUTPUT 	(uint8_t)1

#define DIO_FLOATING  (uint8_t)0
#define DIO_PULL_UP   (uint8_t)1

#define DIO_PORTA	(uint8_t)0
#define DIO_PORTB	(uint8_t)1
#define DIO_PORTC	(uint8_t)2
#define DIO_PORTD	(uint8_t)3

#define DIO_PIN0	(uint8_t)0
#define DIO_PIN1	(uint8_t)1
#define DIO_PIN2	(uint8_t)2
#define DIO_PIN3	(uint8_t)3
#define DIO_PIN4	(uint8_t)4
#define DIO_PIN5	(uint8_t)5
#define DIO_PIN6	(uint8_t)6
#define DIO_PIN7	(uint8_t)7

#define DIO_LOW 	(uint8_t)0
#define DIO_HIGH 	(uint8_t)1

#define DIO_PORT_IN		(uint8_t)0x00
#define DIO_PORT_OUT	(uint8_t)0xff
#define DIO_PORT_LOW 	(uint8_t)0x00
#define DIO_PORT_HIGH 	(uint8_t)0xff

#define E_OK	(uint8_t)0
#define E_NOK	(uint8_t)1

uint8_t DIO_U8SetPinDirection(uint8_t Copy_U8Port , uint8_t Copy_U8Pin, uint8_t Copy_U8Direction );

uint8_t DIO_U8SetPinValue(uint8_t Copy_U8Port , uint8_t Copy_U8Pin, uint8_t Copy_U8Value );

uint8_t DIO_U8SetPortDirection(uint8_t Copy_U8Port, uint8_t Copy_U8Direction);

uint8_t DIO_U8SetPortValue(uint8_t Copy_U8Port, uint8_t Copy_U8Value);

uint8_t DIO_U8TogglePinValue(uint8_t Copy_U8Port, uint8_t Copy_U8Pin);

uint8_t DIO_U8GetPinValue( uint8_t Copy_U8Port , uint8_t Copy_U8Pin, uint8_t * Copy_U8Value);
//uint8_t DIO_U8GetPortValue ( uint8_t Copy_U8Port , uint8_t * Copy_U8Value);
//uint8_t DIO_U8SetPinInputMode(uint8_t Copy_U8Port , uint8_t Copy_U8Pin, uint8_t Copy_U8InputMode);
#endif
