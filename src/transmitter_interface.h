// This file defines the interface between the RF transmitter and the communication module

#ifndef __RF_TRANSMITTER_INTERFACE_H
#define __RF_TRANSMITTER_INTERFACE_H

#include "data_structures.h"
#include "SPI.h"

// Declare a function to initialize the RF transceiver as a transmitter

// Declare a function to initialize the RF transceiver as a receiver
void transmitter_init();
// Declare a function to send a data packet to the RF transmmitter using SPI
void send_rf_packet(rf_data_packet_t* rf_data_packet);

#endif