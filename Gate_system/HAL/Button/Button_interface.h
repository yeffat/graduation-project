/*
 * Button_interface.h
 *
 *  Created on: Jul 5, 2024
 *      Author: ahmed
 */

#ifndef HAL_Button_HW_201_Button_INTERFACE_H_
#define HAL_Button_HW_201_Button_INTERFACE_H_

#ifndef Button_INTERFACE_H_
#define Button_INTERFACE_H_

/**
 * @brief Initializes the Button sensor module and sets up the external interrupt.
 */
void Button_Init(void);

/**
 * @brief Sets a callback function to be called when the Button sensor detects a car parked correctly.
 *
 * @param callback The callback function to set.
 */
void Button_SetCallback(void (*callback)(void));

#endif // Button_INTERFACE_H_


#endif /* HAL_Button_HW_201_Button_INTERFACE_H_ */
