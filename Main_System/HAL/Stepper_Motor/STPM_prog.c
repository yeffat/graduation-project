#include "../Stepper_Motor/STPM_config.h"
#include "../Stepper_Motor/STPM_interface.h"
#include "..\..\LIB\STD_TYPES.h"
#include "..\..\MCAL\DIO\DIO_int.h"
#include "..\..\LIB\DELAY\DELAY_interface.h"



/**
 * @brief Initializes the stepper motor by setting up the control pins.
 */
void StepperMotor_Init(void) {
    // Set the direction of the control pins to output
    DIO_U8SetPinDirection(STEPPER_PORT, STEP_PIN, DIO_OUTPUT);
    DIO_U8SetPinDirection(STEPPER_PORT, DIR_PIN, DIO_OUTPUT);
    DIO_U8SetPinDirection(STEPPER_PORT, ENABLE_PIN, DIO_OUTPUT);

    // Enable the stepper motor driver
    DIO_U8SetPinValue(STEPPER_PORT, ENABLE_PIN, DIO_LOW);
}

/**
 * @brief Rotates the stepper motor in the specified direction for a given number of steps.
 *
 * @param direction The direction to rotate (CW or CCW).
 * @param steps The number of steps to rotate.
 */
void StepperMotor_Rotate(uint8_t direction, uint16_t steps) {
    // Set the direction pin
    DIO_U8SetPinValue(STEPPER_PORT, DIR_PIN, direction);

    // Rotate the motor by the specified number of steps
    for (uint16_t i = 0; i < steps; i++) {
        // Generate a pulse on the step pin
        DIO_U8SetPinValue(STEPPER_PORT, STEP_PIN, DIO_HIGH);
        delay_milliseconds(1); // Adjust delay as per your stepper motor's requirements
        DIO_U8SetPinValue(STEPPER_PORT, STEP_PIN, DIO_LOW);
        delay_milliseconds(1);
    }
}

/**
 * @brief Moves the stepper motor to the specified slot number.
 *
 * @param slotNumber The target slot number to move to.
 */
void StepperMotor_MoveToSlot(uint8_t *currentSlot, uint8_t slotNumber) {
    // Ensure the slot number is within the valid range
    if (slotNumber < TOTAL_SLOTS) {
        // Calculate the number of steps needed to reach the target slot in both directions
        sint16_t stepsCW = (sint16_t)((slotNumber - *currentSlot) * STEPS_PER_SLOT);
        sint16_t stepsCCW = (sint16_t)((*currentSlot - slotNumber) * STEPS_PER_SLOT);

        // Ensure steps are positive for comparison
        if (stepsCW < 0) stepsCW += TOTAL_SLOTS * STEPS_PER_SLOT;
        if (stepsCCW < 0) stepsCCW += TOTAL_SLOTS * STEPS_PER_SLOT;

        // Choose the shortest path
        if (stepsCW <= stepsCCW) {
            StepperMotor_Rotate(CW, stepsCW);
        } else {
            StepperMotor_Rotate(CCW, stepsCCW);
        }

        // Update the current slot
        *currentSlot = slotNumber;
    }
}

