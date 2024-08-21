
#include "slave_interface.h"
#include "slave_config.h"
#include "../../MCAL/SPI/SPI_interface.h"
#include "../../MCAL/DIO/DIO_int.h"


uint8_t response[SPI_BUFFER_SIZE];

void Slave_Comm_Init(void) {
    DIO_U8SetPinDirection(DIO_PORTB, DIO_PIN4, DIO_INPUT);
    DIO_U8SetPinDirection(DIO_PORTB, DIO_PIN5, DIO_INPUT);
    DIO_U8SetPinDirection(DIO_PORTB, DIO_PIN6, DIO_OUTPUT);
    DIO_U8SetPinDirection(DIO_PORTB, DIO_PIN7, DIO_INPUT);
    SPI_vInit(); // Initialize the SPI as a slave

    DIO_U8SetPinDirection(REQUEST_SIGNAL_PORT, REQUEST_SIGNAL_PIN, DIO_OUTPUT); // Set the request signal pin as output


}

void Slave_ReceiveByte(uint8_t*receivedByte ) {

    SPI_u8ReceiveByte_Synch(receivedByte);

}
void Slave_SendByte(uint8_t sent ) {

    SPI_u8SendByte_Synch(sent);

}
void Slave_Send_Request(uint8_t* data) {//Park or retrive car

    DIO_U8SetPinValue(REQUEST_SIGNAL_PORT, REQUEST_SIGNAL_PIN, DIO_HIGH); // Signal the master
    Slave_Send_Data(data);
    DIO_U8SetPinValue(REQUEST_SIGNAL_PORT, REQUEST_SIGNAL_PIN, DIO_LOW); // unSignal the master
}

void Slave_Send_Data(uint8_t* data) {

    // Send data to the slave
    for (uint8_t i = 0; i < SPI_BUFFER_SIZE; i++) {
        SPI_u8SendByte_Synch(data[i]);
    }

}

void Slave_Receive_Data(uint8_t* buffer) {
    // Receive data from the slave
    for (uint8_t i = 0; i < SPI_BUFFER_SIZE; i++) {
        SPI_u8ReceiveByte_Synch(&buffer[i]); // Send dummy byte to receive data
    }

}
