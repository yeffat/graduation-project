
#ifndef HAL_KEYPAD_KEYPAD_H_
#define HAL_KEYPAD_KEYPAD_H_
#include "../../LIB/STD_TYPES.h"


#define KEYPAD_GROUP DIO_PORTC
#define ROWS 4
#define COLS 3

void keyPad_init();
uint8_t KeyPad_get_pressed_key();

#endif /* HAL_KEYPAD_KEYPAD_H_ */
