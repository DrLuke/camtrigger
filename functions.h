#ifndef __FUN_H
#define __FUN_H

#include <avr/io.h>
#include <stdint.h>
#include "eeprom.h"

// Pins of the camera Trigger
#define T1_P PB0	// Focus + data pin, must be pin with ADC!
#define T2_P PB0	// Take Picture

#define SET_P PB0	// Settings pin	LOW = Function 1
		//		HIGH = Function 2


void continuous();
void timed1();
void timed2();
uint8_t check_data();


#endif
