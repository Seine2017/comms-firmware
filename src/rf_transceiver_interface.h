// This file defines the interface between the RF transmitter and the communication module

#ifndef __RF_TRANSMITTER_INTERFACE_H
#define __RF_TRANSMITTER_INTERFACE_H

// Declare a function to initialize the RF transceiver as a transmitter
void rf_transmitter_init();
// Declare a function to initialize the RF transceiver as a receiver
void rf_receiver_init();
// Declare a function to send a data packet to the RF transmmitter using SPI
void send_rf_packet(rf_data_packet_t* rf_data_packet);
// Declare a function to receive a data packet from the RF receiver using SPI
void receive_rf_packet(rf_data_packet_t* rf_data_packet);

#endif