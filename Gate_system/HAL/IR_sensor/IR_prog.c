/*
 * IR_prog.c
 *
 *  Created on: Jul 5, 2024
 *      Author: ahmed
 */
#include "../../LIB/STD_TYPES.h"
#include "..\..\MCAL\DIO\DIO_int.h"
#include "..\..\MCAL\EX_INT\EX_INT_int.h"
#include "IR_config.h"
#include "IR_interface.h"

/**
 * @brief Initializes the IR sensor module and sets up the external interrupt.
 */
void IR_Init(void) {
    // Set the IR sensor pin as input
    DIO_U8SetPinDirection(IR_PORT, IR_PIN, DIO_INPUT);
    DIO_U8SetPinValue(IR_PORT, IR_PIN, DIO_HIGH);
    // Initialize the external interrupt
    EXTI0_VoidInit();
    EXTI0_voidSetSenseControl(FAILING_EDGE);
    EXTI0_voidEnable();

}

/**
 * @brief Sets a callback function to be called when the IR sensor detects a car parked correctly.
 *
 * @param callback The callback function to set.
 */
void IR_SetCallback(void (*callback)(void)) {
    EXTI0_voidSetCallBack(callback);
}


