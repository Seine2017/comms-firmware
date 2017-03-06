// This file implements integration of the RC receiver with the communication code
// (written by Pawel)

#ifndef __RC_RECEIVER_INTERFACE_H
#define __RC_RECEIVER_INTERFACE_H


static void init_TIMER1(){

	TCCR1B |=  1<<CS12 | 1<<CS10; //prescaler set to 1024
	TCNT1 = 0;//initialize counter
}

// Initialise the receiver.
void receiver_init() {
  // Set up timer 0:
  //   COM0A = 00 (OC0A disconnected)
  //   COM0B = 00 (OC0B disconnected)
  //   WGM0 = 010 (clear timer on compare match)
  //   CS0 = 010 (prescaler = 8)
  //   OCIE0A = 0 (no interrupt on output compare match A)
  //   OCIE0B = 0 (no interrupt on output compare match B)
  //   TOIE0 = 1 (interrupt on timer overflow)
  TCCR0A = _BV(WGM01);
  TCCR0B = _BV(CS01);
  TIMSK0 = _BV(TOIE0);

  //    F_OVERFLOW = F_CPU / (PRESCALER * (1 + OCR0A))
  // => OCR0A = F_CPU / (PRESCALER * F_OVERFLOW) - 1
  OCR0A = (uint8_t) (((uint32_t) F_CPU) / (((uint32_t) 8) * ((uint32_t) TICKS_PER_SECOND)) - 1);
}

#endif