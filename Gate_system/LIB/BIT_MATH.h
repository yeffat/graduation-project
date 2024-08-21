#ifndef BIT_MATH_H
#define BIT_MATH_H


#define SET_BIT(REG, BIT_NUM) 		(REG|=(1<<BIT_NUM))
#define CLR_BIT(REG, BIT_NUM)		(REG&= ~(1<<BIT_NUM))
#define TOGGLE_BIT(REG, BIT_NUM)	(REG ^= (1<<BIT_NUM))

#define ASSIGN_BIT(REG,BIT_NUM,value)	do{ CLR_BIT(REG,BIT_NUM); REG|=((value)<<BIT_NUM); }while(0)

#define SET_NIBBLE_LOW(REG)	REG|=0b00001111
#define CLR_NIBBLE_LOW(REG)	REG&=0b11110000
#define TOGGLE_NIBBLE_LOW(REG)	REG ^= 0b00001111
#define ASSIGN_NIBBLE_LOW(REG,value)	do{ CLR_NIBBLE_LOW(REG); REG|=value; }while(0)
 

#define SET_NIBBLE_HIGH(REG)	REG|=0b11110000
#define CLR_NIBBLE_HIGH(REG)	REG&=0b00001111
#define TOGGLE_NIBBLE_HIGH(REG)	REG ^=0b11110000
#define ASSIGN_NIBBLE_HIGH(REG,value)	do{ CLR_NIBBLE_HIGH(REG); REG|=value<<4; }while(0)
	
#define GET_BIT(REG, BIT_NUM)		((REG>>BIT_NUM) & 0x01)
#define GET_NIBBLE_LOW(REG)	REG&0b00001111
#define GET_NIBBLE_HIGH(REG)	(REG&0b11110000)>>4

#define CIR_SHIFT_RIGHT(REG,shiftno)	REG= (REG<<( sizeof(REG)*8 -shiftno)) | (REG>>shiftno)  	
#define CIR_SHIFT_LEFT(REG,shiftno)	REG= (REG>>( sizeof(REG)*8 -shiftno)) | (REG<<shiftno)		

#endif