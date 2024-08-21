/********************************************************************/
/* Description                                                      */
/* ------------                                                     */
/* Interface file for using Delay functions (in milliseconds) 		*/
/* in AVR ATmega32 using NOP assembly instruction 					*/
/* which takes only one cycle             							*/
/********************************************************************/
/* PreProcessor Guard */
#ifndef DELAY_INTERFACE_H_
#define DELAY_INTERFACE_H_
#include"../STD_TYPES.h"
/*
 * Description: Function to make delay in millisecond using NOP assembly instruction
 * Inputs: the required delay in millisecond
 * Output: void
 */
void delay_milliseconds (uint32_t Copy_U32OuterLoopIterations);
#endif /* DELAY_INTERFACE_H_ */
