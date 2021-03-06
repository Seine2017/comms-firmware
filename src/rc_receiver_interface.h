// This file implements integration of the RC receiver with the communication code
// (written by Pawel). It takes adventage of the Pin Changing Interrupts available
// on the microcontroller. It also uses a TIMER1 to aprioprately set to achive
// resolution of 250 in the measurement of the PWM signals from RC receiver.

#ifndef __RC_RECEIVER_INTERFACE_H
#define __RC_RECEIVER_INTERFACE_H

#include "data_structures.h"

// Initialise the receiver. In order to make this function work we also need to initialize
// interrupts - 'sei();'.
void receiver_init();
void receive_rc_packet(rc_data_packet_t* rc_data_packet);

#endif
