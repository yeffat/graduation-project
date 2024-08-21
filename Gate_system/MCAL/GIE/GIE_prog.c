/*
 * GIE_prog.c
 *
 *  Created on: Oct 20, 2023
 *      Author: ahmed
 */
#include "..\..\LIB\BIT_MATH.h"
#include "..\..\LIB\STD_TYPES.h"

#include "GIE_int.h"
#include "GIE_reg.h"


void GIE_voidEnable(void){

	SET_BIT(SREG , I);

}

void GIE_voidDisable(void){

	CLR_BIT(SREG , I);

}
