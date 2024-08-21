#include "master_interface.h"
#include "master_config.h"
#include "..\..\MCAL\SPI\SPI_interface.h"
#include "..\..\MCAL\DIO\DIO_int.h"
#include "..\..\MCAL\DIO\DIO_reg.h"
#include "..\..\MCAL\EX_INT\EX_INT_int.h"
#include "..\..\LIB\DELAY\DELAY_interface.h"




void Master_Comm_Init(void) {
    // Initialize SPI
    DIO_U8SetPinDirection(DIO_PORTB, DIO_PIN4, DIO_OUTPUT);
    DIO_U8SetPinDirection(DIO_PORTB, DIO_PIN5, DIO_OUTPUT);
    DIO_U8SetPinDirection(DIO_PORTB, DIO_PIN6, DIO_INPUT);
    DIO_U8SetPinDirection(DIO_PORTB, DIO_PIN7, DIO_OUTPUT);

    SPI_vInit();

    // Initialize external interrupt for SPI slave ready signal
    EXTI1_VoidInit();
    EXTI1_voidEnable();

    // Set slave ready pin as input
    DIO_U8SetPinDirection(SPI_SLAVE_READY_PIN, DIO_INPUT);
    MASTER_DESELECT_SLAVE();

}

void Master_SendByte(uint8_t send) {
	MASTER_SELECT_SLAVE();

    SPI_u8SendByte_Synch(send);

    MASTER_DESELECT_SLAVE();
}
void Master_ReceiveByte(uint8_t *receive) {
	MASTER_SELECT_SLAVE();

	SPI_u8SendByte_Synch(0xff);
	SPI_u8ReceiveByte_Synch(receive);

	MASTER_DESELECT_SLAVE();

}
void Master_Send_Data(uint8_t* data) {
	MASTER_SELECT_SLAVE();

    // Send data to the slave
	SPI_u8SendByte_Synch(ACK);

    for (uint8_t i = 0; i < SPI_BUFFER_SIZE; i++) {
        SPI_u8SendByte_Synch(data[i]);
    }
   MASTER_DESELECT_SLAVE();

}

void Master_Receive_Data(uint8_t* buffer) {
	MASTER_SELECT_SLAVE();
    // Receive data from the slave
    for (uint8_t i = 0; i < SPI_BUFFER_SIZE; i++) {
        SPI_u8SendByte_Synch(0xff);
        SPI_u8ReceiveByte_Synch(&buffer[i]);
    }
    MASTER_DESELECT_SLAVE();
}

void SetSlaveReadyCallBack(void (*callback)(void)) {
    EXTI1_voidSetCallBack(callback);
}
