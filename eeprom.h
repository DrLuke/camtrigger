#ifndef __EE_H
#define __EE_H

#include <avr/io.h>
#include <stdint.h>

uint8_t read_e(uint8_t addr);
void write_e(uint8_t addr, uint8_t data);

#endif
