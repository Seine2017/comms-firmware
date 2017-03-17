#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "debug.h"
uint16_t prev_time, current_time, time_dif, prev_time2, current_time2, time_dif2;
uint8_t previous_bits = 0xFF;
void init_TIMER1(){
TCCR1B |= 1<<CS12 | 1<<CS10; //prescaler set to 1024
TCNT1 = 0;//initialize counter
}
void init_PWM_interupt(){
DDRC &= ~((1<<DDC0) | (1<<DDC1)); //enable pin PC5 & PC6 as input
PORTC = (1<< PORTC0) | (1<< PORTC1); //enable pull-up resistor on pin PC5 & PC6
PCICR |= 1<<PCIE1; // enable pin change interrupt 1
PCMSK1 |= (1<<PCINT8) | (1<<PCINT9); //enable pin change interrupt on the corresponding I/O (PC5 &
PC6)
sei(); //enable interrupts
}
ISR(PCINT1_vect){
uint8_t change_bits;
 PORTB ^= 1<<PB5; // LED toggle (PB5)
 //calculate time difference of the pulse
 change_bits = previous_bits^PINC;
 //check which bit has changed, there is an issue that with a PWM input
 //that is created by the same time the change of the inputs occurs exactly at the same time,
therefore, one of the inputs is measured every other
 //if the inputs start at different time, the correct PWM duty cycle should be measured
 //the timer has to be set appropriately in order to avoid the overflow
 if (change_bits & (1<<PC0) ){
 current_time = TCNT1;
 if (prev_time>current_time)
 time_dif = 65535-prev_time+current_time; //65535 is set, because we are using 16 bit timer and
this is the TOP value
 else
 time_dif=current_time-prev_time;
 prev_time = TCNT1;
 //only print if changed from logic 1 to 0 (falling edge)
 if(previous_bits& (1<<PC0))
 printf("PC0 duty cycle: %d\n",time_dif);
 }else if(change_bits & (1<<PC1) ){ // repeat the same for the second pin
 current_time2 = TCNT1;
 if (prev_time2>current_time2)
 time_dif2 = 65535-prev_time2+current_time2;
 else
 time_dif2=current_time2-prev_time2;
 prev_time2 = TCNT1;
 if (previous_bits & (1<<PC1))
 printf("PC1 duty cycle: %d\n",time_dif2);
 }
 //the above two parts of code will be repeated for pins PC2, PC3, PC4, PC5 giving overall 6 PWM inputs
that will be used as a control signals
 previous_bits = PINC;
}
int main(void) {
 DDRB |= 1<<PB5; // set PB5 to output
 init_TIMER1();
 init_PWM_interupt();
 init_debug_uart0();
 while(1);
}
