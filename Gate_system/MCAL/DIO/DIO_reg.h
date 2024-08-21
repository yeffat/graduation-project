/*
  * DIO_Register.h
 *
 *  Created on: Sep 12, 2023
 *      Author: ahmed
 */
#ifndef DIO_REG_H_
#define DIO_REG_H_
//Port A

#define PORTA (*(volatile uint8_t*)0x3B)
#define PORTA0	0
#define PORTA1	1
#define PORTA2	2
#define PORTA3	3
#define PORTA4	4
#define PORTA5	5
#define PORTA6	6
#define PORTA7	7

#define DDRA (*(volatile uint8_t*)0x3A)
#define DDA0	0
#define DDA1	1
#define DDA2	2
#define DDA3	3
#define DDA4	4
#define DDA5	5
#define DDA6	6
#define DDA7	7

#define PINA (*(volatile uint8_t*)0x39)
#define PINA0	0
#define PINA1	1
#define PINA2	2
#define PINA3	3
#define PINA4	4
#define PINA5	5
#define PINA6	6
#define PINA7	7

//Port B
#define PORTB (*(volatile uint8_t*)0x38)
#define PORTB0	0
#define PORTB1	1
#define PORTB2	2
#define PORTB3	3
#define PORTB4	4
#define PORTB5	5
#define PORTB6	6
#define PORTB7	7

#define DDRB (*(volatile uint8_t*)0x37)
#define DDB0	0
#define DDB1	1
#define DDB2	2
#define DDB3	3
#define DDB4	4
#define DDB5	5
#define DDB6	6
#define DDB7	7

#define PINB (*(volatile uint8_t*)0x36)
#define PINB0	0
#define PINB1	1
#define PINB2	2
#define PINB3	3
#define PINB4	4
#define PINB5	5
#define PINB6	6
#define PINB7	7



//Port C
#define PORTC (*(volatile uint8_t*)0x35)
#define PORTC0	0
#define PORTC1	1
#define PORTC2	2
#define PORTC3	3
#define PORTC4	4
#define PORTC5	5
#define PORTC6	6
#define PORTC7	7

#define DDRC (*(volatile uint8_t*)0x34)
#define DDC0	0
#define DDC1	1
#define DDC2	2
#define DDC3	3
#define DDC4	4
#define DDC5	5
#define DDC6	6
#define DDC7	7

#define PINC (*(volatile uint8_t*)0x33)
#define PINC0	0
#define PINC1	1
#define PINC2	2
#define PINC3	3
#define PINC4	4
#define PINC5	5
#define PINC6	6
#define PINC7	7


// Port D
#define PORTD (*(volatile uint8_t*)0x32)
#define PORTD0	0
#define PORTD1	1
#define PORTD2	2
#define PORTD3	3
#define PORTD4	4
#define PORTD5	5
#define PORTD6	6
#define PORTD7	7

#define DDRD (*(volatile uint8_t*)0x31)
#define DDD0	0
#define DDD1	1
#define DDD2	2
#define DDD3	3
#define DDD4	4
#define DDD5	5
#define DDD6	6
#define DDD7	7


#define PIND (*(volatile uint8_t*)0x30)
#define PIND0	0
#define PIND1	1
#define PIND2	2
#define PIND3	3
#define PIND4	4
#define PIND5	5
#define PIND6	6
#define PIND7	7


#endif
