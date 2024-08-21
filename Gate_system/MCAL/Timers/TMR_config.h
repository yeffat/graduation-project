/*Preprocessor Guard*/
#ifndef TMR_CONFIG_H 
#define TMR_CONFIG_H 

/*====================================================================*/
/*        General Configurations for Timer0,Timer1,Timer2 	          */
/*====================================================================*/
/*
Macros for the initial state of each timer (0,1,2)
Range:   TMR_u8_DISABLE
	   	 TMR_u8_ENABLE
*/
#define  TMR_u8_TIMER1_INIT_STATE     TMR_u8_ENABLE

/*
Macros for the mode of each timer (0,1,2)
Range:   TMR_u8_NORMAL
	   	 TMR_u8_PWM_PHASE_CORRECT
	   	 TMR_u8_CTC
		 TMR_u8_FASTPWM_8BIT
		 TMR_u8_FASTPWM_9BIT  (for Timer1 only)
		 TMR_u8_FASTPWM_10BIT (for Timer1 only)
		 TMR_u8_FASTPWM_ICR1  (for Timer1 only)
		 TMR_u8_FASTPWM_OCRA1 (for Timer1 only)
*/
#define  TMR_u8_TIMER1_MODE   TMR_u8_FASTPWM_ICR1


/*
Macros for the prescaler of each timer (0,1,2)
Range:   TMR_NO_PRESCALER
	   	 TMR_FREQ_OVER_8
	   	 TMR_FREQ_OVER_32
	   	 TMR_FREQ_OVER_64
	   	 TMR_FREQ_OVER_128
		 TMR_FREQ_OVER_256
		 TMR_FREQ_OVER_1024
*/
#define  TMR_TIMER1_PRESCALER       TMR_FREQ_OVER_8


/*====================================================================*/
/*                Configurations for Timer1A/Timer1B                  */
/*====================================================================*/
/*
Macros to specify on which pin related to Timer1A/Timer1B you will apply compare output mode (OC1A/OC1B)
Range:   TMR_u8_DISABLE
	   	 TMR_u8_ENABLE
*/
#define TMR_u8_TIMER1A_COPT_STATE     TMR_u8_DISABLE
#define TMR_u8_TIMER1B_COPT_STATE     TMR_u8_ENABLE

/*
Macro to specify the top value of the timer upon which the period of the generated PWM signal
will be determined (in case of TMR_u8_FASTPWM_ICR1 mode)
*/
#define TMR_u16_ICR1_VAL              (uint16_t)19999
/*====================================================================*/
/*                  Interrupts Configurations                         */
/*====================================================================*/
/*
Macros to set the Compare Output Mode for each timer (0,1,2)
Range:   TMR_u8_TOGGLE_OCX
	   	 TMR_u8_CLEAR_OCX (non-inverting mode in Fast PWM)
	   	 TMR_u8_SET_OCX   (inverting mode in Fast PWM)
*/
#define TMR_u8_TIMER0_COPT_MODE    TMR_u8_OCX_PIN_DISCOUNNECTED
#define TMR_u8_TIMER1_COPT_MODE    TMR_u8_SET_OCX
#define TMR_u8_TIMER2_COPT_MODE    TMR_u8_OCX_PIN_DISCOUNNECTED

/*
Macros to determine the state of the Input Capture Interrupt
Range:   TMR_u8_DIS_INT
	   	 TMR_u8_EN_INT
*/
#define TMR_u8_ICP_INT       	TMR_u8_DIS_INT


#if (TMR_TIMER1_PRESCALER == TMR_NO_PRESCALER)
#define TMR_u32_TIMER1_TOVF       (uint32_t)8192
#elif (TMR_TIMER1_PRESCALER == TMR_FREQ_OVER_8)
#define TMR_u32_TIMER1_TOVF      (uint32_t)65536
#define TMR_u8_TIMER1_TICKTIME   (uint8_t)1
#elif (TMR_TIMER1_PRESCALER == TMR_FREQ_OVER_64)
#define TMR_u32_TIMER1_TOVF       (uint32_t)524288
#define TMR_u8_TIMER1_TICKTIME    (uint8_t)8
#elif (TMR_TIMER1_PRESCALER == TMR_FREQ_OVER_256)
#define TMR_u32_TIMER1_TOVF       (uint32_t)2097152
#define TMR_u8_TIMER1_TICKTIME    (uint8_t)32
#elif (TMR_TIMER1_PRESCALER == TMR_FREQ_OVER_1024)
#define TMR_u32_TIMER1_TOVF       (uint32_t)8388608
#define TMR_u8_TIMER1_TICKTIME    (uint8_t)128
#endif

#endif /* TMR_CONFIG_H */ 

