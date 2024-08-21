#ifndef STEPPER_MOTOR_CFG_H_
#define STEPPER_MOTOR_CFG_H_

/* Configuration settings for the stepper motor control pins */
#define STEPPER_PORT DIO_PORTD
#define STEP_PIN     DIO_PIN5
#define DIR_PIN      DIO_PIN6
#define ENABLE_PIN   DIO_PIN7

/* Configuration settings for the stepper motor operation */
#define TOTAL_SLOTS  6
#define STEPS_PER_SLOT 1000

#endif // STEPPER_MOTOR_CFG_H_
