#define F_CPU 8000000L

#include <avr/io.h>
#include <stdint.h>
#include "eeprom.h"
#include "functions.h"
#include <util/delay.h>

// See functions.h for pin definitions!

void funcaller(uint8_t fun)
{
	// This function chooses the appropriate function to go to, depending on the settings chosen. The data is
	// stored in the EEPROM
	
	uint8_t funmap = read_e(0x00);	// Read the function map data
	
	funmap = (funmap >> (fun?4:0)) | 0x0F;	// If the settings pin is set, access function 2 data, otherwise
						// access function 1 data. Then mask out the unneeded data.
	switch(funmap)
	{
		//No breaks needed, since the functions are infinite loops!
		case 0x00: continuous();
			   break;
		case 0x01: timed1();
			   break;
		case 0x02: timed2();
			   break;
		default: continuous();	// Just set this as default so SOMETHING happens.
	}
}



int main()
{
	// The DPDT switch has, as the name suggests, 2 poles and 2 throws. The switch has an ON-OFF-ON configuration.
	// This means that the switch is basically two switches in one, which can either connect the center pin to the 
	// top row, the low row, or with neither. That way I can assume that all power will be lost to the MCU when
	// the switch is flipped from the top row to the low row (or F1 to F2), as I use one of the switches to toggle
	// power to the voltage regulator.

	// Configure port
	DDRB = 0;	// All pins as inputs
	PORTB = (1 << SET_P) | (1 << T1_P);	// Enable pullup on SET_P and T1_P
	if(PINB & (1 << T1_P))
	{
		_delay_ms(300);
		if(PINB & (1 << T1_P))
		{
			check_data()	// Read in data if the dataline stays low for certain time
		}
	}
	// False alarm? Continue with normal code execution

	// Read out power setting
	for(;;)
	{
		funcaller(PINB & (1 << SET_P));	// Call the function caller function with the value of the settings pin
	}
	// We should never get here, unless something went wrong!

	return 0;
}
