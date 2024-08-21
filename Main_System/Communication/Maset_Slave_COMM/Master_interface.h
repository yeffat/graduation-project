/* Preprocessor Guard */
#ifndef MASTER_INTERFACE_H_
#define MASTER_INTERFACE_H_

#include "..\..\LIB\STD_TYPES.h"

#define MASTER_SELECT_SLAVE() (PORTB &= ~(1 << PORTB4))
#define MASTER_DESELECT_SLAVE() (PORTB |= (1 << PORTB4))

// Initialize the master communication module
void Master_Comm_Init(void);

// Send a command to the slave
void Master_SendByte(uint8_t send);

void Master_ReceiveByte(uint8_t *receive);


// Send data to the slave
void Master_Send_Data(uint8_t* data);

// Receive data from the slave
void Master_Receive_Data(uint8_t* buffer);

void SetSlaveReadyCallBack(void (*callback)(void));

#endif /* MASTER_INTERFACE_H_ */
