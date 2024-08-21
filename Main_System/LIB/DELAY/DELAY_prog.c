/********************************************************************/
/********************************************************************/
/* Description                                                      */
/* ------------                                                     */
/* Program file for using Delay functions (in milliseconds) 		*/
/* in AVR ATmega32 using NOP assembly instruction 					*/
/* which takes only one cycle             							*/
/********************************************************************/
#include "..\STD_TYPES.h"
#include "DELAY_interface.h"
#include "DELAY_priv.h"


/*
 * Description: Function to make delay in millisecond using NOP assembly instruction
 * Inputs: the required delay in millisecond
 * Output: void
 */
void delay_milliseconds (uint32_t Copy_U32OuterLoopIterations)
{

	uint32_t U32OuterLoopIndex = 0, U32InnerLoopIndex = 0;

	for(U32OuterLoopIndex = 0; U32OuterLoopIndex < Copy_U32OuterLoopIterations; U32OuterLoopIndex++)
	{

		// This loop yields 1 millisecond

		for (U32InnerLoopIndex = 0; U32InnerLoopIndex < INNER_LOOP_ITERATIONS; U32InnerLoopIndex++)
		{
			asm("NOP");
			asm("NOP");
			asm("NOP");
			asm("NOP");
		}
	}

}


