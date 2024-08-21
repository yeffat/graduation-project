#include"SEV_SEG.h"
#include"..\..\MCAL\DIO\DIO_int.h"
void SEV_SEG_VidInit(void)
{
	//Set Direction
	DIO_U8SetPortDirection( SEV_SEG_PORT , DIO_PORT_OUT );
	//common anode
	DIO_U8SetPortValue( SEV_SEG_PORT , DIO_PORT_HIGH );

}


void SEV_SEG_VidSetNumber(uint8_t Copy_U8Number) {
    switch (Copy_U8Number) {
        case 0: DIO_U8SetPortValue(SEV_SEG_PORT, SEV_SEG_ZERO); break;
        case 1: DIO_U8SetPortValue(SEV_SEG_PORT, SEV_SEG_ONE); break;
        case 2: DIO_U8SetPortValue(SEV_SEG_PORT, SEV_SEG_TWO); break;
        case 3: DIO_U8SetPortValue(SEV_SEG_PORT, SEV_SEG_THREE); break;
        case 4: DIO_U8SetPortValue(SEV_SEG_PORT, SEV_SEG_FOUR); break;
        case 5: DIO_U8SetPortValue(SEV_SEG_PORT, SEV_SEG_FIVE); break;
        case 6: DIO_U8SetPortValue(SEV_SEG_PORT, SEV_SEG_SIX); break;
        case 7: DIO_U8SetPortValue(SEV_SEG_PORT, SEV_SEG_SEVEN); break;
        case 8: DIO_U8SetPortValue(SEV_SEG_PORT, SEV_SEG_EIGHT); break;
        case 9: DIO_U8SetPortValue(SEV_SEG_PORT, SEV_SEG_NINE); break;
        default: /* Handle invalid input */ break;
    }
}
