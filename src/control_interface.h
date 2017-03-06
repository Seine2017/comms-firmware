// This file specifies the interface between the inter-pprocessor communication
// code (written by Kiran) and the control code (written by Kier)

#ifndef __CONTROL_INTERFACE_H
#define __CONTROL_INTERFACE_H

#include "data_structures.h"
#include "SPI.h" // we have to define the library

// declare a function to initialize SPI communication with the control module
void comms_init();


// define a function to send a data packet with the RC inputs to 
// the RF transmitter using SPI
void send_data_packet(rc_data_packet_t* rc_data_packet); //does '_t' corresponds to type ???

// define a function to receive a data packet with logging data from the control 
// control module using SPI
void receive_data_packet(logg_data_packet_t* logg_data_packet); 

#endif