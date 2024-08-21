#include "..\..\LIB\STD_TYPES.h"
#include "..\..\LIB\BIT_MATH.h"

#include "DIO_int.h"
#include "DIO_reg.h"

/*Function for the pin direction*/
uint8_t DIO_U8SetPinDirection(uint8_t Copy_U8Port , uint8_t Copy_U8Pin, uint8_t Copy_U8Direction ){
	uint8_t err_status = E_OK;

	switch (Copy_U8Direction)
	{
		case DIO_INPUT:

			switch (Copy_U8Port)
			{
				case DIO_PORTA:
					CLR_BIT (DDRA, Copy_U8Pin);
					break;
				case DIO_PORTB:
					CLR_BIT (DDRB, Copy_U8Pin);
					break;
				case DIO_PORTC:
					CLR_BIT (DDRC, Copy_U8Pin);
					break;
				case DIO_PORTD:
					CLR_BIT (DDRD, Copy_U8Pin);
					break;
				default : err_status = E_NOK;
			}
			break;

		case DIO_OUTPUT:
			switch (Copy_U8Port)
			{
					case DIO_PORTA:
						SET_BIT (DDRA, Copy_U8Pin);
						break;
					case DIO_PORTB:
						SET_BIT (DDRB, Copy_U8Pin);
						break;
					case DIO_PORTC:
						SET_BIT (DDRC, Copy_U8Pin);
						break;
					case DIO_PORTD:
						SET_BIT (DDRD, Copy_U8Pin);
						break;
					default : err_status = E_NOK;
			}
			break;
		default : err_status = E_NOK;
	}
	return err_status;
}

/*Function for value*/
uint8_t DIO_U8SetPinValue(uint8_t Copy_U8Port , uint8_t Copy_U8Pin, uint8_t Copy_U8Value ){
	uint8_t err_status = E_OK;
	switch (Copy_U8Value)
		{
			case DIO_LOW:

				switch (Copy_U8Port)
				{
					case DIO_PORTA:
						CLR_BIT (PORTA, Copy_U8Pin);
						break;
					case DIO_PORTB:
						CLR_BIT (PORTB, Copy_U8Pin);
						break;
					case DIO_PORTC:
						CLR_BIT (PORTC, Copy_U8Pin);
						break;
					case DIO_PORTD:
						CLR_BIT (PORTD, Copy_U8Pin);
						break;
					default : err_status = E_NOK;
				}
				break;

			case DIO_HIGH:
				switch (Copy_U8Port)
				{
						case DIO_PORTA:
							SET_BIT (PORTA, Copy_U8Pin);
							break;
						case DIO_PORTB:
							SET_BIT (PORTB, Copy_U8Pin);
							break;
						case DIO_PORTC:
							SET_BIT (PORTC, Copy_U8Pin);
							break;
						case DIO_PORTD:
							SET_BIT (PORTD, Copy_U8Pin);
							break;
						default :err_status = E_NOK;
				}
				break;
			default : err_status = E_NOK;

		}
	return err_status;

}


/*Function to set port direction*/
uint8_t DIO_U8SetPortDirection(uint8_t Copy_U8Port, uint8_t Copy_U8Direction)
{
	uint8_t err_status = E_OK;
	switch(Copy_U8Port)
	{
		case DIO_PORTA :
			DDRA = Copy_U8Direction ;
			break;

		case DIO_PORTB :
			DDRB = Copy_U8Direction ;
			break;

		case DIO_PORTC :
			DDRC = Copy_U8Direction ;
			break;

		case DIO_PORTD :
			DDRD = Copy_U8Direction ;
			break;
		default : err_status = E_NOK;
	}
	return err_status;
}

/*Function to set port value*/
uint8_t DIO_U8SetPortValue(uint8_t Copy_U8Port, uint8_t Copy_U8Value)
{
	uint8_t err_status = E_OK;
	switch(Copy_U8Port)
	{
		case DIO_PORTA :
			PORTA = Copy_U8Value ;
			break;

		case DIO_PORTB :
			PORTB = Copy_U8Value ;
			break;

		case DIO_PORTC :
			PORTC = Copy_U8Value ;
			break;

		case DIO_PORTD :
			PORTD = Copy_U8Value ;
			break;
		default : err_status = E_NOK;
	}
	return err_status;
}
//Function to toggle the bin
uint8_t DIO_U8TogglePinValue(uint8_t Copy_U8Port, uint8_t Copy_U8Pin)
{
	uint8_t err_status = E_OK;
	switch(Copy_U8Port)
		{
			case DIO_PORTA :
				TOGGLE_BIT(PORTA,Copy_U8Pin);
				break;

			case DIO_PORTB :
				TOGGLE_BIT(PORTB,Copy_U8Pin);
				break;

			case DIO_PORTC :
				TOGGLE_BIT(PORTC,Copy_U8Pin);
				break;

			case DIO_PORTD :
				TOGGLE_BIT(PORTD,Copy_U8Pin);
				break;
			default : err_status = E_NOK;
		}
	return err_status;
}

uint8_t DIO_U8GetPinValue( uint8_t Copy_U8Port , uint8_t Copy_U8Pin, uint8_t *Copy_U8Value)
{
	uint8_t err_status = E_OK;

	switch(Copy_U8Port)
	{
		case DIO_PORTA :
			*Copy_U8Value =  GET_BIT( PINA , Copy_U8Pin );
			break;
		case DIO_PORTB :
			*Copy_U8Value = GET_BIT( PINB , Copy_U8Pin );
			break;
		case DIO_PORTC :
			*Copy_U8Value = GET_BIT( PINC , Copy_U8Pin );
			break;
		case DIO_PORTD :
			*Copy_U8Value = GET_BIT( PIND , Copy_U8Pin );
			break;
		default : err_status = E_NOK;

	}
	return err_status;
}
//uint8_t DIO_U8SetPinInputMode(uint8_t Copy_U8Port , uint8_t Copy_U8Pin, uint8_t Copy_U8InputMode){
//	uint8_t err_status = E_OK;
//	if (Copy_U8InputMode == DIO_PULL_UP){
//		switch(Copy_U8Port)
//		{
//			case DIO_PORTA :
//				SET_BIT(PORTA,Copy_U8Pin);
//				break;
//
//			case DIO_PORTB :
//				SET_BIT(PORTB,Copy_U8Pin);
//				break;
//
//			case DIO_PORTC :
//				SET_BIT(PORTC,Copy_U8Pin);
//				break;
//
//			case DIO_PORTD :
//				SET_BIT(PORTD,Copy_U8Pin);
//				break;
//			default : err_status = E_NOK;
//		}
//		return err_status;
//
//	}
//	else if(Copy_U8InputMode == DIO_FLOATING ){
//		switch(Copy_U8Port)
//		{
//			case DIO_PORTA :
//				CLR_BIT(PORTA,Copy_U8Pin);
//				break;
//
//			case DIO_PORTB :
//				CLR_BIT(PORTB,Copy_U8Pin);
//				break;
//
//			case DIO_PORTC :
//				CLR_BIT(PORTC,Copy_U8Pin);
//				break;
//
//			case DIO_PORTD :
//				CLR_BIT(PORTD,Copy_U8Pin);
//				break;
//			default : err_status = E_NOK;
//
//		}
//		return err_status;
//	}
//	err_status = E_NOK;
//	return err_status;
//}
