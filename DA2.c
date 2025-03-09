#include <avr/io.h>
#include "util/delay.h"
#include <avr/interrupt.h>

ISR (INT0_vect) {
	
	if((PIND & 0x01) == 0x01)j{
		PORTB = 0xFF;
		_delay_ms(3000);
	}
	
}

int main(void)
{
	DDRC = 0x00; // input from port c
	DDRB = 0xFF; // Output from B
	DDRD = 0x00; // Input on PD2 
	
	
	EICRA = 0x03;
	sei();
	EIMSK |= (1 << INT0);
	EIFR = 0x01;
	

    while (1) 
    {
		
		if((PINC & 0x01) == 0){
			 PORTB = 0xFF;
		}
		_delay_ms(1500);
		
    }
}


