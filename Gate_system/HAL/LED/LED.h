/*
 * LED.h
 *
 *  Created on: Jul 5, 2024
 *      Author: ahmed
 */

#ifndef LED_H_
#define LED_H_

#include "..\..\LIB\STD_TYPES.h"
#include "..\..\MCAL\DIO\DIO_int.h"
// LED States
#define LED_ON  1
#define LED_OFF 0

// Define LEDs with their corresponding ports and pins
#define LED_GATE_CLOSED			DIO_PORTD, DIO_PIN1
#define LED_GATE_OPEN			DIO_PORTD, DIO_PIN0

// Function Prototypes
void LED_Init();
void LED_On(uint8_t port, uint8_t pin);
void LED_Off(uint8_t port, uint8_t pin);
void LED_Toggle(uint8_t port, uint8_t pin);

#endif // LED_H_

