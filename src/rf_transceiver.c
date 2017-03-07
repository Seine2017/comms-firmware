// This file defines the interface between the RF transmitter and the communication module

#include "SPI.h"
#include "data_structures.h"

// Define a function to initialize the RF transceiver as a transmitter
void rf_receiver_init(){
	
}
// Define a function to initialize the RF transceiver as a receiver
void rf_transmitter_init(){
	
}
// Define a function to send a data packet to the RF transmmitter using SPI
void send_rf_packet(rf_data_packet_t* rf_data_packet){
	
}
// Declare a function to receive a data packet from the RF receiver using SPI
void receive_rf_packet(rf_data_packet_t* rf_data_packet){
	
}
// Declare a function to put the logging data into the data structure that will be send 
// to the communication module
void put_into_rf_packet(rf_data_packet_t* rf_data_packet, float roll, float pitch, float yaw_vel){
	rf_data_packet->roll.value=roll;
	rf_data_packet->pitch.value=pitch;
	rf_data_packet->yaw_vel.value=yaw_vel;
}
