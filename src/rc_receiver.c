#include <avr/io.h>
#include <avr/interrupt.h>
#include "rc_receiver_interface.h"

// Define global variables
uint16_t prev_time[4], current_time[4], time_dif[4];
volatile uint16_t duty_cycle[4];
uint8_t previous_bits = 0xFF;


// Initialise the receiver.
void receiver_init() {
	/////////////////////////////// TIMER1 initialization/////////////////////////////////////////
	TCCR1B |=  _BV(CS11) | _BV(CS10); 	// Set prescaler set to 64. This ensures
										// that the resolution is 250, which should begin
										// sufficient for the purpose of measuring the duty cycle
										// of PWM signals. If we would like to change the accuracy
										// to ~2000, prescaler would need to be set to 1024 
	TCNT1 = 0;	// Initialize the counter
	/////////////////////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////// Enabling Pin Changing Interrupts /////////////////////////////
	DDRC &= ~((1<<DDC0)|(1<<DDC1)|(1<<DDC2)|(1<<DDC3));		// Enable pin PC0, PC1, PC2 
															// and PC3 as inputs.
	PORTC = (1<<PORTC0)|(1<<PORTC1)|(1<<PORTC2)|(1<<PORTC3);	// Enable pull-up resistor  
																// on pin PC0, PC1, PC2 & PC3.
	PCICR |= 1<<PCIE1; 	// Enable pin change interrupt 1
	PCMSK1 |= (1<<PCINT8)|(1<<PCINT9)|(1<<PCINT10)|(1<<PCINT11);	// Enable pin change interrupt 
																	// on the corresponding to
																	// I/O (PC0, PC1, PC2 & PC3).
	//////////////////////////////////////////////////////////////////////////////////////////////
}

// Interrupt service rutine for handling the measurements of the duty cycles of the PWM signals 
// produced by the RC receiver. In the code we assumed 4 channels. The crresponding pins are:
// PC0, PC1, PC2 and PC3.
ISR(PCINT1_vect){
	uint8_t change_bits;
	change_bits = previous_bits^PINC;
	
	// The following 4 if statements calculetes the difference in the time that passed beetwen
	// consecutive edges of the PWM signals. In the function we also handle the case when the 
	// counter overflows to ensure aprioprate duty cycle calculation. The duty cycle is eventually
	// calculated by subtracting 415 from the obtained time difference. This value correspond to 
	// 1000us. The 1ms-2ms pulses are, hence, mapped to a 0-250 range of values.
	if(change_bits & (1<<PC0) ){ 
        current_time[0] = TCNT1;
        if(prev_time[0]>current_time[0])
			time_dif[0] = 65535-prev_time[0]+current_time[0];
          else
			time_dif[0]=current_time[0]-prev_time[0];
			prev_time[0] = TCNT1;
			if (previous_bits & (1<<PC0))
				duty_cycle[0]=time_dif[0]-415;
       }
    if(change_bits & (1<<PC1) ){
        current_time[1] = TCNT1;
        if (prev_time[1]>current_time[1])
        	time_dif[1] = 65535-prev_time[1]+current_time[1];
        else
        	time_dif[1]=current_time[1]-prev_time[1];
        prev_time[1] = TCNT1;
        if (previous_bits & (1<<PC1))
        	duty_cycle[1]=time_dif[1]-415;
    }
    if(change_bits & (1<<PC2) ){ 
        current_time[2] = TCNT1;
        if (prev_time[2]>current_time[2])
        	time_dif[2] = 65535-prev_time[2]+current_time[2];
        else
        	time_dif[2]=current_time[2]-prev_time[2];
        prev_time[2] = TCNT1;
        if (previous_bits & (1<<PC2))
        	duty_cycle[2]=time_dif[2]-415;
    }
    if(change_bits & (1<<PC3) ){
        current_time[3] = TCNT1;
        if (prev_time[3]>current_time[3])
        	time_dif[3] = 65535-prev_time[3]+current_time[3];
        else
        	time_dif[3]=current_time[3]-prev_time[3];
        prev_time[3] = TCNT1;
        if (previous_bits & (1<<PC3))
        	duty_cycle[3]=time_dif[3]-415;
    }
    previous_bits = PINC;
}

// This function reads the current input signlas from the RC receiver and puts them into 
// the data structure that will be send to the control module
void receive_rc_packet(rc_data_packet_t* rc_data_packet){
	rc_data_packet->channel_0 = duty_cycle[0];
	rc_data_packet->channel_1 = duty_cycle[1];
	rc_data_packet->channel_2 = duty_cycle[2];
	rc_data_packet->channel_3 = duty_cycle[3];
}
