
#include "..\..\LIB\STD_TYPES.h"
#include "..\..\LIB\BIT_MATH.h"
#include "TMR_config.h"
#include "TMR_interface.h"
#include "TMR_priv.h"


/*Static variables which save the value of TCCR register corresponding to each timer*/
static uint8_t TMR_u8Timer1CtrlRegValue;

/*
 * Description: Function to set the initialized state and prescaler for each timer (0,1,2)
 * Inputs: none
 * Output: void
 */
void TMR_vInit (void)
{
	/* Setting the initialization for Timer1 */
	if (TMR_u8_TIMER1_INIT_STATE == TMR_u8_DISABLE)
	{
	   CLR_BIT(TMR_TCCR1B,0);
	   CLR_BIT(TMR_TCCR1B,1);
	   CLR_BIT(TMR_TCCR1B,2);
	}
	else
	{
		if (TMR_u8_TIMER1_MODE == TMR_u8_FASTPWM_ICR1)
				{
					SET_BIT(TMR_TCCR1A,1);
					SET_BIT(TMR_TCCR1B,3);
					SET_BIT(TMR_TCCR1B,4);

					TMR_ICR1 = TMR_u16_ICR1_VAL;
				}


		/* Checking the compare output mode applied on OC1A/OC1B pins in (CTC/FAST PWM/PHASE CORRECT) modes*/
		switch (TMR_u8_TIMER1_COPT_MODE)
		{
			case TMR_u8_TOGGLE_OCX:
			{
				if (TMR_u8_TIMER1A_COPT_STATE == TMR_u8_ENABLE)
					SET_BIT(TMR_TCCR1A,6);
				if (TMR_u8_TIMER1B_COPT_STATE == TMR_u8_ENABLE)
					SET_BIT(TMR_TCCR1A,4);
				break;
			}
			case TMR_u8_CLEAR_OCX:
			{
				if (TMR_u8_TIMER1A_COPT_STATE == TMR_u8_ENABLE)
					SET_BIT(TMR_TCCR1A,7);
				if (TMR_u8_TIMER1B_COPT_STATE == TMR_u8_ENABLE)
					SET_BIT(TMR_TCCR1A,5);
				break;
			}
			case TMR_u8_SET_OCX:
			{
				if (TMR_u8_TIMER1A_COPT_STATE == TMR_u8_ENABLE)
				{
					SET_BIT(TMR_TCCR1A,6);
					SET_BIT(TMR_TCCR1A,7);
				}
				if (TMR_u8_TIMER1B_COPT_STATE == TMR_u8_ENABLE)
				{
					SET_BIT(TMR_TCCR1A,4);
					SET_BIT(TMR_TCCR1A,5);
				}
				break;
			}
		}
		/* Checking assigned Prescaler for Timer/Counter1 */

#if TMR_TIMER1_PRESCALER == TMR_NO_PRESCALER

				SET_BIT(TMR_TCCR1B,0);
#elif TMR_TIMER1_PRESCALER == TMR_FREQ_OVER_8

				SET_BIT(TMR_TCCR1B,1);
#elif TMR_TIMER1_PRESCALER == TMR_FREQ_OVER_64

				SET_BIT(TMR_TCCR1B,0);
				SET_BIT(TMR_TCCR1B,1);
#elif TMR_TIMER1_PRESCALER == TMR_FREQ_OVER_256

				SET_BIT(TMR_TCCR1B,2);
#elif TMR_TIMER1_PRESCALER == TMR_FREQ_OVER_1024

				SET_BIT(TMR_TCCR1B,0);
				SET_BIT(TMR_TCCR1B,2);
#else
				SET_BIT(TMR_TCCR1B,0);
#endif

		TMR_u8Timer1CtrlRegValue = TMR_TCCR1B;

	}
	return;
}


/*
 * Description: Function to set the duty cycle of the PWM signal generated from Timer1,Pins OC1A or/and OC1B
 * (used mainly in servo interfacing and load which needs TMR_u8_FASTPWM_ICR1 timer mode)
 * Inputs: The desired timer compare value
 * Output: void
 */
void TMR_u8SetPWM (uint16_t Copy_u16ReqCompValue)
{
   if (TMR_u8_TIMER1A_COPT_STATE == TMR_u8_ENABLE)
   {
	   if (TMR_u8_TIMER1_COPT_MODE == TMR_u8_CLEAR_OCX)
		   TMR_OCRA1 = Copy_u16ReqCompValue;
	   else if (TMR_u8_TIMER1_COPT_MODE == TMR_u8_SET_OCX)
		   TMR_OCRA1 = TMR_u16_ICR1_VAL-Copy_u16ReqCompValue;
	}
	if (TMR_u8_TIMER1B_COPT_STATE == TMR_u8_ENABLE)
	{
		   if (TMR_u8_TIMER1_COPT_MODE == TMR_u8_CLEAR_OCX)
			   TMR_OCRB1 = Copy_u16ReqCompValue;
		   else if (TMR_u8_TIMER1_COPT_MODE == TMR_u8_SET_OCX)
			   TMR_OCRB1 = TMR_u16_ICR1_VAL-Copy_u16ReqCompValue;
	}
	return;
}

