#include "KEYPAD.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/DELAY/DELAY_interface.h"

#define KEYPAD_GROUP DIO_PORTC
#define ROWS 4
#define COLS 3

uint8_t keypad_arr[ROWS][COLS] = {
    { 1	, 2,  3	,},
    { 4	, 5,  6	,},
    { 7	, 8,  9	,},
    {'*', 0, '#',}
};

void keyPad_init() {
	 // Set PC3, PC2, PC1, PC0 (rows) as outputs and PC6, PC5, PC4 (columns) as inputs
	    DIO_U8SetPinDirection(KEYPAD_GROUP, 0, DIO_OUTPUT);
	    DIO_U8SetPinDirection(KEYPAD_GROUP, 1, DIO_OUTPUT);
	    DIO_U8SetPinDirection(KEYPAD_GROUP, 2, DIO_OUTPUT);
	    DIO_U8SetPinDirection(KEYPAD_GROUP, 3, DIO_OUTPUT);
	    DIO_U8SetPinDirection(KEYPAD_GROUP, 4, DIO_INPUT);
	    DIO_U8SetPinDirection(KEYPAD_GROUP, 5, DIO_INPUT);
	    DIO_U8SetPinDirection(KEYPAD_GROUP, 6, DIO_INPUT);

	    // Enable pull-up resistors on column pins and set row pins high
	    DIO_U8SetPinValue(KEYPAD_GROUP, 3, DIO_HIGH);
	    DIO_U8SetPinValue(KEYPAD_GROUP, 2, DIO_HIGH);
	    DIO_U8SetPinValue(KEYPAD_GROUP, 1, DIO_HIGH);
	    DIO_U8SetPinValue(KEYPAD_GROUP, 0, DIO_HIGH);
	    DIO_U8SetPinValue(KEYPAD_GROUP, 6, DIO_HIGH);
	    DIO_U8SetPinValue(KEYPAD_GROUP, 5, DIO_HIGH);
	    DIO_U8SetPinValue(KEYPAD_GROUP, 4, DIO_HIGH);
}

uint8_t KeyPad_get_pressed_key() {
    uint8_t cols_num = 0;
    uint8_t rows_num = 0;
    uint8_t retNum = 0xFF;

    for (rows_num = 0; rows_num < ROWS; rows_num++) {
        DIO_U8SetPinValue(KEYPAD_GROUP, rows_num, DIO_LOW);
        for (cols_num = 4; cols_num < 7; cols_num++) {
            uint8_t pin_value;
            if (DIO_U8GetPinValue(KEYPAD_GROUP, cols_num, &pin_value) == E_OK && pin_value == 0) {
                retNum = keypad_arr[rows_num][cols_num - 4];
                delay_milliseconds(10);
                DIO_U8SetPinValue(KEYPAD_GROUP, rows_num, DIO_HIGH);
                return retNum;
            }
            delay_milliseconds(10);
        }
        DIO_U8SetPinValue(KEYPAD_GROUP, rows_num, DIO_HIGH);
    }
    return retNum;
}
