
/*Preprocessor Guard*/
#ifndef TMR_PRIV_H 
#define TMR_PRIV_H 

/*Private macro for the number of the availabe timers in AVR Atmega32*/
#define TMR_u8_NO_OF_TIMERS   	 	     (uint8_t)3

#define TMR_u8_MAXVAL_TIMER02_REG         256U
#define TMR_u32_MAXVAL_TIMER1_REG         65536U

/*Private macros for the initial state of the timers*/
#define TMR_u8_DISABLE        		     0
#define TMR_u8_ENABLE          		     1

/*Private macros for the available mode for the timer peripheral in AVR ATmega32*/
#define  TMR_u8_NORMAL                   (uint8_t)0
#define  TMR_u8_PWM_PHASE_CORRECT   	 (uint8_t)1
#define  TMR_u8_CTC                  	 (uint8_t)2
#define  TMR_u8_FASTPWM_8BIT             (uint8_t)3
#define  TMR_u8_FASTPWM_9BIT             (uint8_t)4
#define  TMR_u8_FASTPWM_10BIT            (uint8_t)5
#define  TMR_u8_FASTPWM_ICR1  			 6
#define  TMR_u8_FASTPWM_OCRA1 			 (uint8_t)7

/*Private macros for the available prescalers can be assigned for the timer peripheral*/
#define TMR_NO_PRESCALER    		0U
#define TMR_FREQ_OVER_8    		    1U
#define TMR_FREQ_OVER_32            2U
#define TMR_FREQ_OVER_64            3U
#define TMR_FREQ_OVER_128           4U
#define TMR_FREQ_OVER_256           5U
#define TMR_FREQ_OVER_1024          6U

/*Macros for enabling or disabling the timer interrupt*/
#define TMR_u8_DIS_INT    		 (uint8_t)0
#define TMR_u8_EN_INT      		 (uint8_t)1

/*Macros for available output mode on compare match timer */
#define TMR_u8_OCX_PIN_DISCOUNNECTED    (uint8_t)0
#define TMR_u8_TOGGLE_OCX				(uint8_t)1
#define TMR_u8_CLEAR_OCX				(uint8_t)2
#define TMR_u8_SET_OCX			    	(uint8_t)3

/*Macros for the possible sense level for the input capture pin D6*/
#define TMR_u8_RISING_EDGE                   (uint8_t)0
#define TMR_u8_FALLING_EDGE                  (uint8_t)1


#define TMR_TCCR1A	(* (volatile uint8_t *) (0x4F))
#define TMR_TCCR1B	(* (volatile uint8_t *) (0x4E))
#define TMR_TCNT1H	(* (volatile uint8_t *) (0x4D))
#define TMR_TCNT1L     (* (volatile uint8_t *) (0x4C))
#define TMR_TCNT1     (* (volatile uint16_t *) (0x4C))
#define TMR_OCR1AL    (* (volatile uint8_t *) (0x4A))
#define TMR_OCR1AH    (* (volatile uint8_t *) (0x4B))
#define TMR_OCRA1      (* (volatile uint16_t *) (0x4A))
#define TMR_OCR1BL     (* (volatile uint8_t *) (0x48))
#define TMR_OCR1BH    (* (volatile uint8_t *) (0x49))
#define TMR_OCRB1      (* (volatile uint16_t *) (0x48))
#define TMR_ICR1H     (* (volatile uint8_t *) (0x47))
#define TMR_ICR1L     (* (volatile uint8_t *) (0x46))
#define TMR_ICR1      (* (volatile uint16_t *) (0x46))
#define TMR_TIFR    (* (volatile uint8_t *) (0x58))

#define TMR_TIMSK (* (volatile uint8_t *) (0x59))

///*************************************************************************************/
///*Static Functions to set the desired time needed in case of normal mode or CTC mode */
///*************************************************************************************/
//void TMR_vSetTIMER0OVFTime (float32_t Copy_F32TimerCtr);
//



#endif /* TMR_PRIV_H */ 
