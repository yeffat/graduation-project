#ifndef SLAVE_CONFIG_H_
#define SLAVE_CONFIG_H_

// Define the SPI buffer size
#define SPI_BUFFER_SIZE 2

// Request types
// From slave to master
#define REQUEST_PARK_CAR               0x06
#define REQUEST_RETRIEVE_CAR           0x07

// From master to slave
//PARK REQUEST
#define EMPTY_SLOT_FOUND               0x08
#define NO_EMPTY_SLOT                  0x09
#define REQUESTED_EMPTY_SLOT_READY     0x0A
//retrieve REQUEST
#define REQUESTED_CAR_READY            0x0B
#define WRONG_SLOT_ID                  0x0C
#define CLOSE_GATE						0x0D

#define UNKNOWN_REQUEST                0x0E
// Define GPIO pin for signaling the master
#define REQUEST_SIGNAL_PORT DIO_PORTB
#define REQUEST_SIGNAL_PIN  DIO_PIN3

#endif /* SLAVE_CONFIG_H_ */
