
#include "..\..\LIB\STD_TYPES.h"
#include "..\..\LIB\BIT_MATH.h"
#include "..\..\LIB\Delay\DELAY_interface.h"
#include "..\..\MCAL\DIO\DIO_int.h"
#include "LCD_interface.h" 
#include "LCD_priv.h" 
#include "LCD_config.h" 

/*
 * Description: Function to run some required commands at first as an initialization
 * Inputs: none
 * Output: void
 */
void LCD_VidInit (void)
{
	DIO_U8SetPortDirection(LCD_DataPort,DIO_PORT_OUT);
	DIO_U8SetPinDirection(LCD_ControlPort,LCD_U8_RS_PIN,DIO_OUTPUT);
	DIO_U8SetPinDirection(LCD_ControlPort,LCD_U8_RW_PIN,DIO_OUTPUT);
	DIO_U8SetPinDirection(LCD_ControlPort,LCD_U8_E_PIN,DIO_OUTPUT);


	delay_milliseconds (5);
	if (LCD_U8_MODE == LCD_U8_4BIT_MODE)
	{
		LCD_VidWriteCommand (0x33);
		LCD_VidWriteCommand (0x32);
	}
	LCD_VidWriteCommand (LCD_U8_INIT_FUNCTION_SET);
	delay_milliseconds (2);
	LCD_VidWriteCommand (LCD_U8_INIT_DISPLAY_CONTROL);
	delay_milliseconds (2);
	LCD_VidWriteCommand (LCD_U8_CLEAR);
	delay_milliseconds (2);
}

/*
 * Description: Function needed to send Data to the LCD
 * Inputs: The array of character needed to be displayed and it is required position in x & y axis
 * Output: Error state
 */
uint8_t LCD_U8WriteString (uint8_t *Copy_U8Data,uint8_t Copy_U8XPos,uint8_t Copy_U8YPos)
{
	/*Local Variable holding the error state*/
	uint8_t Local_U8Error = ERROR_OK;
	uint8_t Local_U8Address;
	if ((Copy_U8XPos >= LCD_U8_COLOMN_NO) || (Copy_U8YPos >= LCD_U8_ROW_NO) || (Copy_U8Data == NULL))
	{
		Local_U8Error = ERROR_NOK;
	}
	else
	{
		Local_U8Address = Copy_U8XPos+(Copy_U8YPos*LCD_U8_2ND_ROW);
		Local_U8Address |= LCD_U8_SET_DDRAM_ADDRESS;
		LCD_VidWriteCommand(Local_U8Address);

		while (*Copy_U8Data != '\0')
		{
			LCD_VidWriteData(*Copy_U8Data++);
			Local_U8Address++;

			/* End of line 1 */
			if (Local_U8Address == LCD_U8_LINE1_END)
			{
				/* Move the cursor to line 2 */
				Local_U8Address = LCD_U8_LINE2_START;
				LCD_VidWriteCommand(Local_U8Address);
			}

			/* End of line 2 */
			if (Local_U8Address == LCD_U8_LINE2_END)
			{
				/* Move the cursor to line 1 */
				Local_U8Address = LCD_U8_SET_DDRAM_ADDRESS;
				LCD_VidWriteCommand(Local_U8Address);
			}
		}
	}
	/*Function return*/
	return Local_U8Error;
}

/*
 * Description: Function save any word of special letters outside the asci scope
 * Inputs: pointer to the array of 8 patterns needed for each letter of this word and the word size
 * Output: Error state
 */
uint8_t LCD_U8SaveSpecialWord (uint8_t AU8_SymbolPattern[][8],uint8_t Copy_U8WordSize)
{
	/*Local Variable holding the error state*/
	uint8_t Local_U8Error = ERROR_OK;
	uint8_t Local_U8Index1,Local_U8Index2;
	if (Copy_U8WordSize > LCD_U8_MAX_SYMBOL)
	{
		Local_U8Error = ERROR_NOK;
	}
	LCD_VidWriteCommand(LCD_U8_SET_CGRAM_ADDRESS);

	for (Local_U8Index1 = UNSIGNED_MIN ; Local_U8Index1 < Copy_U8WordSize ; Local_U8Index1++)
	{
		for (Local_U8Index2 = UNSIGNED_MIN ; Local_U8Index2 < LCD_U8_CHARACTER_SIZE ; Local_U8Index2++)
		{
			LCD_VidWriteData(AU8_SymbolPattern[Local_U8Index1][Local_U8Index2]);
		}
	}

	/*Function return*/
	return Local_U8Error;
}

/*
 * Description: Function to write a special word on the LCD
 * Inputs: the symbol index in the CGRAM and its required position on the LCD according to x & y axis
 * Output: Error state
 */
