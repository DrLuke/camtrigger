#include "eeprom.h"

uint8_t read_e(uint8_t addr)
{
	while(EECR & (1 << EEPE));	// Wait for eventual write cycle to complete
	EEAR = addr;	// Set EEPROM-address to desired address
	EECR = (1 << EERE);	// Start read of EEPROM

	return EEDR;	// Return data from EEPROM
}

void write_e(uint8_t addr, uint8_t data)
{
	while(EECR & (1 << EEPE));	// Wait for eventual write cycle to complete
	EECR = (0 << EEPM1) | (0 << EEPM0);	// Set programming mode
	EEAR = addr;	// Set EEPROM-address to desired address
	EEDR = data;	// Set data to be written
	EECR = (1 << EEMPE);	// No idea why this must be done
	EECR |= (1 << EEPE);	// Initiate erase/write cycle
}


