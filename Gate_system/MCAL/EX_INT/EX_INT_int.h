/*
q * EX_INT_interface.h
 *
 *  Created on: Oct 14, 2023
 *      Author: ahmed
 */

#ifndef MCAL_EX_INT_EX_INT_INT_H_
#define MCAL_EX_INT_EX_INT_INT_H_

#define LOW_LEVEL		1
#define ANY_CHANGE		2
#define FAILING_EDGE	3
#define RISING_EDGE 	4

/******************************************************************/
/******************************************************************/
//INTERRUPT 0
void EXTI0_VoidInit(void);
// Configuration in run time
void EXTI0_voidSetSenseControl(uint8_t copy_U8SenseControl);
void EXTI0_voidEnable(void);
void EXTI0_voidSetCallBack(void (*copy_PFunc)(void));
void EXTI0_voidDisable(void);

/******************************************************************/

//INTERRUPT 1
void EXTI1_VoidInit(void);
// Configuration in run time
void EXTI1_voidSetSenseControl(uint8_t copy_U8SenseControl);
void EXTI1_voidEnable(void);
void EXTI1_voidSetCallBack(void (*copy_PFunc)(void));
void EXTI1_voidDisable(void);

/******************************************************************/

//INTERRUPT 2
void EXTI2_VoidInit(void);
// Configuration in run time
void EXTI2_voidSetSenseControl(uint8_t copy_U8SenseControl);
void EXTI2_voidEnable(void);
void EXTI2_voidSetCallBack(void (*copy_PFunc)(void));
void EXTI2_voidDisable(void);

#endif /* MCAL_EX_INT_EX_INT_INT_H_ */
