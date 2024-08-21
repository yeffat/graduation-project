/*
 * EX_INT_prog.c
 *
 *  Created on: Oct 14, 2023
 *      Author: ahmed
 */
#include "../EX_INT/EX_INT_cfg.h"
#include "../EX_INT/EX_INT_int.h"
#include "../EX_INT/EX_INT_private.h"
#include "../EX_INT/EX_INT_reg.h"
#include "..\..\LIB\STD_TYPES.h"
#include "..\..\LIB\BIT_MATH.h"




void (*INT0_PFun)(void);
void (*INT1_PFun)(void);
void (*INT2_PFun)(void);

/**************************************************************************/
/**************************************************************************/
void EXTI0_VoidInit(void){

	switch (INT0_SENSE)
	{
	case LOW_LEVEL:
		CLR_BIT(MCUCR, ISC01);
		CLR_BIT(MCUCR, ISC00);
		break;

	case ANY_CHANGE:
		CLR_BIT(MCUCR, ISC01);
		SET_BIT(MCUCR, ISC00);
		break;
	case FAILING_EDGE:
			SET_BIT(MCUCR, ISC01);
			CLR_BIT(MCUCR, ISC00);
			break;
	case RISING_EDGE:
			SET_BIT(MCUCR, ISC01);
			SET_BIT(MCUCR, ISC00);
			break;
	}
	//PIE 	Enable interrupt 0
	SET_BIT(GICR, INT0);

}
/**************************************************************************/
void EXTI1_VoidInit(void){

	switch (INT1_SENSE)
	{
	case LOW_LEVEL:
		CLR_BIT(MCUCR, ISC11);
		CLR_BIT(MCUCR, ISC10);
		break;

	case ANY_CHANGE:
		CLR_BIT(MCUCR, ISC11);
		SET_BIT(MCUCR, ISC10);
		break;
	case FAILING_EDGE:
			SET_BIT(MCUCR, ISC11);
			CLR_BIT(MCUCR, ISC10);
			break;
	case RISING_EDGE:
			SET_BIT(MCUCR, ISC11);
			SET_BIT(MCUCR, ISC10);
			break;
	}
	//PIE 	Enable interrupt 1
	SET_BIT(GICR, INT1);

}
/**************************************************************************/
void EXTI2_VoidInit(void){

	switch (INT2_SENSE)
	{
	case FAILING_EDGE:
			CLR_BIT(MCUCSR, ISC2);
			break;
	case RISING_EDGE:
			SET_BIT(MCUCSR, ISC2);
			break;

	}
	//PIE 	Enable interrupt 2
	SET_BIT(GICR, INT2);

}
/**************************************************************************/
/**************************************************************************/
//Change Sense control of interrupt 0 during program
void EXTI0_voidSetSenseControl(uint8_t copy_U8SenseControl){
	switch (copy_U8SenseControl)
		{
		case LOW_LEVEL:
			CLR_BIT(MCUCR, ISC01);
			CLR_BIT(MCUCR, ISC00);
			break;

		case ANY_CHANGE:
			CLR_BIT(MCUCR, ISC01);
			SET_BIT(MCUCR, ISC00);
			break;
		case FAILING_EDGE:
				SET_BIT(MCUCR, ISC01);
				CLR_BIT(MCUCR, ISC00);
				break;
		case RISING_EDGE:
				SET_BIT(MCUCR, ISC01);
				SET_BIT(MCUCR, ISC00);
				break;
		}

}
//Change Sense control of interrupt 1 during program
void EXTI1_voidSetSenseControl(uint8_t copy_U8SenseControl){
	switch (copy_U8SenseControl)
		{
		case LOW_LEVEL:
			CLR_BIT(MCUCR, ISC11);
			CLR_BIT(MCUCR, ISC10);
			break;

		case ANY_CHANGE:
			CLR_BIT(MCUCR, ISC11);
			SET_BIT(MCUCR, ISC10);
			break;
		case FAILING_EDGE:
				SET_BIT(MCUCR, ISC11);
				CLR_BIT(MCUCR, ISC10);
				break;
		case RISING_EDGE:
				SET_BIT(MCUCR, ISC11);
				SET_BIT(MCUCR, ISC10);
				break;
		}

}
//Change Sense control of interrupt 2 during program
void EXTI2_voidSetSenseControl(uint8_t copy_U8SenseControl){
	switch (copy_U8SenseControl)
		{

		case FAILING_EDGE:
				CLR_BIT(MCUCSR, ISC2);
				break;
		case RISING_EDGE:
				SET_BIT(MCUCSR, ISC2);
				break;
		}

}

/**************************************************************************/
/**************************************************************************/
//Enable or disable interrupt 0
void EXTI0_voidEnable(void){

	SET_BIT(GICR, INT0);
}
void EXTI0_voidDisable(void){

	CLR_BIT(GICR, INT0);
}
/**************************************************************************/
//Enable or disable interrupt 1
void EXTI1_voidEnable(void){

	SET_BIT(GICR, INT1);
}
void EXTI1_voidDisable(void){

	CLR_BIT(GICR, INT1);
}
/**************************************************************************/
//Enable or disable interrupt 2
void EXTI2_voidEnable(void){

	SET_BIT(GICR, INT2);
}
void EXTI2_voidDisable(void){

	CLR_BIT(GICR, INT2);
}

/**************************************************************************/
/**************************************************************************/
void EXTI0_voidSetCallBack(void (*copy_PFunc)(void)){

	INT0_PFun = copy_PFunc;

}
/**************************************************************************/
void EXTI1_voidSetCallBack(void (*copy_PFunc)(void)){

	INT1_PFun = copy_PFunc;

}
/**************************************************************************/
void EXTI2_voidSetCallBack(void (*copy_PFunc)(void)){

	INT2_PFun = copy_PFunc;

}

/**************************************************************************/
/**************************************************************************/
//attribute prevents optimization
void __vector_1(void) __attribute__((signal)); //ISR for interrupt 0
void __vector_2(void) __attribute__((signal)); //ISR for interrupt 1
void __vector_3(void) __attribute__((signal)); //ISR for interrupt 2


/**************************************************************************/
/**************************************************************************/
void __vector_1(void){

	INT0_PFun();
}
/**************************************************************************/
void __vector_2(void){

	INT1_PFun();
}
/**************************************************************************/
void __vector_3(void){

	INT2_PFun();
}
