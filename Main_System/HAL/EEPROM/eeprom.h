#ifndef EEPROM_H_
#define EEPROM_H_


#include "..\..\LIB\STD_TYPES.h"

void eeprom_init(void);
void eeprom_write_byte(unsigned short address, unsigned char data);
unsigned char eeprom_read_byte(unsigned short address);
void eeprom_write_block(unsigned short address, const unsigned char* data, unsigned short length);
void eeprom_read_block(unsigned short address, unsigned char* data, unsigned short length);

#endif /* EEPROM_H_ */
