#include "../../LIB/STD_TYPES.h"
#include "I2c.h"
#include "I2C_priv.h"
#include "../../LIB/BIT_MATH.h"

void i2c_init_master(void)
{
    TWBR = 2; // bit rate = 400.000 kbps, F_CPU = 8M, SCL freq = F_CPU / (16 + 2 * TWBR * 4^TWPS)
    TWSR &= ~((1<<TWPS1) | (1<<TWPS0)); // Prescaler = 1
    TWAR = (1<<1); // My address = 0x01
    TWCR = (1<<TWEN); // Enable I2C
}

void i2c_init_slave(void)
{
    TWAR = (1<<1); // My address = 0x01
    TWCR = (1<<TWEN); // Enable I2C
}

void i2c_start(void)
{
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); // Clear TWI interrupt flag, put start condition on SDA, enable TWI
    while(!(TWCR & (1<<TWINT))); // Wait till start condition is transmitted
    while((TWSR & 0xF8) != START_ACK); // Check for acknowledgment
}

void i2c_repeated_start(void)
{
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); // Clear TWI interrupt flag, put start condition on SDA, enable TWI
    while(!(TWCR & (1<<TWINT))); // Wait till restart condition is transmitted
    while((TWSR & 0xF8) != REP_START_ACK); // Check for acknowledgment
}

void i2c_send_slave_address_with_write_req(unsigned char slave_address)
{
    TWDR = (slave_address << 1); // Address and write instruction
    TWCR = (1<<TWINT) | (1<<TWEN); // Clear TWI interrupt flag, enable TWI
    while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
    while((TWSR & 0xF8) != SLAVE_ADD_AND_WR_ACK); // Check for acknowledgment
}

void i2c_send_slave_address_with_read_req(unsigned char slave_address)
{
    TWDR = (slave_address << 1) | 1; // Address and read instruction
    TWCR = (1<<TWINT) | (1<<TWEN); // Clear TWI interrupt flag, enable TWI
    while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
    while((TWSR & 0xF8) != SLAVE_ADD_AND_RD_ACK); // Check for acknowledgment
}

void i2c_write_byte(unsigned char byte)
{
    TWDR = byte; // Put data in TWDR
    TWCR = (1<<TWINT) | (1<<TWEN); // Clear TWI interrupt flag, enable TWI
    while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
    while((TWSR & 0xF8) != WR_BYTE_ACK); // Check for acknowledgment
}

unsigned char i2c_read_byte(void)
{
    TWCR = (1<<TWINT) | (1<<TWEN); // Clear TWI interrupt flag, enable TWI
    while(!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
    while((TWSR & 0xF8) != RD_BYTE_WITH_NACK); // Check for acknowledgment
    return TWDR;
}

void i2c_stop(void)
{
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO); // Clear TWI interrupt flag, put stop condition on SDA, enable TWI
}

void i2c_slave_check_slave_address_received_with_write_req(void)
{
    TWCR = (1<<TWEA) | (1<<TWEN) | (1<<TWINT); // Enable acknowledgment after receive, enable TWI, clear TWI interrupt flag
    while (!(TWCR & (1<<TWINT))); // Wait for TWINT flag
    while((TWSR & 0xF8) != SLAVE_ADD_RCVD_WR_REQ);
}

void i2c_slave_check_slave_address_received_with_read_req(void)
{
    TWCR = (1<<TWEA) | (1<<TWEN) | (1<<TWINT); // Enable acknowledgment after receive, enable TWI, clear TWI interrupt flag
    while (!(TWCR & (1<<TWINT))); // Wait for TWINT flag
    while((TWSR & 0xF8) != SLAVE_ADD_RCVD_RD_REQ);
}

unsigned char i2c_slave_read_byte(void)
{
    TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN); // Clear TWI interrupt flag, get enable acknowledgment, enable TWI
    while(!(TWCR & (1<<TWINT))); // Wait for TWINT flag
    while((TWSR & 0xF8) != SLAVE_DATA_RECEIVED);
    return TWDR;
}

void i2c_slave_write_byte(unsigned char byte)
{
    TWDR = byte;
    TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN); // Clear TWI interrupt flag, get enable acknowledgment, enable TWI
    while(!(TWCR & (1<<TWINT))); // Wait for TWINT flag
    while((TWSR & 0xF8) != SLAVE_BYTE_TRANSMITTED); // Data byte in TWDR has been transmitted
}
