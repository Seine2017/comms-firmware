// This file implements the data conversion between 8 bits data packets received from the 
// RF receiver and its corresponding floating point numbers.(Written by Dominic) The data is 
// further put into data structure that will be send to  the host computer for telemetry purposes.

#include "data_conversion.h"

// Encode the data
void encode_data(logg_data_packet_t* logg_data_packet, rf_data_packet_t* rf_data_packet){
	rf_data_packet->roll.value = logg_data_packet->roll.value;
	rf_data_packet->pitch.value = logg_data_packet->pitch.value;
	rf_data_packet->yaw_vel.value = logg_data_packet->yaw_vel.value;
}

// Decode the data
// Declares a function that convertes the data received through RF communication
// received in packets of bytes to its corresponding float numbers and puts all the data
// into the structure to send the data to the host
void decode_data(rf_data_packet_t* rf_data_packet, host_data_packet_t* host_data_packet){
	host_data_packet->roll = rf_data_packet->roll.value;
	host_data_packet->pitch = rf_data_packet->pitch.value;
	host_data_packet->yaw_vel = rf_data_packet->yaw_vel.value;
}
