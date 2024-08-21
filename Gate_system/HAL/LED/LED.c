/*
 * LED.c
 *
 *  Created on: Jul 5, 2024
 *      Author: ahmed
 */

#include "led.h"

#include "..\..\MCAL\DIO\DIO_int.h"

void LED_Init() {
    DIO_U8SetPinDirection(LED_GATE_CLOSED, DIO_OUTPUT);
    DIO_U8SetPinDirection(LED_GATE_OPEN, DIO_OUTPUT);

}

void LED_On(uint8_t port, uint8_t pin) {
    DIO_U8SetPinValue(port, pin, DIO_HIGH);
}

void LED_Off(uint8_t port, uint8_t pin) {
    DIO_U8SetPinValue(port, pin, DIO_LOW);
}

void LED_Toggle(uint8_t port, uint8_t pin) {
    DIO_U8TogglePinValue(port, pin);
}

