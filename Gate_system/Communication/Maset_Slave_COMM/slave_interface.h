#ifndef SLAVE_INTERFACE_H_
#define SLAVE_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

// Initialize the slave communication module
void Slave_Comm_Init(void);

// Check for a command from the master
void Slave_SendByte(uint8_t sent );
void Slave_ReceiveByte(uint8_t*receivedByte);

// Send a request to the master

void Slave_Send_Request(uint8_t* data);

void Slave_Receive_Data(uint8_t* buffer);

void Slave_Send_Data(uint8_t* data);

#endif /* SLAVE_INTERFACE_H_ */
