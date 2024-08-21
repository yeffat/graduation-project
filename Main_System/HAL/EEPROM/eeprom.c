#include "../../LIB/STD_TYPES.h"
#include "..\..\MCAL\I2C\I2C.h"
#include "../../LIB/DELAY/DELAY_interface.h"
#include "eeprom.h"


void eeprom_init(void)
{
    i2c_init_master();
}

void eeprom_write_byte(unsigned short address, unsigned char data)
{
    i2c_start();

    i2c_send_slave_address_with_write_req(0x50 | ((address & 0x0700) >> 8));

    i2c_write_byte((unsigned char)address);

    i2c_write_byte(data);

    i2c_stop();
    delay_milliseconds(4);
    return;
}

unsigned char eeprom_read_byte(unsigned short address)
{
    unsigned char data;
    i2c_start();

    i2c_send_slave_address_with_write_req(0x50 | ((address & 0x0700) >> 8));

    i2c_write_byte((unsigned char)address);

    i2c_repeated_start();

    i2c_send_slave_address_with_read_req(0x50 | ((address & 0x0700) >> 8));

    data = i2c_read_byte();

    i2c_stop();
    delay_milliseconds(4);
    return data;
}

void eeprom_write_block(unsigned short address, const unsigned char* data, unsigned short length)
{
    unsigned short i;
    for (i = 0; i < length; i++)
    {
        eeprom_write_byte(address + i, data[i]);
        delay_milliseconds(5); // Small delay to ensure EEPROM write is complete
    }
}

void eeprom_read_block(unsigned short address, unsigned char* data, unsigned short length)
{
    unsigned short i;
    for (i = 0; i < length; i++)
    {
        data[i] = eeprom_read_byte(address + i);
        delay_milliseconds(5); // Small delay to ensure EEPROM read is complete
    }
}
