// This file simulates the Remote Controller receiver's output.
// It produces 4 PWM signals varying from 1000us up to 2000us.

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= 1<<PB0 | 1<<PB1 | 1<<PB2 | 1<<PB3; // set some pins to output

    uint16_t duty_cycle = 0; //set duty cycle to 0%
    uint16_t duty_cycle2 = 500; //set duty cycle to 25%
	uint16_t duty_cycle3 = 750; //set duty cycle to 75%
	uint16_t duty_cycle4 = 1000; //set duty cycle to 100%

    while(1) {
	_delay_us(4000);
	// Set pin B0 high
	PORTB |= _BV ( PB0 ) ;
	_delay_us(1000+duty_cycle);
	// Set pin B0 low
	PORTB &= ~ _BV ( PB0 );
	_delay_us(2000-duty_cycle);


	_delay_us(4000);
	// Set pin B1 high
	PORTB |= _BV ( PB1 ) ;
	_delay_us(1000+duty_cycle2);
	// Set pin B1 low
	PORTB &= ~ _BV ( PB1 );
	_delay_us(2000-duty_cycle2);


	_delay_us(4000);
	// Set pin B2 high
	PORTB |= _BV ( PB2 ) ;
	_delay_us(1000+duty_cycle3);
	// Set pin B2 low
	PORTB &= ~ _BV ( PB2 );
	_delay_us(2000-duty_cycle3);

	_delay_us(4000);
	// Set pin B2 high
	PORTB |= _BV ( PB3 ) ;
	_delay_us(1000+duty_cycle4);
	// Set pin B2 low
	PORTB &= ~ _BV ( PB3 );
	_delay_us(2000-duty_cycle4);

	duty_cycle = (duty_cycle+1)%1001;

    }
}
