#include <avr/io.h>
#include "util/delay.h"
#include <avr/interrupt.h>

ISR (INT0_vect) {
    // If the PIND is high, we output from PORTB for 3 seconds
    if((PIND & 0x02) == 0x02){
        PORTB = 0xFF; // Turn LED on
        _delay_ms(3000);
    }
    PORTB = 0x00;

}

int main(void)
{
    DDRC = 0x00; // input from port c
    DDRB = 0xFF; // Output from B
    DDRD = 0x00; // Input on PD2 


    EICRA = 0x03; // Rising edge triggered
    sei(); // Enable global interrupt
    EIMSK |= (1 << INT0); // Enable interrupt for INT0
    EIFR = 0x01; // Enable flag for INT0


    while (1) 
    {

        if((PINC & 0x01) == 0x01){
             PORTB = 0xFF; // Turn LED on
        }
        _delay_ms(1500);
        PORTB = 0x00;

    }
} 
