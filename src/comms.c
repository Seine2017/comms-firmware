
#include "control_interface.h"
#include "data_structures.h"
#include "SPI.h" // we have to define the library

// Define a function to initialize SPI communication with the control module
void comms_master_init(){
	
}

// Define a function to initialize SPI communication with the communication module
void comms_slave_init(){
	
}

// Define a function to send a data packet with the RC inputs to 
// the control module
void send_data_packet(rc_data_packet_t* rc_data_packet){
	
}

// Define a function to receive a data packet with logging data from the control 
// control module using SPI
void receive_data_packet(logg_data_packet_t* logg_data_packet){
	
}

// Define a function to send a data packet with the logging data to the 
// communicaiton module
void send_data_packet(rc_data_packet_t* rc_data_packet){
	
}

// Define a function to receive a data packet with RC inpunts from the
// communication module
void receive_data_packet(logg_data_packet_t* logg_data_packet){
	
}