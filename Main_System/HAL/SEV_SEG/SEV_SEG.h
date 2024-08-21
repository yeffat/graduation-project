#ifndef SEV_SEG_H_
#define SEV_SEG_H_

#include"..\..\LIB\STD_TYPES.h"
#define    SEV_SEG_PORT      DIO_PORTA


#define    SEV_SEG_ZERO      ~0b00111111
#define    SEV_SEG_ONE       ~0b00000110
#define    SEV_SEG_TWO       ~0b01011011
#define    SEV_SEG_THREE     ~0b01001111
#define    SEV_SEG_FOUR      ~0b01100110
#define    SEV_SEG_FIVE      ~0b01101101
#define    SEV_SEG_SIX       ~0b01111101
#define    SEV_SEG_SEVEN     ~0b00000111
#define    SEV_SEG_EIGHT     ~0b01111111
#define    SEV_SEG_NINE      ~0b01101111



void SEV_SEG_VidInit(void);

void SEV_SEG_VidSetNumber (  uint8_t Copy_U8Number );




#endif

