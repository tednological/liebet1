#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define LED_PIN PB5
#define SWITCH_PIN PC1

// Delay subroutine .15 seconds
void delay_150ms(void) {
	_delay_ms(150);
}

int main(void) {
	// Set PB5 as output
	DDRB |= (1 << LED_PIN);
	// Set PC1 as input
	DDRC &= ~(1 << SWITCH_PIN);
	// Set PD2 as input
	DDRD |= (1 << INTERRUPT_PIN);
	// Enable pull-up resistor for PC1
	PORTC |= (1 << SWITCH_PIN);

	while (1) {
		// Poll PC1
		if (PINC & (1 << SWITCH_PIN)) {
			PORTB |= (1 << LED_PIN); // turn on LED
			// delay subroutine called 10 times
			for (int i = 0; i < 10; i++) {
				delay_150ms();
			}
			PORTB &= ~(1 << LED_PIN); // Turn off the LED
		}
	}

	return 0;
}
