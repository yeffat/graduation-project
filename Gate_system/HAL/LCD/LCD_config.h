
/*Preprocessor Guard*/
#ifndef LCD_CONFIG_H 
#define LCD_CONFIG_H 

/*
Macro for setting the LCD mode
Range:
      LCD_U8_4BIT_MODE
      LCD_U8_8BIT_MODE
 */
#define LCD_U8_MODE                LCD_U8_8BIT_MODE

/*
Macro for setting the initialized commands for Function Set
Range:
      LCD_U8_FUN_SET_8BIT_1LINE
      LCD_U8_FUN_SET_8BIT_2LINES
      LCD_U8_FUN_SET_4BIT_1LINE
      LCD_U8_FUN_SET_4BIT_2LINES
 */
#define LCD_U8_INIT_FUNCTION_SET    		 LCD_U8_FUN_SET_8BIT_2LINES


/*
Macro for setting the initialized commands for Display on/off control
Range:
      LCD_U8_DISPLAY_OFF_CURSOR_OFF
      LCD_U8_DISPLAY_ON_CURSOR_ON
      LCD_U8_DISPLAY_ON_CURSOR_OFF
 */
#define LCD_U8_INIT_DISPLAY_CONTROL          LCD_U8_DISPLAY_ON_CURSOR_ON

/*Defining the pins of the LCD control pins*/
#define LCD_U8_RS_PIN			DIO_PIN0
#define LCD_U8_RW_PIN			DIO_PIN1
#define LCD_U8_E_PIN			DIO_PIN2

#define LCD_ControlPort			DIO_PORTB

/*Defining the pins of the LCD data pins*/
#define LCD_DataPort			DIO_PORTA

#define LCD_U8_D0_PIN			DIO_PIN0
#define LCD_U8_D1_PIN			DIO_PIN1
#define LCD_U8_D2_PIN			DIO_PIN2
#define LCD_U8_D3_PIN			DIO_PIN3
#define LCD_U8_D4_PIN			DIO_PIN4
#define LCD_U8_D5_PIN			DIO_PIN5
#define LCD_U8_D6_PIN			DIO_PIN6
#define LCD_U8_D7_PIN			DIO_PIN7

#endif /* LCD_CONFIG_H */ 
