
/*Preprocessor Guard*/
#ifndef TMR_INTERFACE_H
#define TMR_INTERFACE_H

/*Macro for defining the 3 availabe timers in AVR ATmega32*/
#define TMR_u8_TIMER1      (uint8_t)1

/*
 * Description: Function to set the initialized state and prescaler for each timer (0,1,2)
 * Inputs: none
 * Output: void
 */
void TMR_vInit (void);

/*
 * Description: Function to set the duty cycle of the PWM signal generated from Timer1,Pins OC1A or/and OC1B
 * (used mainly in servo interfacing)
 * Inputs: The desired timer compare value
 * Output: void
 */
void TMR_u8SetPWM (uint16_t Copy_u16ReqCompValue);


#endif /* TMR_INTERFACE_H */
