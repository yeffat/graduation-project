
/*Preprocessor Guard*/
#ifndef LCD_INTERFACE_H 
#define LCD_INTERFACE_H 

/*
 * Description: Function to run some required commands at first as an initialization
 * Inputs: none
 * Output: void
 */
void LCD_VidInit(void);

/*
 * Description: Function to clear the LCD from any previous displayed data on it.
 * Inputs: none
 * Output: void
 */
void LCD_VidCLEAR(void);

/*
 * Description:  Function to shift the display to lift.
 * Inputs: none
 * Output: void
 */
void LCD_VidShiftLeft(void);


/*
 * Description: Function to shift the display to right.
 * Inputs: none
 * Output: void
 */
void LCD_VidShiftRight(void);

/*
 * Description: Function needed to send Data to the LCD
 * Inputs: The array of character needed to be displayed and it is required position on the LCD according to x & y axis
 * Output: Error state
 */
uint8_t LCD_U8WriteString (uint8_t *Copy_U8Data,uint8_t Copy_U8XPos,uint8_t Copy_U8YPos);

/*
 * Description: Function save any word of special letters outside the asci scope
 * Inputs: pointer to the array of 8 patterns needed for each letter of this word and the word size
 * Output: Error state
 */
uint8_t LCD_U8SaveSpecialWord (uint8_t AU8_SymbolPattern[][8],uint8_t Copy_U8WordSize);

/*
 * Description: Function to write a special word on the LCD
 * Inputs: the symbol index in the CGRAM and its required position on the LCD according to x & y axis
 * Output: Error state
 */
uint8_t LCD_U8SwriteSpecialSymbol (uint8_t Copy_U8SymbolIndex,uint8_t Copy_U8XPos,uint8_t Copy_U8YPos);
extern void LCD_vidDisplayINT(uint16_t num);
#endif /* LCD_INTERFACE_H */ 
