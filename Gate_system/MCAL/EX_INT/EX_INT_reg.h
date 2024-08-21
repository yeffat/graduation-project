/*
 * EXT_INT_reg.h
 *
 *  Created on: Oct 14, 2023
 *      Author: ahmed
 */

#ifndef MCAL_EX_INT_EX_INT_REG_H_
#define MCAL_EX_INT_EX_INT_REG_H_

//#define SREG (*(volatile uint8_t*)0x5F)
//#define C	0
//#define Z	1
//#define N	2
//#define V	3
//#define S	4
//#define H	5
//#define T	6
//#define I	7


#define MCUCSR	(*(volatile uint8_t*)0x54)
#define PORF	0
#define EXTRF	1
#define BORF	2
#define WDRF	3
#define JTRF	4

#define ISC2	6
#define JTD		7

#define MCUCR	(*(volatile uint8_t*)0x55)
#define ISC00	0
#define ISC01	1
#define ISC10	2
#define ISC11	3
#define SM0		4
#define SM1		5
#define SM2		6
#define SE		7

#define GIFR	(*(volatile uint8_t*)0x5A)

#define GICR	(*(volatile uint8_t*)0x5B)
#define IVCE	0
#define IVSEL	1




#define INT2	5
#define INT0	6
#define INT1	7



#endif /* MCAL_EX_INT_EX_INT_REG_H_ */
