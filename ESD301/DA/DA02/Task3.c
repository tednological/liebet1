#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define LED_PIN PB5
#define INTERRUPT_PIN PD2

ISR (INT0_vect) {
	// If the PIND is high, we output from PORTB for 3 seconds
	if (PIND & (1 << INTERRUPT_PIN)) {
		PORTB |= (1 << LED_PIN); // turn on LED
		// delay subroutine called 20 times for 3 second delay
		for (int i = 0; i < 20; i++) {
			delay_150ms();
		}
		PORTB &= ~(1 << LED_PIN); // Turn off the LED
	}

}
// Delay subroutine .15 seconds
void delay_150ms(void) {
	_delay_ms(150);
}

int main(void) {
	// Set PB5 as output
	DDRB |= (1 << LED_PIN);
	// Set PD2 as input
	DDRD |= (1 << INTERRUPT_PIN);
  
	EICRA = 0x03; // Rising edge triggered
	sei(); // Enable global interrupt
	EIMSK |= (1 << INT0); // Enable interrupt for INT0
	EIFR = 0x01; // Enable flag for INT0

	while (1) {
	}

	return 0;
}
