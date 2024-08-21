/*
Driver instructions:
Note: This driver with these instructions is tested on AVR ATmega32
In order to use this driver, you have to configure the timer driver first in a way
to fit with the required setting needed to interface this servo using PWM generated signal from the timer peripheral.
These timer configurations are as follows:
1- Enable Timer1.
#define  TMR_u8_TIMER1_INIT_STATE   TMR_u8_ENABLE
2- Select the mode of Timer1 to be in fastPWM mode.
#define  TMR_u8_TIMER1_MODE         TMR_u8_FASTPWM_ICR1
3- Set Timer1 Prescaler to be over 8 (knowing that the system clock is = 8MHZ)
#define  TMR_TIMER1_PRESCALER       TMR_FREQ_OVER_8
4- Specify which Timer1 pin you want to generate the PWM signal (TIMER1A(OC1A)/TIMER1B(OC1B))
EX: #define TMR_u8_TIMER1A_COPT_STATE     TMR_u8_ENABLE
5- Add 19999 value in ICR1 register so that the period of the generated PWM signal = 20ms
#define TMR_u16_ICR1_VAL            (u16)19999
6- Set the Compare Output Mode for timer1 to be on inverting mode (recommended)
#define TMR_u8_TIMER1_COPT_MODE     TMR_u8_SET_OCX
7- Call SERVO_u8SetServoAngle function and pass the required angle in it.
*/

/*Preprocessor Guard*/
#ifndef SERVO_INTERFACE_H
#define SERVO_INTERFACE_H

void SERVO_u8Init(void);
uint8_t SERVO_u8SetServoAngle (uint8_t Copy_U8Angle);

#endif /* SERVO_INTERFACE_H */

