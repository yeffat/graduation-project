/*
 * Master_config.h
 *
 *  Created on: Jul 7, 2024
 *      Author: ahmed
 */

#ifndef MASTER_CONFIG_H
#define MASTER_CONFIG_H



// Define the pins and ports for selecting slaves
#define SPI_SS_PIN    DIO_PORTB, DIO_PIN4


// Define any necessary configuration macros here
#define SPI_BUFFER_SIZE  2
#define SPI_SLAVE_READY_PIN DIO_PORTD, DIO_PIN3  // External interrupt pin
#define ACK	0x20
#define NACK 0x21

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

#endif /* MASTER_CONFIG_H */
