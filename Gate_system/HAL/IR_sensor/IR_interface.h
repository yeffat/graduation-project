/*
 * IR_interface.h
 *
 *  Created on: Jul 5, 2024
 *      Author: ahmed
 */

#ifndef HAL_IR_HW_201_IR_INTERFACE_H_
#define HAL_IR_HW_201_IR_INTERFACE_H_

#ifndef IR_INTERFACE_H_
#define IR_INTERFACE_H_

/**
 * @brief Initializes the IR sensor module and sets up the external interrupt.
 */
void IR_Init(void);

/**
 * @brief Sets a callback function to be called when the IR sensor detects a car parked correctly.
 *
 * @param callback The callback function to set.
 */
void IR_SetCallback(void (*callback)(void));

#endif // IR_INTERFACE_H_


#endif /* HAL_IR_HW_201_IR_INTERFACE_H_ */
