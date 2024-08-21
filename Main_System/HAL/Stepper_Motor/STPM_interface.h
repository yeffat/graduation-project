#ifndef STEPPER_MOTOR_INTERFACE_H_
#define STEPPER_MOTOR_INTERFACE_H_
#include"..\..\LIB\STD_TYPES.h"

#define CW	1
#define CCW	0
/**
 * @brief Initializes the stepper motor by setting up the control pins.
 */
void StepperMotor_Init(void);

/**
 * @brief Rotates the stepper motor in the specified direction for a given number of steps.
 *
 * @param direction The direction to rotate (CW or CCW).
 * @param steps The number of steps to rotate.
 */
void StepperMotor_Rotate(uint8_t direction, uint16_t steps);

/**
 * @brief Moves the stepper motor to the specified slot number.
 *
 * @param slotNumber The target slot number to move to.
 */
void StepperMotor_MoveToSlot(uint8_t *currentSlot, uint8_t slotNumber);

#endif // STEPPER_MOTOR_INTERFACE_H_