uint8_t LCD_U8SwriteSpecialSymbol (uint8_t Copy_U8SymbolIndex,uint8_t Copy_U8XPos,uint8_t Copy_U8YPos)
{
	/*Local Variable holding the error state*/
	uint8_t Local_U8Error = ERROR_OK;
	uint8_t Local_U8Address;
	if ((Copy_U8XPos >= LCD_U8_COLOMN_NO) || (Copy_U8YPos >= LCD_U8_ROW_NO))
	{
		Local_U8Error = ERROR_NOK;
	}
	else
	{
		Local_U8Address = Copy_U8XPos+(Copy_U8YPos*LCD_U8_2ND_ROW);
		Local_U8Address |= LCD_U8_SET_DDRAM_ADDRESS;
		LCD_VidWriteCommand(Local_U8Address);
		LCD_VidWriteData(Copy_U8SymbolIndex);
	}
	/*Function return*/
	return Local_U8Error;
}

/*=====================================Common Commands===================*/
/*
 * Description: Function to clear the LCD from any previous displayed data on it.
 * Inputs: none
 * Output: void
 */
void LCD_VidCLEAR(void)
{
	LCD_VidWriteCommand (LCD_U8_CLEAR);
}

/*
 * Description: Function to shift the display to right
 * Inputs: none
 * Output: void
 */
void LCD_VidShiftRight(void)
{
	LCD_VidWriteCommand (LCD_U8_SHIFT_RIGHT);
}

/*
 * Description: Function to shift the display to lift
 * Inputs: none
 * Output: void
 */
void LCD_VidShiftLeft(void)
{
	LCD_VidWriteCommand (LCD_U8_SHIFT_LEFT);
}

/*====================Static Functions===============================*/
/*
 * Description: Function needed to send Data to the LCD
 * Inputs: The data needed to be sent Data as a string or a single character
 * Output: Error state
 */
static void LCD_VidWriteData (uint8_t Copy_U8Data)
{
	DIO_U8SetPinValue(DIO_PORTB,LCD_U8_RS_PIN,DIO_HIGH);
	U8Write(Copy_U8Data);
	return;
}


/*
 * Description: Function needed to send Command to the LCD
 * Inputs: The command needed to be sent
 * Output: Error state
 */
static void LCD_VidWriteCommand (uint8_t Copy_U8Command)
{
	DIO_U8SetPinValue (LCD_ControlPort,LCD_U8_RS_PIN,DIO_LOW);
	U8Write (Copy_U8Command);
}

/*
 * Description: Private function needed to send Data/Command to the LCD
 * Inputs: The data or the command needed to be sent
 * Output: Error state
 */
static uint8_t U8Write (uint8_t Copy_U8Data)
{
	/*Local Variable holding the error state*/
	uint8_t Local_U8Error = ERROR_OK;

	Local_U8Error = DIO_U8SetPinValue (LCD_ControlPort,LCD_U8_E_PIN,DIO_LOW);
	Local_U8Error = DIO_U8SetPinValue (LCD_ControlPort,LCD_U8_RW_PIN,DIO_LOW);

	if (LCD_U8_MODE == LCD_U8_8BIT_MODE)
	{
		Local_U8Error = DIO_U8SetPortValue (LCD_DataPort , Copy_U8Data);

		Local_U8Error = DIO_U8SetPinValue (LCD_ControlPort,LCD_U8_E_PIN,DIO_HIGH);
		delay_milliseconds (1);
		Local_U8Error = DIO_U8SetPinValue (LCD_ControlPort,LCD_U8_E_PIN,DIO_LOW);
		delay_milliseconds (5);
	}



	if (LCD_U8_MODE == LCD_U8_4BIT_MODE)
	{
		Local_U8Error = DIO_U8SetPinValue (LCD_ControlPort,LCD_U8_E_PIN,DIO_LOW);

		Local_U8Error = DIO_U8SetPinValue (LCD_DataPort,LCD_U8_D4_PIN,GET_BIT(Copy_U8Data,0));
		Local_U8Error = DIO_U8SetPinValue (LCD_DataPort,LCD_U8_D5_PIN,GET_BIT(Copy_U8Data,1));
		Local_U8Error = DIO_U8SetPinValue (LCD_DataPort,LCD_U8_D6_PIN,GET_BIT(Copy_U8Data,2));
		Local_U8Error = DIO_U8SetPinValue (LCD_DataPort,LCD_U8_D7_PIN,GET_BIT(Copy_U8Data,3));

		Local_U8Error = DIO_U8SetPinValue (LCD_ControlPort,LCD_U8_E_PIN,DIO_HIGH);
		delay_milliseconds (1);
		Local_U8Error = DIO_U8SetPinValue (LCD_ControlPort,LCD_U8_E_PIN,DIO_LOW);
		delay_milliseconds (5);
	}
	/*Function return*/
	return Local_U8Error;
}
extern void LCD_vidDisplayINT(uint16_t num)
{

	uint32_t y=1;
	if (num==0)
		LCD_VidWriteData('0');
	if(num<0){
		LCD_VidWriteData('-');
		num=num*-1;
	}
	while(num !=0){
		y=((y*10)+(num%10));
		num=num/10;
	}
    while(y!=1){
    	LCD_VidWriteData((y%10)+'0');
    	y=y/10;
    }
}
