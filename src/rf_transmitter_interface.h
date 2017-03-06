// This file defines the interface between the RF transmitter and the communication module

#ifndef __RF_TRANSMITTER_INTERFACE_H
#define __RF_TRANSMITTER_INTERFACE_H

#include "SPI.h"

// Define a structure for the data packet to be send to the host microcontroller
typedef struct{

}rf_data_packet_t;

// Define a function to send a data packet to the RF transmmitter using SPI
void send_rf_packet(rf_data_packet_t* rf_data_packet);

#endif