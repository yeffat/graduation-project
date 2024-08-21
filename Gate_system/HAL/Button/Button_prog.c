/*
 * Button_prog.c
 *
 *  Created on: Jul 5, 2024
 *      Author: ahmed
 */
#include "../../LIB/STD_TYPES.h"
#include "..\..\MCAL\DIO\DIO_int.h"
#include "..\..\MCAL\EX_INT\EX_INT_int.h"
#include "Button_config.h"
#include "Button_interface.h"

/**
 * @brief Initializes the Button sensor module and sets up the external interrupt.
 */
void Button_Init(void) {
    // Set the Button sensor pin as input
    DIO_U8SetPinDirection(Button_PORT, Button_PIN, DIO_INPUT);
    // Initialize the external interrupt
    EXTI1_VoidInit();
    EXTI1_voidSetSenseControl(FAILING_EDGE);
    EXTI1_voidEnable();

}

/**
 * @brief Sets a callback function to be called when the Button sensor detects a car parked correctly.
 *
 * @param callback The callback function to set.
 */
void Button_SetCallback(void (*callback)(void)) {
    EXTI1_voidSetCallBack(callback);
}


