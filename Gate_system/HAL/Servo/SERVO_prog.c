
#include "../../LIB\STD_TYPES.h"
#include "../../LIB\BIT_MATH.h"

#include "../../MCAL/Timers/TMR_interface.h"
#include "../../MCAL/DIO/DIO_int.h"

#include "SERVO_interface.h"

void SERVO_u8Init(){
	TMR_vInit();

	DIO_U8SetPinDirection(DIO_PORTD,DIO_PIN4,DIO_OUTPUT);

}
uint8_t SERVO_u8SetServoAngle (uint8_t Copy_U8Angle)
{
	/*Local Variable holding the error state*/
	uint8_t Local_u8Error = ERROR_OK;
	uint16_t Local_u16RequiredCompareValue;

	if (Copy_U8Angle <= 180)
	{
		Local_u16RequiredCompareValue = (490+(11*Copy_U8Angle));
		//Local_u16RequiredCompareValue =1000 + ((uint32_t)Copy_U8Angle * 1000 / 180);
		TMR_u8SetPWM (Local_u16RequiredCompareValue);
	}
	else
	{
		Local_u8Error = ERROR_NOK;
	}
	/*Function return*/
	return Local_u8Error;
}
