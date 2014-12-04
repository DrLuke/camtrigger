#include "functions.h"

/* EEPROM map
 * 0x00:	funmap
 * 0x01:	
 */

uint8_t check_data()
{
	// Check if we have incoming data within the first few seconds of operation.
	uint8_t gotData = 0;
	gotdata = (PINB & (1 << T1_P))?0:1;	// If the T1_P-pin reads low, the line is being actively pulled down, since it's in pull-up high-z mode

	

}

void continuous()
{
	// This will continuously trigger the photo taking. Good for long time exposures.
	DDRB |= (1 << T2_P);	// Set "take picture" pin to output
	PORTB &= ~(1 << T2_P);	// Set "take picture" pin to low to trigger picture taking
	for(;;)	// Infinite loop
	{
		// Make sure this is set continuously to prevent accidents
		DDRB &= ~(1 << T1_P);	// Disable all output on "focus" pin
		PORTB |= (1 << T1_P);	// Enable pull-up on "focus" pin

		if(check_data()) { return; }
	}
}

void timed1()
{


}

void timed2()
{


}
