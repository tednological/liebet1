#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>



// Delay subroutine .15 seconds
void delay_150ms(void) {
	_delay_ms(150);
}

int main(){
	delay_150ms();
	return 0;
}
