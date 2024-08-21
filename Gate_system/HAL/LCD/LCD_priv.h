/*Preprocessor Guard*/
#ifndef LCD_PRIV_H 
#define LCD_PRIV_H 

/*Private macros for the probable LCD mode*/
#define  LCD_U8_4BIT_MODE    (uint8_t)0
#define  LCD_U8_8BIT_MODE    (uint8_t)1

/*Macro for the number of rows and colomn of the LCD */
#define LCD_U8_ROW_NO       (uint8_t)2
#define LCD_U8_COLOMN_NO    (uint8_t)16

/*Macros for whole needed commands for the LCD */
#define LCD_U8_FUN_SET_8BIT_1LINE        (uint8_t)0x30
#define LCD_U8_FUN_SET_8BIT_2LINES       (uint8_t)0x38
#define LCD_U8_FUN_SET_4BIT_1LINE	 	 (uint8_t)0x20
#define LCD_U8_FUN_SET_4BIT_2LINES	  	 (uint8_t)0x28
#define LCD_U8_ENTRY_MODE				 (uint8_t)0x06
#define LCD_U8_CLEAR                     (uint8_t)0x01
#define LCD_U8_DISPLAY_OFF_CURSOR_OFF	 (uint8_t)0x08
#define LCD_U8_DISPLAY_ON_CURSOR_ON 	 (uint8_t)0x0E
#define LCD_U8_DISPLAY_ON_CURSOR_OFF	 (uint8_t)0x0C
#define LCD_U8_SHIFT_RIGHT				 (uint8_t)0x1C
#define LCD_U8_SHIFT_LEFT				 (uint8_t)0x18
#define LCD_U8_RETURN_HOME               (uint8_t)0x02
#define LCD_U8_SET_CGRAM_ADDRESS         (uint8_t)0x40
#define LCD_U8_SET_DDRAM_ADDRESS         (uint8_t)0x80

/*Macro to set the size of the single character in the LCD */
#define LCD_U8_CHARACTER_SIZE    (uint8_t)8
#define LCD_U8_MAX_SYMBOL        (uint8_t)8

/*Macro of the address of the 1st character in the second row*/
#define LCD_U8_2ND_ROW            (uint8_t)0x40
#define LCD_U8_LINE1_END          (uint8_t)0x90
#define LCD_U8_LINE2_START        (uint8_t)0xC0
#define LCD_U8_LINE2_END          (uint8_t)0xD0


/*
 * Description: Private function needed to send Data/Command to the LCD
 * Inputs: The data or the command needed to be sent
 * Output: Error state
 */
static uint8_t U8Write (uint8_t Copy_U8Data);

/*
 * Description: Function needed to send Command to the LCD
 * Inputs: The command needed to be sent
 * Output: Error state
 */
static void LCD_VidWriteCommand (uint8_t Copy_U8Command);
/*
 * Description: Function needed to send Data to the LCD
 * Inputs: The data needed to be sent Data as a string or a single character
 * Output: Error state
 */
static void LCD_VidWriteData (uint8_t Copy_U8Data);

#endif /* LCD_PRIV_H */ 
